#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "vm.h"

int main() {
	lexer l;
	parser p;
	generator g;
	vm v;

	l.lex("print((2*3+1)*5)"); //should be 6
	v.load(g.generate(p.parse(l.getTokens())));
	v.run();

	return 0;
}
