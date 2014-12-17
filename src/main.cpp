#include "log.h"
#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "vm.h"

#include <string>
#include <sstream>
#include <fstream>

const static string revision_name = "yamanashi";
const static int major_revision = 0;
const static int minor_revision = 2;


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

	//start compilation
	lexer l;
	parser p;
	generator g;
	vm v;

	l.lex(program); //should be 5
	v.load(g.generate(p.parse(l.getTokens())));
	v.run();

	return 0;
}
