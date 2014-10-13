//
//  IObjectAddable.cpp
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

	void ObjectAddable::Added(std::shared_ptr<Object> parent_object)
	{
		_parent_object = parent_object;
	}

	const Object & ObjectAddable::Parent() const
	{
		return *_parent_object;
	}
}