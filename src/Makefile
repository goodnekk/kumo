objects = $(bin)/main.o $(bin)/lexer.o $(bin)/token.o $(bin)/program.o $(bin)/parser.o $(bin)/desugerer.o $(bin)/stack.o $(bin)/vm.o $(bin)/bytecodegenerator.o $(bin)/graphgenerator.o $(bin)/variable.o

bin = ../bin
flags = -g -std=c++11

$(bin)/kumo: $(objects)
	g++ $(objects) $(flags) -o $(bin)/kumo
	$(bin)/kumo ../examples/test.kmo

$(bin)/main.o: main.cpp
	g++ -c main.cpp $(flags) -o $(bin)/main.o

$(bin)/lexer.o: lexer.cpp
	g++ -c lexer.cpp $(flags) -o $(bin)/lexer.o

$(bin)/token.o: token.cpp
	g++ -c token.cpp $(flags) -o $(bin)/token.o

$(bin)/program.o: program.cpp
	g++ -c program.cpp $(flags) -o $(bin)/program.o

$(bin)/parser.o: parser.cpp
	g++ -c parser.cpp $(flags) -o $(bin)/parser.o

$(bin)/desugerer.o: desugerer.cpp
	g++ -c desugerer.cpp $(flags) -o $(bin)/desugerer.o

$(bin)/vm.o: vm.cpp
	g++ -c vm.cpp $(flags) -o $(bin)/vm.o

$(bin)/stack.o: stack.cpp
	g++ -c stack.cpp $(flags) -o $(bin)/stack.o

$(bin)/bytecodegenerator.o: bytecodegenerator.cpp
	g++ -c bytecodegenerator.cpp $(flags) -o $(bin)/bytecodegenerator.o

$(bin)/graphgenerator.o: graphgenerator.cpp
	g++ -c graphgenerator.cpp $(flags) -o $(bin)/graphgenerator.o

$(bin)/variable.o: variable.cpp
	g++ -c variable.cpp $(flags) -o $(bin)/variable.o

test:
	$(bin)/kumo ../examples/test.kmo

delete:
	rm -f $(bin)/kumo.exe
	rm -f $(objects)

clean: delete $(bin)/kumo
