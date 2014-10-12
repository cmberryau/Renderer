//
//  IObjectAddable.hpp
//  Renderer
//
//  Created by Christopher Berry on 28/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _i_object_addable_h
#define _i_object_addable_h

#include <memory>

namespace Renderer
{
    class Object;
    
    class ObjectAddable
    {
        public:
			virtual ~ObjectAddable(){};
        
            // called on each frame
			virtual void Update(Object & parent_object){};
        
            // called when the ObjectAddable is
            virtual void Added(Object & parent_object){};
        
        protected:
            explicit ObjectAddable();
    };
}

#endif // _i_object_addable_h