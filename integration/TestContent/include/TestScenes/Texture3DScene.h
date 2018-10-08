//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TEXTURE3DSCENE_H
#define RAMSES_TEXTURE3DSCENE_H

#include "IntegrationScene.h"

namespace ramses
{
    class Effect;
    class GroupNode;
    class Vector3fArray;
    class UInt16Array;
    class Texture3D;
}

namespace ramses_internal
{
    class Texture3DScene : public IntegrationScene
    {
    public:
        Texture3DScene(ramses::RamsesClient& ramsesClient, ramses::Scene& scene, UInt32 state, const Vector3& cameraPosition);

        enum
        {
            SLICES_4 = 0
        };

    protected:
        void createQuad(Float x, Float y, Float depth, Float texCoordMagnifier = 1.f);

        ramses::Effect* m_effect;
        ramses::GroupNode* m_groupNode;
        const ramses::Vector3fArray* m_vertexPositions;
        const ramses::UInt16Array* m_indices;
        ramses::Texture3D* m_texture;
    };
}

#endif
