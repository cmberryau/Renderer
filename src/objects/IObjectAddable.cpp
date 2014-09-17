//
//  IObjectAddable.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "IObjectAddable.hpp"

namespace Renderer
{
	void IObjectAddable::Added(Object * parent_object)
	{
		_parent_object = parent_object;
	}
}