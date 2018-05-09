all: Board.o Board

FLAGS = -g -Wall -Wextra -g

OGL = -framework OpenGL -framework GLUT -framework Carbon

BoardImg: BoardImg.cpp BoardImg.hpp
	g++ $(FLAGS) $(OGL) -o BoardImg BoardImg.cpp

Board.o: Board.cpp Board.hpp Global.hpp
	g++ $(FLAGS) -c Board.cpp

Board: Board.o
	g++ $(FLAGS) -o Board Board.o

Test: Board.o
	g++ $(FLAGS) -o Test Test.cpp Board.o

clean:
	rm Test BoardImg Board Board.o