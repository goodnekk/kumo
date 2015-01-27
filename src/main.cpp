#include "log.h"
#include "lexer.h"
#include "parser.h"
#include "graphgenerator.h"
#include "bytecodegenerator.h"
#include "vm.h"

#include <string>
#include <sstream>
#include <fstream>

const static string revision_name = "pre release";
const static int major_revision = 0;
const static int minor_revision = 3;

int main(int argc, char* argv[]) {
	LOG("hello kumo v"<< major_revision<<"."<<minor_revision<<"("<<revision_name<<")");
	//load program into memory
	std::fstream t(argv[1]);
	if (!t) {
		LOG_ERROR("please specify file");
		return 0;
	}
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string program = buffer.str();


	if(argc==3 && std::string(argv[2])=="-g"){

		LOG("output graph");
		lexer l;
		parser p;
		graphgenerator gr;

		l.lex(program);
		gr.generate(p.parse(l.getTokens()));

	} else {
		lexer l;
		parser p;
		bytecodegenerator g;
		vm v;

		l.lex(program);
		v.load(g.generate(p.parse(l.getTokens())));
		v.run();
	}

	return 0;
}
