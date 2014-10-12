//
//  Object.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _object_h
#define _object_h

#include "math/Transform.hpp"

#include <vector>

namespace Renderer
{
    class Object
    {
        public:
			explicit Object(){};
			~Object(){};
			
			const Transform & LocalTransform() const;

			void Update();        
			void Draw() const;

		private:
            Transform _transform;
    };
}

#endif // _object_h