//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "Platform_Windows_WGL_ES_3_0/Platform_Windows_WGL_ES_3_0.h"

#include "Context_WGL/Context_WGL.h"
#include "Device_GL/Device_GL.h"

#include "Utils/LogMacros.h"


namespace ramses_internal
{
    IPlatformFactory* PlatformFactory_Base::CreatePlatformFactory(const RendererConfig& rendererConfig)
    {
        return new Platform_Windows_WGL_ES_3_0(rendererConfig);
    }

    Platform_Windows_WGL_ES_3_0::Platform_Windows_WGL_ES_3_0(const RendererConfig& rendererConfig)
        : PlatformFactory_Windows_WGL(rendererConfig)
    {
    }

    IDevice* Platform_Windows_WGL_ES_3_0::createDevice(IContext& context)
    {
        Context_WGL* platformContext = getPlatformContext<Context_WGL>(context);
        assert(0 != platformContext);
        Device_GL* device = new Device_GL(*platformContext, 3, 0, true);
        return addPlatformDevice(device);
    }

    const Int32* Platform_Windows_WGL_ES_3_0::getContextAttributes()
    {
        const Int32* returnValue = NULL;

        if(m_wglExtensions.isExtensionAvailable("create_context_profile"))
        {
            static const Int32 attribs[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 0,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_ES_PROFILE_BIT_EXT, 0,
                0
            };
            returnValue = attribs;
        }
        else
        {
            LOG_ERROR(CONTEXT_RENDERER, "Platform_Windows_WGL_ES_3_0::getContextAttributes:  could not load WGL context attributes");
        }

        return returnValue;
    }
}
