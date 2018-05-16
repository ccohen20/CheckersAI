all: Board.o AI.o search.o BoardImg AIFight

FLAGS = -g -Wall -Wextra

OGL = -framework OpenGL -framework GLUT -framework Carbon

BoardImg: BoardImg.cpp BoardImg.hpp
	g++ $(FLAGS) $(OGL) -o BoardImg BoardImg.cpp Board.o AI.o search.o

AIFight: AIFight.cpp AIFight.hpp
	g++ $(FLAGS) $(OGL) -o AIFight AIFight.cpp Board.o AI.o search.o

Board.o: Board.cpp Board.hpp Global.hpp
	g++ $(FLAGS) -c Board.cpp

AI.o: AI.cpp AI.hpp Board.o
	g++ $(FLAGS) -c AI.cpp

search.o: search.cpp search.hpp Board.hpp
	g++ $(FLAGS) -c search.cpp

clean:
	rm BoardImg Board.o AI.o search.o AIFight