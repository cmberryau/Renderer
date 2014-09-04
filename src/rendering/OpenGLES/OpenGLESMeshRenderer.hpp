//
//  OpenGLESMeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 04/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengles_mesh_renderer_h
#define _opengles_mesh_renderer_h

#include "rendering/MeshRenderer.hpp"
#include "rendering/Camera.hpp"
#include "rendering/OpenGLES/OpenGLESShader.hpp"

#include <SDL2/SDL_opengles2.h>

namespace Renderer
{
    template <typename T>
	class OpenGLESMeshRendererType : public MeshRendererType<T>
	{
		public:
			static OpenGLESMeshRendererType<T> * Create(RenderingContext * rendering_context)
            {
                return new OpenGLESMeshRendererType<T>(rendering_context);
            }
        
			void SetMesh(MeshType<T> * mesh)
			{
				if (mesh == nullptr)
				{
					throw std::exception();
				}

				mesh->Validate();
				this->_mesh = mesh;

				this->CreateShader(mesh);				
			}

            void CreateShader(MeshType<float> * mesh)
            {                

            }
        
			void Draw(ObjectType<float> * parent_object)
			{
				if (this->_mesh == nullptr)
				{
					throw std::exception();
				}

				this->_material->Use();

				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, _mesh->Vertices());
				glEnableVertexAttribArray(0);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}

			~OpenGLESMeshRendererType<T>()
            {
                
            }

            OpenGLESMeshRendererType<T>(RenderingContextType<T> * rendering_context) : MeshRendererType<T>(rendering_context)
            {
                
            }
	};
    
    typedef OpenGLESMeshRendererType<float> OpenGLESMeshRenderer;
    typedef OpenGLESMeshRendererType<double> OpenGLESMeshRendererd;
}

#endif // _opengles_mesh_renderer_h