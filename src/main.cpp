#include "log.h"
#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "vm.h"

#include <string>
#include <sstream>
#include <fstream>

const static float revision = 0.01;

int main(int argc, char* argv[]) {
	LOG("hello kumo "<<revision);
	//load program into memory
	std::fstream t(argv[1]);
	if (!t) {
		LOG_ERROR("please specify file");
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
