CC=emcc

ifeq ($(OS),Windows_NT)
	LIBRARIES=..\emscripten\libs\libSDL2.a
	LDFLAGS=-s DEMANGLE_SUPPORT=1 --embed-file shaders\GLSLES\defaultes.vert --embed-file shaders\GLSLES\defaultes.frag --embed-file cube.obj --embed-file cube_n.obj --embed-file sphere.obj --embed-file cone.obj --embed-file bunny.obj --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I..\src
	SOURCE_DIR=..\src
	SOURCES=$(wildcard *.cpp) events\EventListener.cpp geometry\MeshFactory.cpp rendering\Material.cpp rendering\ShaderFactory.cpp rendering\OpenGL\OpenGLShader.cpp rendering\OpenGLES\OpenGLESShader.cpp windowing\Window.cpp scene\Scene.cpp utility\IO.cpp utility\util.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
else
	LIBRARIES=../emscripten/libs/libSDL2.a
	LDFLAGS=-s DEMANGLE_SUPPORT=1 --embed-file shaders/GLSLES/defaultes.vert --embed-file shaders/GLSLES/defaultes.frag --embed-file cube.obj --embed-file cube_n.obj --embed-file sphere.obj --embed-file cone.obj --embed-file bunny.obj --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I../src
	SOURCE_DIR=../src
	SOURCES=$(wildcard *.cpp) events/EventListener.cpp geometry/MeshFactory.cpp rendering/Material.cpp rendering/ShaderFactory.cpp rendering/OpenGL/OpenGLShader.cpp rendering/OpenGLES/OpenGLESShader.cpp windowing/Window.cpp scene/Scene.cpp utility/IO.cpp utility/util.cpp
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