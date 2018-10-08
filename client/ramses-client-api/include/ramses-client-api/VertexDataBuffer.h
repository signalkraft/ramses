//  -------------------------------------------------------------------------
//  Copyright (C) 2017 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_VERTEXDATABUFFER_H
#define RAMSES_VERTEXDATABUFFER_H

#include "ramses-client-api/SceneObject.h"
#include "ramses-client-api/EDataType.h"

namespace ramses
{
    /**
    * @brief The VertexDataBuffer is a mutable scene resource used to specify attribute vertex data in a GeometryBinding
    */
    class RAMSES_API VertexDataBuffer : public SceneObject
    {
    public:

        /**
        * @brief Update data of VertexDataBuffer resource.
        *
        * @param data               Pointer in memory to the data provided for update. The function makes
        *                           a copy of the data into VertexDataBuffer data structures. VertexDataBuffer
        *                           object does not take ownership of the memory data passed to it.
        * @param dataSizeInBytes    The size in bytes of the resource data to be updated. Data size
        *                           must be less than or equal to the maximum data size specified at
        *                           creation time of the VertexDataBuffer object. The function writes
        *                           resource data up to the specified size only, leaving without modifying
        *                           the remaining resource data after specified size.
        * @param offsetInBytes      The offset in bytes at which data update should begin.
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t setData(const char* data, uint32_t dataSizeInBytes, uint32_t offsetInBytes = 0u);

        /**
        * @brief Returns the maximum size (in bytes) of data that can be stored in the data buffer
        *
        * @return Maximum size in bytes
        */
        uint32_t getMaximumSizeInBytes() const;

        /**
        * @brief Returns the used size (in bytes) of data.
        *        If data buffer fully set by \c setData, then used and maximum size are equal.
        *
        * @return Used size in bytes
        */
        uint32_t getUsedSizeInBytes() const;

        /**
        * @brief Returns the data type associated with the resource data
        *
        * @return data type of resource data
        */
        EDataType getDataType() const;

        /**
        * @brief Copies the data of the data buffer into a user-provided buffer. The buffer must
        * be sufficiently large to hold the data for the whole data buffer
        *
        * @param[out] buffer The buffer where the resource data will be copied into
        * @param[in] bufferSize The size of given buffer in bytes
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t getData(char* buffer, uint32_t bufferSize) const;

        /**
        * Stores internal data for implementation specifics of VertexDataBuffer.
        */
        class VertexDataBufferImpl& impl;

    protected:
        /**
        * @brief Scene is the factory for creating VertexDataBuffer instances.
        */
        friend class SceneImpl;

        /**
        * @brief Constructor for VertexDataBuffer.
        *
        * @param[in] pimpl Internal data for implementation specifics of VertexDataBuffer (sink - instance becomes owner)
        */
        explicit VertexDataBuffer(VertexDataBufferImpl& pimpl);

        /**
        * @brief Destructor of the VertexDataBuffer
        */
        virtual ~VertexDataBuffer();
    };
}

#endif
