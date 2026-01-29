CXX = g++
CXXFLAGS = -Wall -std=c++17

INCLUDES = -I./glad/include

SRC = main.cpp Mesh.cpp Shader.cpp Model.cpp glad/glad.c

LIBS = -lglfw -ldl -lGL -lm -lassimp

OUT = main

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)
