#pragma once

#include <string>
#include <vector>

#include "token.h"
#include "tokentypes.h"
#include "log.h"

using namespace std;

class lexer{
	private:

		string data; //stores input string
		string currentToken;

		vector<token> tokens; //stores resulting token stream

		int state; //internal state
		int pointer; //current character counter
		string character;

		void step();
		void analize();
		void pushToken(const int);

		bool isLetter(string c);
		bool isNumber(string c);
		bool isWhitespace(string c);
		bool isOperator(string c);
		bool isNewline(string c);

	public:
		void lex(string data);
		vector<token> getTokens();
};
