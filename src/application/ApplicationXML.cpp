//
//  ApplicationXML.cpp
//  Renderer
//
//  Created by Christopher Berry on 09/11/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ApplicationXML.hpp"

namespace Renderer
{
    const std::string ApplicationXML::kApplicationTag = "Application";
    const std::string ApplicationXML::kSceneTag = "Scene";
    const std::string ApplicationXML::kObjectTag = "Object";
    const std::string ApplicationXML::kMeshTag = "Mesh";
    const std::string ApplicationXML::kTransformTag = "Transform";
    const std::string ApplicationXML::kTranslationTag = "Translation";
    const std::string ApplicationXML::kRotationTag = "Rotation";
    const std::string ApplicationXML::kScaleTag = "Scale";
    const std::string ApplicationXML::kPathTag = "Path";
    const std::string ApplicationXML::kNameTag = "Name";
    const std::string ApplicationXML::kXTag = "x";
    const std::string ApplicationXML::kYTag = "y";
    const std::string ApplicationXML::kZTag = "z";
    const std::string ApplicationXML::kCameraTag = "Camera";
    
    const std::string ApplicationXML::kNameAttribute = "name";
    const std::string ApplicationXML::kPathAttribute = "path";
}