//  -------------------------------------------------------------------------
//  Copyright (C) 2015 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_CONTEXTMOCK_H
#define RAMSES_CONTEXTMOCK_H

#include "renderer_common_gmock_header.h"
#include "gmock/gmock.h"
#include "RendererAPI/IContext.h"
#include "Platform_Base/DeviceResourceMapper.h"


namespace ramses_internal
{
    class ContextMock : public IContext
    {
    public:
        ContextMock();
        ~ContextMock() override;

        MOCK_METHOD0(init, Bool()); // Does not exist in IContext, needed for only for testing
        MOCK_METHOD0(getResources, DeviceResourceMapper&());
        MOCK_CONST_METHOD1(getProcAddress, void*(const Char*));
    };


    class ContextMockWithDestructor : public ContextMock
    {
    public:
        ContextMockWithDestructor();
        ~ContextMockWithDestructor() override;

        MOCK_METHOD0(Die, void());
    };
}

#endif
