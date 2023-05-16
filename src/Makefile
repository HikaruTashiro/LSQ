EXE = App
IMGUI_DIR = ./imgui
SOURCES = App.cpp lsq.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/implot_items.cpp $(IMGUI_DIR)/implot.cpp
SOURCES += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
SOURCES += $(IMGUI_DIR)/imgui_stdlib.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL -lGLEW

CXXFLAGS = -std=c++11 -I$(IMGUI_DIR)
CXXFLAGS += -g -Wall -Wformat -pthread
LIBS =

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
		LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
		CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
		LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += -L$(shell pwd)
	CXXFLAGS += `pkg-config --cflags glfw3`
		CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(RENDER)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<
	
%.o:$(IMGUI_DIR)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(STBI)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
		@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
		$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
		rm -f $(EXE) $(OBJS)
