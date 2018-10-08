//  -------------------------------------------------------------------------
//  Copyright (C) 2012 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------


#include "SceneTest.h"

using namespace testing;

namespace ramses_internal
{
    TYPED_TEST_CASE(AScene, SceneTypes);

    TYPED_TEST(AScene, ContainsCreatedRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        EXPECT_TRUE(this->m_scene.isRenderableAllocated(renderable));
    }

    TYPED_TEST(AScene, ReleasesRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        this->m_scene.releaseRenderable(renderable);

        EXPECT_FALSE(this->m_scene.isRenderableAllocated(renderable));
    }

    TYPED_TEST(AScene, ReturnsNodeOfRenderable)
    {
        const NodeHandle node = this->m_scene.allocateNode();
        const RenderableHandle renderable = this->m_scene.allocateRenderable(node);

        EXPECT_EQ(node, this->m_scene.getRenderable(renderable).node);
    }

    TYPED_TEST(AScene, ReturnsInvalidEffectResourceForNewRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());

        EXPECT_EQ(ResourceContentHash::Invalid(), this->m_scene.getRenderable(renderable).effectResource);
    }

    TYPED_TEST(AScene, ReturnsInvalidRenderStateForNewRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());

        EXPECT_EQ(RenderStateHandle::Invalid(), this->m_scene.getRenderable(renderable).renderState);
    }

    TYPED_TEST(AScene, SetsRenderStateForRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        const RenderStateHandle state = this->m_scene.allocateRenderState();
        this->m_scene.setRenderableRenderState(renderable, state);

        EXPECT_EQ(state, this->m_scene.getRenderable(renderable).renderState);
    }

    TYPED_TEST(AScene, SetsEffectAndGeometryLayoutRenderable)
    {
        const ResourceContentHash hash(123u, 0);
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        this->m_scene.setRenderableEffect(renderable, hash);

        EXPECT_EQ(hash, this->m_scene.getRenderable(renderable).effectResource);
    }

    TYPED_TEST(AScene, SetsDataInstanceToRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        const DataLayoutHandle layoutHandle = this->m_scene.allocateDataLayout({});
        const DataInstanceHandle dataInstance1 = this->m_scene.allocateDataInstance(layoutHandle);
        const DataInstanceHandle dataInstance2 = this->m_scene.allocateDataInstance(layoutHandle);
        this->m_scene.setRenderableDataInstance(renderable, ERenderableDataSlotType_Uniforms, dataInstance1);
        this->m_scene.setRenderableDataInstance(renderable, ERenderableDataSlotType_Geometry, dataInstance2);

        EXPECT_EQ(dataInstance1, this->m_scene.getRenderable(renderable).dataInstances[ERenderableDataSlotType_Uniforms]);
        EXPECT_EQ(dataInstance2, this->m_scene.getRenderable(renderable).dataInstances[ERenderableDataSlotType_Geometry]);
    }

    TYPED_TEST(AScene, DrawsNothingIfIndicesRangeNotSpecified)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());

        EXPECT_EQ(0u, this->m_scene.getRenderable(renderable).startIndex);
        EXPECT_EQ(0u, this->m_scene.getRenderable(renderable).indexCount);
    }

    TYPED_TEST(AScene, SetsStartIndexOfRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        this->m_scene.setRenderableStartIndex(renderable, 12u);

        EXPECT_EQ(12u, this->m_scene.getRenderable(renderable).startIndex);
    }

    TYPED_TEST(AScene, SetsIndexCountOfRenderable)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        this->m_scene.setRenderableIndexCount(renderable, 12);

        EXPECT_EQ(12u, this->m_scene.getRenderable(renderable).indexCount);
    }

    TYPED_TEST(AScene, SetsRenderableVisible)
    {
        const RenderableHandle renderable = this->m_scene.allocateRenderable(this->m_scene.allocateNode());
        this->m_scene.setRenderableVisibility(renderable, false);

        EXPECT_EQ(false, this->m_scene.getRenderable(renderable).isVisible);
    }

    TYPED_TEST(AScene, ContainsZeroTotalRenderablesUponCreation)
    {
        EXPECT_EQ(0u, this->m_scene.getRenderableCount());
    }

    TYPED_TEST(AScene, CreatingRenderableIncreasesRenderableCount)
    {
        this->m_scene.allocateRenderable(this->m_scene.allocateNode());

        EXPECT_EQ(1u, this->m_scene.getRenderableCount());
    }
}
