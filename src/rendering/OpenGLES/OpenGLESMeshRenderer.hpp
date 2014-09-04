//
//  OpenGLESMeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 04/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#ifndef _opengles_mesh_renderer_h
#define _opengles_mesh_renderer_h

#include "rendering/MeshRenderer.hpp"
#include "rendering/Camera.hpp"
#include "rendering/OpenGLES/OpenGLShader.hpp"

#ifdef EMSCRIPTEN
#include <SDL/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengles2.h>
#endif

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

			}

			void GenerateArrays(MeshType<T> * mesh)
			{

			}

            void CreateShader(MeshType<float> * mesh)
            {                

            }
        
			void Draw(ObjectType<float> * parent_object)
			{
                
			}

			void Draw(ObjectType<double> * parent_object)
            {

            }

			~OpenGLESMeshRendererType<T>()
            {
                
            }

            OpenGLESMeshRendererType<T>(RenderingContextType<T> * rendering_context) : MeshRendererType<T>(rendering_context)
            {
                
            }
        
		protected:
        
            GLuint _vertex_array_objects[1];
			GLuint _vertex_element_buffer[1];
            GLuint _vertex_buffer_objects[1];
        
            GLint _model_matrix_uniform;
            GLint _projection_matrix_uniform;
	};
    
    typedef OpenGLESMeshRendererType<float> OpenGLESMeshRenderer;
    typedef OpenGLESMeshRendererType<double> OpenGLESMeshRendererd;
}

#endif // _opengles_mesh_renderer_h

#endif // EMSCRIPTEN