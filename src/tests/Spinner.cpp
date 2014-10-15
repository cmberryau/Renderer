//
//  Spinner.cpp
//  Renderer
//
//  Created by Christopher Berry on 15/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Spinner.hpp"
#include "objects/Object.hpp"

namespace Renderer
{
    void Spinner::Update()
    {
        Parent().LocalTransform().Rotate(1.0f, 1.0f, 0.0f);
    }
}