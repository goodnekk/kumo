#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "vm.h"

#include <string>
#include <sstream>
#include <fstream>

int main(int argc, char* argv[]) {

	//load program into memory
	std::fstream t(argv[1]);
	if (!t) {
		std::cout << "please specify file" << std::endl;
		return 0;
	}
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string program = buffer.str();


	lexer l;
	parser p;
	generator g;
	vm v;

	l.lex(program); //should be 5
	v.load(g.generate(p.parse(l.getTokens())));
	v.run();

	return 0;
}
