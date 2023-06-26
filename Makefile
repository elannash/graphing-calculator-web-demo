PATH_TO_SFML_HEADERS = /opt/homebrew/opt/sfml/include 	# Update this to your SFML include path
PATH_TO_SFML_LIBS = /opt/homebrew/opt/sfml/lib 			# Update this to your SFML lib path

CXX = g++
CXXFLAGS = -std=c++11 -I$(PATH_TO_SFML_HEADERS)
LINKER_FLAGS = -L$(PATH_TO_SFML_LIBS) -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DIR = build
BIN_DIR = build
SRC_DIR = includes

SRCS = main.cpp $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
EXEC = $(BIN_DIR)/main

all: $(EXEC)

$(EXEC): 
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRCS) $(LINKER_FLAGS) 

.PHONY: all