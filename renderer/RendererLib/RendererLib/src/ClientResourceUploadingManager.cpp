//  -------------------------------------------------------------------------
//  Copyright (C) 2017 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "RendererLib/ClientResourceUploadingManager.h"
#include "RendererLib/RendererClientResourceRegistry.h"
#include "RendererLib/IResourceUploader.h"
#include "RendererAPI/IRenderBackend.h"
#include "RendererAPI/IEmbeddedCompositingManager.h"
#include "RendererAPI/IDevice.h"
#include "Utils/LogMacros.h"
#include "Common/Cpp11Macros.h"
#include "PlatformAbstraction/PlatformTime.h"
#include "RendererLib/FrameTimer.h"

namespace ramses_internal
{
    ClientResourceUploadingManager::ClientResourceUploadingManager(
        RendererClientResourceRegistry& resources,
        IResourceUploader& uploader,
        IRenderBackend& renderBackend,
        Bool keepEffects,
        const FrameTimer& frameTimer,
        UInt64 clientResourceCacheSize)
        : m_clientResources(resources)
        , m_uploader(uploader)
        , m_renderBackend(renderBackend)
        , m_keepEffects(keepEffects)
        , m_frameTimer(frameTimer)
        , m_clientResourceCacheSize(clientResourceCacheSize)
    {
    }

    ClientResourceUploadingManager::~ClientResourceUploadingManager()
    {
        // Unload all remaining resources that were kept due to caching strategy.
        // Or in case display is being destructed together with scenes and there is no more rendering,
        // ie. no more deferred upload/unloads
        ResourceContentHashVector resourcesToUnload;
        getClientResourcesToUnloadNext(resourcesToUnload, false, std::numeric_limits<UInt64>::max());
        unloadClientResources(resourcesToUnload);

        ramses_foreach(m_clientResources.getAllResourceDescriptors(), res)
        {
            assert(res->value.status != EResourceStatus_Uploaded);
        }
    }

    Bool ClientResourceUploadingManager::hasAnythingToUpload() const
    {
        return !m_clientResources.getAllProvidedResources().empty();
    }

    void ClientResourceUploadingManager::uploadAndUnloadPendingResources()
    {
        ResourceContentHashVector resourcesToUpload;
        UInt64 sizeToUpload = 0u;
        getAndPrepareClientResourcesToUploadNext(resourcesToUpload, sizeToUpload);
        const UInt64 sizeToBeFreed = getAmountOfMemoryToBeFreedForNewResources(sizeToUpload);

        ResourceContentHashVector resourcesToUnload;
        getClientResourcesToUnloadNext(resourcesToUnload, m_keepEffects, sizeToBeFreed);

        unloadClientResources(resourcesToUnload);
        uploadClientResources(resourcesToUpload);
    }

    void ClientResourceUploadingManager::unloadClientResources(const ResourceContentHashVector& resourcesToUnload)
    {
        ramses_foreach(resourcesToUnload, res)
        {
            const ResourceDescriptor& rd = m_clientResources.getResourceDescriptor(*res);
            unloadClientResource(rd);
        }
    }

    void ClientResourceUploadingManager::uploadClientResources(const ResourceContentHashVector& resourcesToUpload)
    {
        for (UInt32 i = 0; i < resourcesToUpload.size(); ++i)
        {
            const ResourceDescriptor& rd = m_clientResources.getResourceDescriptor(resourcesToUpload[i]);
            const UInt32 resourceSize = rd.resource.getResourceObject()->getDecompressedDataSize();
            uploadClientResource(rd);

            const Bool checkTimeLimit = (i % NumResourcesToUploadInBetweenTimeBudgetChecks == 0) || rd.type == EResourceType_Effect || resourceSize > LargeResourceByteSizeThreshold;
            if (checkTimeLimit && m_frameTimer.isTimeBudgetExceededForSection(EFrameTimerSectionBudget::ClientResourcesUpload))
            {
                LOG_INFO(CONTEXT_RENDERER, "ClientResourceUploadingManager::uploadClientResources: Interrupt: Exceeded time for client resource upload");
                break;
            }
        }
    }

    void ClientResourceUploadingManager::uploadClientResource(const ResourceDescriptor& rd)
    {
        assert(rd.resource.getResourceObject() != NULL);
        assert(!rd.deviceHandle.isValid());
        LOG_TRACE(CONTEXT_PROFILING, "        ResourceUploadingManager::uploadResource upload resource of type " << EnumToString(rd.type));

        const IResource* pResource = rd.resource.getResourceObject();
        assert(pResource->isDeCompressedAvailable());

        const UInt32 resourceSize = pResource->getDecompressedDataSize();
        const DeviceResourceHandle deviceHandle = m_uploader.uploadResource(m_renderBackend, rd.resource);
        m_clientResources.setResourceData(rd.hash, ManagedResource(), deviceHandle, pResource->getTypeID());
        if (deviceHandle.isValid())
        {
            m_clientResourceSizes.put(rd.hash, resourceSize);
            m_clientResourceTotalUploadedSize += resourceSize;
            m_clientResources.setResourceStatus(rd.hash, EResourceStatus_Uploaded);
        }
        else
        {
            LOG_ERROR(CONTEXT_RENDERER, "ResourceUploadingManager::uploadResource failed to upload resource #" << StringUtils::HexFromResourceContentHash(rd.hash) << " (" << EnumToString(rd.type) << ")");
            m_clientResources.setResourceStatus(rd.hash, EResourceStatus_Broken);
        }
    }

