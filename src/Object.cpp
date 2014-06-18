//
//  Object.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Object.h"

namespace Renderer
{
    Object::Object()
    {
        this->transform = new Transform();
    }
    
    Object::~Object()
    {
        delete this->transform;
    }
}