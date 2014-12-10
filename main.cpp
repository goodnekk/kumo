#include "lexer.h"
#include "parser.h"
#include "vm.h"

int main() {
	//lexer l;
	//parser p;
	vm v;

	//l.lex("1+2+3"); //should be 6
	//p.parse(l.getTokens());

	int temp[] = {0, 5, 0, 10, 2, 3};
	std::vector<int> program(temp, temp+6);
	v.load(program);
	v.run();

	return 0;
}
