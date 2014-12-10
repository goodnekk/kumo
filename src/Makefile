objects = $(bin)/main.o $(bin)/lexer.o $(bin)/token.o $(bin)/parser.o $(bin)/vm.o $(bin)/generator.o

bin = ../bin

$(bin)/kumo: $(objects)
	g++ $(objects) -o $(bin)/kumo
	$(bin)/kumo

$(bin)/main.o: main.cpp
	g++ -c main.cpp -o $(bin)/main.o

$(bin)/lexer.o: lexer.cpp
	g++ -c lexer.cpp -o $(bin)/lexer.o

$(bin)/token.o: token.cpp
	g++ -c token.cpp -o $(bin)/token.o

$(bin)/parser.o: parser.cpp
	g++ -c parser.cpp -o $(bin)/parser.o

$(bin)/vm.o: vm.cpp
	g++ -c vm.cpp -o $(bin)/vm.o

$(bin)/generator.o: generator.cpp
	g++ -c generator.cpp -o $(bin)/generator.o
