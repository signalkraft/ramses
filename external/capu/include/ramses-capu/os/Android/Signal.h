/*
 * Copyright (C) 2015 BMW Car IT GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RAMSES_CAPU_ANDROID_SIGNAL_H
#define RAMSES_CAPU_ANDROID_SIGNAL_H

#include <ramses-capu/os/Posix/Signal.h>

namespace ramses_capu
{
    namespace os
    {
        class Signal: private ramses_capu::posix::Signal
        {
        public:
            using ramses_capu::posix::Signal::signal;
            using ramses_capu::posix::Signal::raise;
        };
    }
}
#endif // RAMSES_CAPU_ANDROID_SIGNAL_H
