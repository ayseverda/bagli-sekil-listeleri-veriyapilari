all: derle bagla calistir

derle:
	g++ -I ./include -o ./lib/main.o -c ./src/main.cpp
	g++ -I ./include -o ./lib/RandomGenerator.o -c ./src/RandomGenerator.cpp
	g++ -I ./include -o ./lib/Persistence.o -c ./src/Persistence.cpp
	g++ -I ./include -o ./lib/Rectangle.o -c ./src/Rectangle.cpp
	g++ -I ./include -o ./lib/Screen.o -c ./src/Screen.cpp
	g++ -I ./include -o ./lib/Star.o -c ./src/Star.cpp
	g++ -I ./include -o ./lib/ControlNode.o -c ./src/ControlNode.cpp
	g++ -I ./include -o ./lib/ShapeNode.o -c ./src/ShapeNode.cpp
	g++ -I ./include -o ./lib/Triangle.o -c ./src/Triangle.cpp
	g++ -I ./include -o ./lib/ControlList.o -c ./src/ControlList.cpp
	g++ -I ./include -o ./lib/Shape.o -c ./src/Shape.cpp

bagla:
	g++ -I ./include -o ./bin/sekil_listesi.exe \
		./lib/main.o \
		./lib/RandomGenerator.o \
		./lib/Persistence.o \
		./lib/Rectangle.o \
		./lib/Screen.o \
		./lib/Star.o \
		./lib/ControlNode.o \
		./lib/ShapeNode.o \
		./lib/Triangle.o \
		./lib/ControlList.o \
		./lib/Shape.o

calistir:
	./bin/sekil_listesi.exe

clean:
	if exist lib\*.o del /Q lib\*.o
	if exist bin\sekil_listesi.exe del /Q bin\sekil_listesi.exe

