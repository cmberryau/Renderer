//
//  MeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_renderer_h
#define _mesh_renderer_h

#include "geometry/Mesh.hpp"
#include "rendering/Material.hpp"

#include <memory>

namespace Renderer
{	
	class Object;
    class Scene;

	class MeshRenderer
	{
		public:
			// caches the mesh and prepares it for drawing
            virtual void AddMesh(std::shared_ptr<Mesh> mesh_ptr) = 0;
		
			// sets the material
            void AddMaterial(std::shared_ptr<Material> material_ptr);

			// draws the mesh
            virtual void Draw(Object & parent_object, const Scene & scene) const = 0;
		
			virtual ~MeshRenderer(){};

		protected:
            explicit MeshRenderer();
        
			const Mesh & GetMesh() const;
            const Material & GetMaterial() const;
        
            bool HasMesh() const;
            bool HasMaterial() const;
        
            void SetMesh(const std::shared_ptr<Mesh> & mesh_ptr);
            void SetMaterial(const std::shared_ptr<Material> & material_ptr);
        
        private:
            std::shared_ptr<Mesh> _mesh_ptr;
            std::shared_ptr<Material> _material_ptr;
	};
}

#endif // _mesh_renderer_h