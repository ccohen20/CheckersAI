all: BoardImg

FLAGS = -g -Wall -Wextra -g

OGL = -framework OpenGL -framework GLUT -framework Carbon

BoardImg: BoardImg.cpp BoardImg.h
	g++ $(FLAGS) $(OGL) -o BoardImg BoardImg.cpp