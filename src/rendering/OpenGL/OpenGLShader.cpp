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
        
    }
    
    OpenGLShader::OpenGLShader(const char * vertex_source,
                               const char * geometry_source,
                               const char * fragment_source)
    : _vertex_source(vertex_source),
      _geometry_source(geometry_source),
      _fragment_source(fragment_source)
    {
        
    }
}