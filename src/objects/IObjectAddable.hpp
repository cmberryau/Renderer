//
//  IObjectAddable.hpp
//  Renderer
//
//  Created by Christopher Berry on 28/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _i_object_addable_h
#define _i_object_addable_h

namespace Renderer
{
    class Object;
    
    class IObjectAddable
    {
        public:
			virtual ~IObjectAddable(){};
			virtual void Update(Object * parent_object){};
			void Added(Object * parent_object);
        
        protected:
            explicit IObjectAddable() : _parent_object(nullptr){}
        
            Object * _parent_object;
    };
}

#endif // _i_object_addable_h