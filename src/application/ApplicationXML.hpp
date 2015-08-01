//
//  ApplicationXML.hpp
//  Renderer
//
//  Created by Christopher Berry on 09/11/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _application_xml_h
#define _application_xml_h

#include <string>

namespace Renderer
{
    class ApplicationXML
    {
        public:
            static const std::string kApplicationTag;
            static const std::string kSceneTag;
            static const std::string kObjectTag;
            static const std::string kMeshTag;
            static const std::string kTransformTag;
			static const std::string kPositionTag;
            static const std::string kRotationTag;
            static const std::string kScaleTag;
            static const std::string kPathTag;
            static const std::string kNameTag;
            static const std::string kXTag;
            static const std::string kYTag;
            static const std::string kZTag;
            static const std::string kCameraTag;
        
            static const std::string kNameAttribute;
            static const std::string kPathAttribute;
        
        private:
            explicit ApplicationXML();
            ~ApplicationXML();
    };
}

#endif // _application_xml_h