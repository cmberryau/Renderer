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
    template <typename T>
    class ObjectType;
    
    template <typename T>
    class IObjectAddableType
    {
        public:
            virtual ~IObjectAddableType<T>(){}
            
            virtual void Update(ObjectType<T> * parent_object){};
        
            void Added(ObjectType<T> * parent_object)
            {
                _parent_object = parent_object;
            };
        
        protected:
            IObjectAddableType() : _parent_object(nullptr){}
        
            ObjectType<T> * _parent_object;
    };
    

    typedef IObjectAddableType<float> IObjectAddable;
    typedef IObjectAddableType<double> IObjectAddabled;
}

#endif // _i_object_addable_h