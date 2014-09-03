CC=emcc
LDFLAGS=
CFLAGS=-02 -std=c++11 -I..\src
SOURCE_DIR=..\src
SOURCES=$(wildcard *.cpp) events\EventListener.cpp geometry\MeshFactory.cpp rendering\Material.cpp rendering\ShaderFactory.cpp rendering\OpenGL\OpenGLShader.cpp windowing\Window.cpp utility\IO.cpp
OBJECTS=$(SOURCES:.cpp=.bc)
EXECUTABLE=renderer.html

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.bc: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	del *.bc