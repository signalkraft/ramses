//  -------------------------------------------------------------------------
//  Copyright (C) 2015 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "RendererCommands/SystemCompositorControllerListIviSurfaces.h"
#include "Ramsh/RamshInput.h"

namespace ramses_internal
{
    SystemCompositorControllerListIviSurfaces::SystemCompositorControllerListIviSurfaces(RendererCommandBuffer& rendererCommandBuffer)
        : m_rendererCommandBuffer(rendererCommandBuffer)
    {
        description = "print out a list of ivi-ids that are registered at the system compositor";
        registerKeyword("scListSurfaces");
        registerKeyword("scl");
    }

    Bool SystemCompositorControllerListIviSurfaces::executeInput(const RamshInput& input)
    {
        UNUSED(input);
        m_rendererCommandBuffer.systemCompositorControllerListIviSurfaces();
        return true;
    }
}
