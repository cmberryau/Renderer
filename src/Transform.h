//
//  Transform.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _transform_h
#define _transform_h

#include "Vector3.h"

namespace Renderer
{
    class Transform
    {
        public:
            Vector3 * position;
            Vector3 * rotation;
            Vector3 * scale;
        
            Transform(Vector3 * position);
            Transform();
            ~Transform();
    };
}

#endif // #ifndef _transform_h
