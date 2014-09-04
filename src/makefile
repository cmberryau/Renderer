CC=emcc

ifeq ($(OS),Windows_NT)
	LDFLAGS=--embed-file shaders\GLSLES\default.vert --embed-file shaders\GLSLES\default.frag --embed-file bunny.obj
	CFLAGS=-02 -std=c++11 -I..\src
	SOURCE_DIR=..\src
	SOURCES=$(wildcard *.cpp) events\EventListener.cpp geometry\MeshFactory.cpp rendering\Material.cpp rendering\ShaderFactory.cpp rendering\OpenGL\OpenGLShader.cpp windowing\Window.cpp utility\IO.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
else
	LDFLAGS=--embed-file shaders/GLSL/default.vert --embed-file shaders/GLSL/default.frag --embed-file bunny.obj
	CFLAGS=-02 -std=c++11 -I../src
	SOURCE_DIR=../src
	SOURCES=$(wildcard *.cpp) events/EventListener.cpp geometry/MeshFactory.cpp rendering/Material.cpp rendering/ShaderFactory.cpp rendering/OpenGL/OpenGLShader.cpp windowing/Window.cpp utility/IO.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
endif
	EXECUTABLE=renderer.html

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.bc: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
		del *.bc *.html *.js *.map
else
		rm *.bc *.html *.js *.map
endif