//
//  OpenGLESRenderingContext.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "OpenGLESRenderingContext.hpp"
#include "utility/IO.hpp"

namespace Renderer
{
	OpenGLESRenderingContext::OpenGLESRenderingContext(const Window & window)
	{
		SDL_GLContext sdl_gl_context = SDL_GL_CreateContext(window.GetSDLWindow());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		std::string vertex_shader_path("src/shaders/GLSLES/defaultes.vert");
		std::string fragment_shader_path("src/shaders/GLSLES/defaultes.frag");
		std::string vertex_shader_source = IO::ReadFile(vertex_shader_path);
		std::string fragment_shader_source = IO::ReadFile(fragment_shader_path);
		_default_shader = CreateShader(vertex_shader_source, fragment_shader_source);
		_default_material = std::make_shared<Material>(_default_shader);
    }

	void OpenGLESRenderingContext::BeginScene() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLESRenderingContext::EndScene() const
	{
		
	}

	std::unique_ptr<MeshRenderer> OpenGLESRenderingContext::CreateMeshRenderer() const
	{
		return std::unique_ptr<MeshRenderer>(new OpenGLESMeshRenderer());
	}

	std::shared_ptr<Material> OpenGLESRenderingContext::DefaultMaterial() const
	{
		return _default_material;
	}

	std::shared_ptr<Shader> OpenGLESRenderingContext::CreateShader(std::string & vertex_source,
																   std::string & fragment_source) const
	{
		std::shared_ptr<Shader> shader(new OpenGLESShader());
		shader->Compile(vertex_source, fragment_source);

		return shader;
	}

	std::shared_ptr<Shader> OpenGLESRenderingContext::CreateShader(std::string & vertex_source,
																   std::string & geometry_source,
																   std::string & fragment_source) const
	{
		throw std::runtime_error(std::string("OpenGL ES does not support Geometry shaders"));

		return nullptr;
	}
}

#endif // EMSCRIPTEN