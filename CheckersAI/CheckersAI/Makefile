all: Board.o AI.o BoardImg

FLAGS = -g -Wall -Wextra

OGL = -framework OpenGL -framework GLUT -framework Carbon

BoardImg: BoardImg.cpp BoardImg.hpp
	g++ $(FLAGS) $(OGL) -o BoardImg BoardImg.cpp Board.o AI.o

Board.o: Board.cpp Board.hpp Global.hpp
	g++ $(FLAGS) -c Board.cpp

AI.o: AI.cpp AI.hpp Board.o
	g++ $(FLAGS) -c AI.cpp

clean:
	rm BoardImg Board.o AI.o