//
//  Spinner.hpp
//  Renderer
//
//  Created by Christopher Berry on 15/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _spinner_h
#define _spinner_h

#include "objects/ObjectAddable.hpp"

namespace Renderer
{
    class Spinner : public ObjectAddable
    {
        public:
            explicit Spinner(){};
            ~Spinner(){};
        
            void Update() override;
    };
}

#endif