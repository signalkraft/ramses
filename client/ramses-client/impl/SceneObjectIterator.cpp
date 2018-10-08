//  -------------------------------------------------------------------------
//  Copyright (C) 2015 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "ramses-client-api/SceneObjectIterator.h"
#include "ramses-client-api/Scene.h"
#include "ObjectIteratorImpl.h"
#include "SceneImpl.h"

namespace ramses
{
    SceneObjectIterator::SceneObjectIterator(const Scene& scene, ERamsesObjectType objectType)
        : impl(new ObjectIteratorImpl(scene.impl.getObjectRegistry(), objectType))
    {
    }

    SceneObjectIterator::~SceneObjectIterator()
    {
        delete impl;
    }

    RamsesObject* SceneObjectIterator::getNext()
    {
        return impl->getNext();
    }
}