    void ClientResourceUploadingManager::unloadClientResource(const ResourceDescriptor& rd)
    {
        assert(rd.sceneUsage.empty());
        assert(rd.status == EResourceStatus_Uploaded);
        assert(m_clientResourceSizes.contains(rd.hash));

        LOG_TRACE(CONTEXT_PROFILING, "        ResourceUploadingManager::unloadResource delete resource of type " << EnumToString(rd.type));
        LOG_TRACE(CONTEXT_RENDERER, "ResourceUploadingManager::unloadResource Unloading resource #" << rd.hash);
        m_uploader.unloadResource(m_renderBackend, rd.type, rd.hash, rd.deviceHandle);

        auto resSizeIt = m_clientResourceSizes.find(rd.hash);
        assert(m_clientResourceTotalUploadedSize >= resSizeIt->value);
        m_clientResourceTotalUploadedSize -= resSizeIt->value;
        m_clientResourceSizes.remove(resSizeIt);

        LOG_TRACE(CONTEXT_RENDERER, "ResourceUploadingManager::unloadResource Removing resource descriptor for resource #" << rd.hash);
        m_clientResources.unregisterResource(rd.hash);
    }

    void ClientResourceUploadingManager::getClientResourcesToUnloadNext(ResourceContentHashVector& resourcesToUnload, Bool keepEffects, UInt64 sizeToBeFreed) const
    {
        assert(resourcesToUnload.empty());
        const ResourceContentHashVector& unusedResources = m_clientResources.getAllResourcesNotInUseByScenes();
        UInt64 sizeToUnload = 0u;

        // collect unused resources to be unloaded
        // if total size of resources to be unloaded is enough
        // we stop adding more unused resources, they can be kept uploaded as long as not more memory is needed
        for (const auto& hash : unusedResources)
        {
            if (sizeToUnload >= sizeToBeFreed)
            {
                break;
            }

            const ResourceDescriptor& rd = m_clientResources.getResourceDescriptor(hash);
            if (rd.status == EResourceStatus_Uploaded)
            {
                const Bool keepEffectCached = keepEffects && (rd.type == EResourceType_Effect);
                if (!keepEffectCached)
                {
                    resourcesToUnload.push_back(hash);
                    assert(m_clientResourceSizes.contains(hash));
                    sizeToUnload += *m_clientResourceSizes.get(hash);
                }
            }
        }
    }

    void ClientResourceUploadingManager::getAndPrepareClientResourcesToUploadNext(ResourceContentHashVector& resourcesToUpload, UInt64& totalSize) const
    {
        assert(resourcesToUpload.empty());

        totalSize = 0u;
        const ResourceContentHashVector& providedResources = m_clientResources.getAllProvidedResources();
        ramses_foreach(providedResources, res)
        {
            const ResourceContentHash hash = *res;
            const ResourceDescriptor& rd = m_clientResources.getResourceDescriptor(hash);
            assert(rd.status == EResourceStatus_Provided);
            assert(rd.resource.getResourceObject() != NULL);
            const IResource* resource = rd.resource.getResourceObject();
            resource->decompress();
            totalSize += resource->getDecompressedDataSize();

            resourcesToUpload.push_back(hash);
        }
    }

    UInt64 ClientResourceUploadingManager::getAmountOfMemoryToBeFreedForNewResources(UInt64 sizeToUpload) const
    {
        if (m_clientResourceCacheSize == 0u)
        {
            // unload all if no caching is allowed
            return std::numeric_limits<UInt64>::max();
        }

        if (m_clientResourceCacheSize > m_clientResourceTotalUploadedSize)
        {
            const UInt64 remainingCacheSize = m_clientResourceCacheSize - m_clientResourceTotalUploadedSize;
            if (remainingCacheSize < sizeToUpload)
            {
                return sizeToUpload - remainingCacheSize;
            }
            else
            {
                return 0u;
            }
        }
        else
        {
            // cache already exceeded, try unloading all that is above cache limit plus size for new resources to be uploaded
            return sizeToUpload + m_clientResourceTotalUploadedSize - m_clientResourceCacheSize;
        }
    }
}
