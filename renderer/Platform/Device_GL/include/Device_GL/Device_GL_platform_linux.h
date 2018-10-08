//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_DEVICE_GL_PLATFORM_LINUX_H
#define RAMSES_DEVICE_GL_PLATFORM_LINUX_H

#define LOAD_ALL_API_PROCS            // does nothing for linux - api procs are already defined in the GL library
#define DECLARE_ALL_API_PROCS         // does nothing for linux - api procs are already declared in the GL headers
#define DEFINE_ALL_API_PROCS          // does nothing for linux - api procs are already defined in the GL headers

// extension procs, however, need to be declared and defined
#define DECLARE_EXTENSION_PROC(TYPE, NAME) extern TYPE NAME;
#define DEFINE_EXTENSION_PROC(TYPE, NAME) TYPE NAME = 0;

#endif
