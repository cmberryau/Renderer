//
//  OpenGLShader.cpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLShader.hpp"

namespace Renderer
{
    void OpenGLShader::Use()
    {
        glUseProgram(_program);
    }
    
    OpenGLShader::OpenGLShader(GLuint program)
    {
        _program = program;
    }
}