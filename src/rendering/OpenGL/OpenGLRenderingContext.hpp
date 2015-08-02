//
//  OpenGLRenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef EMSCRIPTEN

#ifndef _opengl_renderingcontext_h
#define _opengl_renderingcontext_h

#include "rendering/RenderingContext.hpp"
#include "rendering/OpenGL/OpenGLMeshRenderer.hpp"
#include "rendering/OpenGL/OpenGLCommon.hpp"
#include "windowing/Window.hpp"

#ifdef _DEBUG
#include <stdio.h>
#endif

#include <exception>

namespace Renderer
{
	class OpenGLRenderingContext : public RenderingContext
	{
		public:
			explicit OpenGLRenderingContext(const Window & window);
			explicit OpenGLRenderingContext(const Window & window,
											int desired_major_version,
											int desired_minor_version);
			virtual ~OpenGLRenderingContext() override {};
			
			virtual void BeginScene() const override;
			virtual void EndScene() const override;
			virtual std::unique_ptr<MeshRenderer> CreateMeshRenderer() const override;
			virtual std::shared_ptr<Material> DefaultMaterial() const override;
			virtual std::shared_ptr<Shader> CreateShader(std::string & vertex_source,
														 std::string & fragment_source) const override;
			virtual std::shared_ptr<Shader> CreateShader(std::string & vertex_source,
														 std::string & geometry_source,
														 std::string & fragment_source) const override;

		protected:
			bool IsReady() const;

		private:
			struct OpenGLVersion
			{
				explicit OpenGLVersion(int major, int minor) :
				_major(major), _minor(minor)
				{

				}

				bool operator == (const OpenGLVersion & rhs)
				{
					if (this->_major == rhs._major &&
						this->_minor == rhs._minor)
					{
						return true;
					}

					return false;
				}

				int _major;
				int _minor;
			};

			struct SDL_GLContextDeleter
			{
				void operator()(SDL_GLContext context)
				{
					SDL_GL_DeleteContext(context);
				}
			};

			void Init(const Window & window, int desired_major_version = 0, int desired_minor_version = 0);
			std::unique_ptr<SDL_GLContext, SDL_GLContextDeleter> 
			CreateSDLContext(const Window & window, const OpenGLVersion & version_to_create);

			OpenGLVersion CurrentOpenGLVersion() const;
			void SetupDefaultGLAttributes();

			std::vector<OpenGLVersion> _supported_opengl_versions;
			std::unique_ptr<SDL_GLContext, SDL_GLContextDeleter> _sdl_gl_context;

			std::shared_ptr<Shader> _default_shader;
			std::shared_ptr<Material> _default_material;
	};
}

#endif // _opengl_renderingcontext_h

#endif // !EMSCRIPTEN