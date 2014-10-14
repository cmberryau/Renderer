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
			virtual void Update(){};
			
			// object will call this when ObjectAddable is added
            virtual void Added(Object * parent_object) final;
        
        protected:
			explicit ObjectAddable();
			const Object & Parent() const;

		private:
			Object * _parent_object;
    };
}

#endif // _i_object_addable_h