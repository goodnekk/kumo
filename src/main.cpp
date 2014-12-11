#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "vm.h"

int main() {
	lexer l;
	parser p;
	generator g;
	vm v;

	l.lex("print()"); //should be 6
	v.load(g.generate(p.parse(l.getTokens())));
	v.run();

	/*
	int temp[] = {0, 5, 0, 10, 2, 3};
	std::vector<int> program(temp, temp+6);
	v.load(program);
	v.run();
	*/
	return 0;
}
