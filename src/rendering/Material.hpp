//
//  Material.hpp
//  Renderer
//
//  Created by Christopher Berry on 31/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _material_h
#define _material_h

#include "Shader.hpp"

#include <memory>

namespace Renderer
{
    class Material
    {
        public:
			explicit Material(std::shared_ptr<class Shader> shader);
			~Material();

			void Use() const;
			const Shader & GetShader() const;
        
        private:
			std::shared_ptr<Shader> _shader;
    };
}

#endif // _material_h