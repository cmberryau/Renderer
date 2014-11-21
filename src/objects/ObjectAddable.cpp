//
//  ObjectAddable.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ObjectAddable.hpp"

namespace Renderer
{
	ObjectAddable::ObjectAddable()
	{

	}

	void ObjectAddable::Added(Object * parent_object)
	{
		_parent_object = parent_object;
	}

    Object & ObjectAddable::Parent()
	{
		return *_parent_object;
	}
}