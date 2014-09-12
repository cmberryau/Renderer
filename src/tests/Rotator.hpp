//
//  Rotator
//  Renderer
//
//  Created by Christopher Berry on 28/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _rotator_h
#define _rotator_h

#include "objects/Object.hpp"

namespace Renderer
{
    class Rotator : public IObjectAddable
    {
        public:
            Rotator(){}
            
            void Update(Object * parent_object)
            {
                parent_object->LocalTransform()->Rotate(1.0f, 1.0f, 0.0f);
            }
    };
}

#endif // _rotator_h