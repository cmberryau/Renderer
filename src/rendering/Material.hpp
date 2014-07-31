//
//  Material.hpp
//  Renderer
//
//  Created by Christopher Berry on 31/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _material_h
#define _material_h

namespace Renderer
{
    class Material
    {
        public:        
            virtual ~Material(){}
        
        protected:
            Material(){};
    };
}

#endif // _material_h