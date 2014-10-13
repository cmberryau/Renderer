CC=emcc

ifeq ($(OS),Windows_NT)
	LIBRARIES=..\emscripten\libs\libSDL2.a
	LDFLAGS=-s DEMANGLE_SUPPORT=1 --embed-file shaders\GLSLES\defaultes.vert --embed-file shaders\GLSLES\defaultes.frag --embed-file cube.obj --embed-file cube_n.obj --embed-file sphere.obj --embed-file cone.obj --embed-file bunny.obj --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I..\src
	SOURCE_DIR=..\src
	SOURCES=$(wildcard *.cpp) application\Application.cpp \
	application\ApplicationFactory.cpp \
	events\EventListener.cpp \
	geometry\Mesh.cpp \
	geometry\MeshFactory.cpp \
	math\Mathf.cpp \
	math\Transform.cpp \
	objects\ObjectAddable.cpp \
	objects\Object.cpp \
	rendering\Camera.cpp \
	rendering\Material.cpp \
	rendering\MeshRenderer.cpp \
	rendering\RenderingContext.cpp \
	rendering\ShaderFactory.cpp \
	rendering\OpenGLES\OpenGLESCommon.cpp \
	rendering\OpenGLES\OpenGLESMeshRenderer.cpp \
	rendering\OpenGLES\OpenGLESRenderingContext.cpp \
	rendering\OpenGLES\OpenGLESShader.cpp \
	scene\Scene.cpp \
	utility\IO.cpp \
	utility\Util.cpp \
	windowing\Window.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
else
	LIBRARIES=../emscripten/libs/libSDL2.a
	LDFLAGS=-s DEMANGLE_SUPPORT=1 --embed-file shaders/GLSLES/defaultes.vert --embed-file shaders/GLSLES/defaultes.frag --embed-file cube.obj --embed-file cube_n.obj --embed-file sphere.obj --embed-file cone.obj --embed-file bunny.obj --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I../src
	SOURCE_DIR=../src
	SOURCES=$(wildcard *.cpp) application/Application.cpp \
	application/ApplicationFactory.cpp \
	events/EventListener.cpp \
	geometry/Mesh.cpp \
	geometry/MeshFactory.cpp \
	math/Mathf.cpp \
	math/Transform.cpp \
	objects/ObjectAddable.cpp \
	objects/Object.cpp \
	rendering/Camera.cpp \
	rendering/Material.cpp \
	rendering/MeshRenderer.cpp \
	rendering/RenderingContext.cpp \
	rendering/ShaderFactory.cpp \
	rendering/OpenGLES/OpenGLESCommon.cpp \
	rendering/OpenGLES/OpenGLESMeshRenderer.cpp \
	rendering/OpenGLES/OpenGLESRenderingContext.cpp \
	rendering/OpenGLES/OpenGLESShader.cpp \
	scene/Scene.cpp \
	utility/IO.cpp \
	utility/Util.cpp \
	windowing/Window.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
endif
	EXECUTABLE=renderer.html

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

%.bc: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
		del *.bc *.html *.js *.map *.mem
else
		rm *.bc *.html *.js *.map *.mem
endif