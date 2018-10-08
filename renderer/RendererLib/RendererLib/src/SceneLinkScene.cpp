//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "RendererLib/SceneLinkScene.h"
#include "RendererLib/SceneLinksManager.h"

namespace ramses_internal
{
    SceneLinkScene::SceneLinkScene(SceneLinksManager& sceneLinksManager, const SceneInfo& sceneInfo)
        : TransformationCachedSceneWithExplicitMemory(sceneInfo)
        , m_sceneLinksManager(sceneLinksManager)
    {
    }

    DataSlotHandle SceneLinkScene::allocateDataSlot(const DataSlot& dataSlot, DataSlotHandle handle)
    {
        const DataSlotHandle dataSlotHandle = TransformationCachedSceneWithExplicitMemory::allocateDataSlot(dataSlot, handle);
        m_sceneLinksManager.handleDataSlotCreated(getSceneId(), dataSlotHandle);

        return dataSlotHandle;
    }

    void SceneLinkScene::releaseDataSlot(DataSlotHandle handle)
    {
        m_sceneLinksManager.handleDataSlotDestroyed(getSceneId(), handle);
        TransformationCachedSceneWithExplicitMemory::releaseDataSlot(handle);
    }
}
