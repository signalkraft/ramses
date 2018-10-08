//  -------------------------------------------------------------------------
//  Copyright (C) 2012 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "renderer_common_gmock_header.h"
#include "gmock/gmock.h"
#include "RendererLib/DisplayConfig.h"
#include "RendererLib/RendererConfig.h"

namespace ramses_internal
{
    void PrintTo(const DisplayConfig& config, ::std::ostream* os)
    {
        *os << "Fullscreen=" << config.getFullscreenState();
        *os << "\nBorderlesss=" << config.getBorderlessState();
        *os << "\nWarping=" << config.isWarpingEnabled();

        *os << "\nAntialiasing method=" << config.getAntialiasingMethod();
        *os << "\nAntialiasing samples=" << config.getAntialiasingSampleCount();

        *os << "\nWindowWidth=" << config.getDesiredWindowWidth();
        *os << "\nWindowHeight=" << config.getDesiredWindowHeight();
        *os << "\nWindowPositionX=" << config.getWindowPositionX();
        *os << "\nWindowPositionY=" << config.getWindowPositionY();

        const Vector3 camPos = config.getCameraPosition();
        *os << "\nCamera position x=" << camPos.x << " y=" << camPos.y << " z=" << camPos.z;
        const Vector3 camRot = config.getCameraRotation();
        *os << "\nCamera rotation x=" << camRot.x << " y=" << camRot.y << " z=" << camRot.z;

        const ProjectionParams& projParams = config.getProjectionParams();
        *os << "\nProjectionType=" << projParams.getProjectionType();

        *os << "\nLeftPlane=" << projParams.leftPlane;
        *os << "\nRightPlane=" << projParams.rightPlane;
        *os << "\nBottomPlane=" << projParams.bottomPlane;
        *os << "\nTopPlane=" << projParams.topPlane;
        *os << "\nNearPlane=" << projParams.nearPlane;
        *os << "\nFarPlane=" << projParams.farPlane;
    }

    void PrintTo(const RendererConfig& config, ::std::ostream* os)
    {
        *os << "SCEnabled=" << config.getSystemCompositorControlEnabled();
        *os << "\nWaylandSocketEmbedded=" << config.getWaylandSocketEmbedded().c_str();
    }
}
