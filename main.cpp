#include "lexer.h"
#include "parser.h"

int main() {
	lexer l;
	parser p;

	l.lex("1+23"); //should be 9
	p.parse(l.getTokens());
	return 0;
}
