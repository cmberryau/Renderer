CC=emcc

ifeq ($(OS),Windows_NT)
	ASSET_DIR=..\assets
	SHADERS_DIR=..\src\shaders
	SOURCE_DIR=..\src
	LIBRARIES=..\lib\emscripten\sdl2\current\libs\libSDL2.a
	LDFLAGS=-s DEMANGLE_SUPPORT=1 --embed-file $(ASSET_DIR) --embed-file $(SHADERS_DIR) --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I ..\src -I ../lib/emscripten/sdl2/current/include
	SOURCES=$(wildcard *.cpp) \
	$(SOURCE_DIR)\main.cpp \
	$(SOURCE_DIR)\application\ApplicationXML.cpp \
	$(SOURCE_DIR)\application\Application.cpp \
	$(SOURCE_DIR)\application\ApplicationFactory.cpp \
	$(SOURCE_DIR)\application\EmscriptenApplication.cpp \
	$(SOURCE_DIR)\events\EventListener.cpp \
	$(SOURCE_DIR)\geometry\Mesh.cpp \
	$(SOURCE_DIR)\geometry\MeshFactory.cpp \
	$(SOURCE_DIR)\math\Mathf.cpp \
	$(SOURCE_DIR)\math\Transform.cpp \
	$(SOURCE_DIR)\objects\ObjectAddable.cpp \
	$(SOURCE_DIR)\objects\Object.cpp \
	$(SOURCE_DIR)\rendering\Camera.cpp \
	$(SOURCE_DIR)\rendering\Material.cpp \
	$(SOURCE_DIR)\rendering\MeshRenderer.cpp \
	$(SOURCE_DIR)\rendering\RenderingContext.cpp \
	$(SOURCE_DIR)\rendering\ShaderFactory.cpp \
	$(SOURCE_DIR)\rendering\OpenGLES\OpenGLESCommon.cpp \
	$(SOURCE_DIR)\rendering\OpenGLES\OpenGLESMeshRenderer.cpp \
	$(SOURCE_DIR)\rendering\OpenGLES\OpenGLESRenderingContext.cpp \
	$(SOURCE_DIR)\rendering\OpenGLES\OpenGLESShader.cpp \
	$(SOURCE_DIR)\scene\Scene.cpp \
	$(SOURCE_DIR)\utility\IO.cpp \
	$(SOURCE_DIR)\utility\Util.cpp \
	$(SOURCE_DIR)\tests\Spinner.cpp \
	$(SOURCE_DIR)\windowing\Window.cpp
	OBJECTS=$(SOURCES:.cpp=.bc)
else
	ASSET_DIR=../assets
	SHADERS_DIR=../src/shaders
	SOURCE_DIR=../src
	LIBRARIES=../lib/emscripten/sdl2/current/libs/libSDL2.a
	LDFLAGS=-s DEMANGLE_SUPPORT=1 --embed-file $(ASSET_DIR) --embed-file $(SHADERS_DIR) --memory-init-file 0
	CFLAGS=-O2 -std=c++11 -I ../src -I ../lib/emscripten/sdl2/current/include
	SOURCES=$(wildcard *.cpp) \
	$(SOURCE_DIR)/main.cpp \
	$(SOURCE_DIR)/application/ApplicationXML.cpp \
	$(SOURCE_DIR)/application/Application.cpp \
	$(SOURCE_DIR)/application/ApplicationXML.cpp \
	$(SOURCE_DIR)/application/ApplicationFactory.cpp \
	$(SOURCE_DIR)/application/EmscriptenApplication.cpp \
	$(SOURCE_DIR)/events/EventListener.cpp \
	$(SOURCE_DIR)/geometry/Mesh.cpp \
	$(SOURCE_DIR)/geometry/MeshFactory.cpp \
	$(SOURCE_DIR)/math/Mathf.cpp \
	$(SOURCE_DIR)/math/Transform.cpp \
	$(SOURCE_DIR)/objects/ObjectAddable.cpp \
	$(SOURCE_DIR)/objects/ObjectFactory.cpp \
	$(SOURCE_DIR)/objects/Object.cpp \
	$(SOURCE_DIR)/rendering/Camera.cpp \
	$(SOURCE_DIR)/rendering/Material.cpp \
	$(SOURCE_DIR)/rendering/MeshRenderer.cpp \
	$(SOURCE_DIR)/rendering/RenderingContext.cpp \
	$(SOURCE_DIR)/rendering/ShaderFactory.cpp \
	$(SOURCE_DIR)/rendering/OpenGLES/OpenGLESCommon.cpp \
	$(SOURCE_DIR)/rendering/OpenGLES/OpenGLESMeshRenderer.cpp \
	$(SOURCE_DIR)/rendering/OpenGLES/OpenGLESRenderingContext.cpp \
	$(SOURCE_DIR)/rendering/OpenGLES/OpenGLESShader.cpp \
	$(SOURCE_DIR)/scene/Scene.cpp \
	$(SOURCE_DIR)/utility/IO.cpp \
	$(SOURCE_DIR)/utility/Util.cpp \
	$(SOURCE_DIR)/tests/Spinner.cpp \
	$(SOURCE_DIR)/windowing/Window.cpp
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
		del ..\*\*.bc *.html *.js *.map *.mem
else
		rm ../*/*.bc *.html *.js *.map *.mem
endif