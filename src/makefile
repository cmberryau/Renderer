CC=emcc

ifeq ($(OS),Windows_NT)
	LIBRARIES=..\emscripten\libs\libSDL2.a
	LDFLAGS=--embed-file shaders\GLSLES\default.vert --embed-file shaders\GLSLES\default.frag --embed-file cube.obj --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I..\src
	SOURCE_DIR=..\src
	SOURCES=$(wildcard *.cpp) events\EventListener.cpp geometry\MeshFactory.cpp rendering\Material.cpp rendering\ShaderFactory.cpp rendering\OpenGL\OpenGLShader.cpp rendering\OpenGLES\OpenGLESShader.cpp windowing\Window.cpp utility\IO.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
else
	LIBRARIES=../emscripten/libs/libSDL2.a
	LDFLAGS=--embed-file shaders/GLSLES/default.vert --embed-file shaders/GLSLES/default.frag --embed-file cube.obj --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I../src
	SOURCE_DIR=../src
	SOURCES=$(wildcard *.cpp) events/EventListener.cpp geometry/MeshFactory.cpp rendering/Material.cpp rendering/ShaderFactory.cpp rendering/OpenGL/OpenGLShader.cpp rendering/OpenGLES/OpenGLESShader.cpp windowing/Window.cpp utility/IO.cpp 
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