//
//  Transform.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Transform.h"

namespace Renderer
{
    Transform::Transform(Vector3 * position)
    {
        this->position = position;
        this->rotation = new Vector3(0.0f, 0.0f, 0.0f);
        this->scale = new Vector3(1.0f, 1.0f, 1.0f);
    }

    Transform::Transform()
    {
        this->position = new Vector3(0.0f, 0.0f, 0.0f);
        this->rotation = new Vector3(0.0f, 0.0f, 0.0f);
        this->scale = new Vector3(1.0f, 1.0f, 1.0f);
    }

    Transform::~Transform()
    {
        delete this->position;
        delete this->rotation;
        delete this->scale;
    }
}