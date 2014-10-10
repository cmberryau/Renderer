//
//  MeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_renderer_h
#define _mesh_renderer_h

#include "rendering/RenderingContext.hpp"
#include "geometry/Mesh.hpp"
#include "objects/Object.hpp"
#include "rendering/Material.hpp"

#include <memory>

namespace Renderer
{	
	class Object;

	class MeshRenderer
	{
		public:
			// caches the mesh and prepares it for drawing
            virtual void AddMesh(const std::shared_ptr<Mesh> & mesh_ptr) = 0;
		
			// sets the material
            void AddMaterial(const std::shared_ptr<Material> & material_ptr);

			// draws the mesh
            virtual void Draw(Object & parent_object) const = 0;
		
			virtual ~MeshRenderer(){};

		protected:
            explicit MeshRenderer(const std::shared_ptr<RenderingContext> & rendering_context_ptr);
        
			const Mesh & GetMesh() const;
            const Material & GetMaterial() const;
            const RenderingContext & GetRenderingContext() const;
        
            bool HasMesh() const;
            bool HasMaterial() const;
            bool HasRenderingContext() const;
        
            void SetMesh(const std::shared_ptr<Mesh> & mesh_ptr);
            void SetMaterial(const std::shared_ptr<Material> & material_ptr);
            void SetRenderingContext(const std::shared_ptr<RenderingContext> & rendering_context_ptr);
        
        private:
            std::shared_ptr<Mesh> _mesh_ptr;
            std::shared_ptr<Material> _material_ptr;
            std::shared_ptr<RenderingContext> _rendering_context_ptr;
	};
}

#endif // _mesh_renderer_h