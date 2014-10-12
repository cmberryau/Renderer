//
//  IObjectAddable.hpp
//  Renderer
//
//  Created by Christopher Berry on 28/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _i_object_addable_h
#define _i_object_addable_h

#include "objects/Object.hpp"

#include <memory>

namespace Renderer
{    
    class ObjectAddable
    {
        public:
			virtual ~ObjectAddable(){};
        
            // called on each frame
			virtual void Update(Object & parent_object){};
        
            // called when the ObjectAddable is
            virtual void Added(Object & parent_object){};
        
        protected:
			explicit ObjectAddable(Object & parent);
			const Object & Parent() const;

		private:
			explicit ObjectAddable();

			Object & _parent_object;
    };
}

#endif // _i_object_addable_h