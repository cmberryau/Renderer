//
//  Object.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _object_h
#define _object_h

#include "Transform.h"

namespace Renderer
{
    class Object
    {
    public:
        Transform * Transform;
        
        Object();
        ~Object();
    };
}

#endif // #ifndef _object_h