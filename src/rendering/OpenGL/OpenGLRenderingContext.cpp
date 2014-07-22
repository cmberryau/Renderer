#include "OpenGLRenderingContext.h"
#include <stdio.h>

namespace Renderer
{
    const int OpenGLRenderingContext::kNumSupportedOpenGLVersions = 9;
    const int OpenGLRenderingContext::kSupportedOpenGLVersions[9][2] = {{4,4},{4,3},{4,2},
                                                                        {4,1},{4,0},{3,3},
                                                                        {3,2},{3,1},{3,0}};
    
    OpenGLRenderingContext * OpenGLRenderingContext::Create(Window * window,
															RenderingContextPrecision precision,
                                                            int major_version,
                                                            int minor_version)
    {
        if(window == nullptr)
            return nullptr;
        
        OpenGLRenderingContext * context = new OpenGLRenderingContext(OpenGLContextType,
																	  FloatPrecision);

        // ensure that the requested OpenGL version is supported
        int requested_major_version = major_version;
        int requested_minor_version = minor_version;
        
        int i = 0;
        for(i = 0; i<kNumSupportedOpenGLVersions; i++)
        {
            if(kSupportedOpenGLVersions[i][0] == requested_major_version &&
               kSupportedOpenGLVersions[i][1] == requested_minor_version)
            {
                break;
            }
        }
        
        // if it's not, just go from the top
        if(i == kNumSupportedOpenGLVersions)
        {
            requested_major_version = kSupportedOpenGLVersions[0][0];
            requested_minor_version = kSupportedOpenGLVersions[0][1];
        }
        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, requested_major_version);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, requested_minor_version);
        
        context->_sdl_gl_context = SDL_GL_CreateContext(window->_sdl_window);
        
        // run through the other supported versions if requested/top version fails
        i=0;
        while(context->_sdl_gl_context == nullptr && i < kNumSupportedOpenGLVersions)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, kSupportedOpenGLVersions[i][0]);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, kSupportedOpenGLVersions[i][1]);
            
            context->_sdl_gl_context = SDL_GL_CreateContext(window->_sdl_window);
            
            i++;
        }
        
        if (context->_sdl_gl_context == nullptr)
        {
            fprintf(stdout, "SDL_GL_CreateContext failed!\n");
            return nullptr;
        }
        
#ifdef _WIN32
        glewExperimental = GL_TRUE;
        
        if (glewInit() != GLEW_OK)
        {
            fprintf(stdout, "glewInit failed!\n");
            return nullptr;
        }
#endif
        
        GLint actual_major_version = -1;
        GLint actual_minor_version = -1;
        
        glGetIntegerv(GL_MAJOR_VERSION, &actual_major_version);
        glGetIntegerv(GL_MINOR_VERSION, &actual_minor_version);
        
        fprintf(stdout, "OpenGL version: %d.%d\n", actual_major_version, actual_minor_version);
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        return context;
    }
    
    OpenGLRenderingContext::~OpenGLRenderingContext()
    {
        SDL_GL_DeleteContext(_sdl_gl_context);
    }

	OpenGLRenderingContext::OpenGLRenderingContext(RenderingContextType context_type,
										           RenderingContextPrecision context_precision)
	: _sdl_gl_context(nullptr), RenderingContext(context_type, context_precision)
	{

	}

	RenderingContextPrecision OpenGLRenderingContext::Precision()
	{
		return _precision;
	}
    
    void OpenGLRenderingContext::BeginScene()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void OpenGLRenderingContext::EndScene()
    {
        glFlush();
    }
}