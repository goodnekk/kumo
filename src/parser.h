#pragma once
#include "token.h"
#include "tokentypes.h"
#include "lexemes.h"

#include "log.h"
#include <vector>
#include <string>

using namespace std;

class parser{
    private:
        vector<token> tokens;

        //recursive analysis
        //non terminals
        token getToken(int n);
        lexemes::node * codeblock(int n);
        lexemes::node * statement(int n);

            lexemes::node * assignment(int n);

            lexemes::node * call(int n);
            lexemes::node * argumentlist(int n);

            lexemes::node * expression(int n);
            lexemes::node * mathexpression(int n);
                lexemes::node * addsub(int n);
                lexemes::node * multdiv(int n);
                lexemes::node * parenthesized(int n);
                lexemes::node * operand(int n);

            lexemes::node * textexpression(int n);
            lexemes::node * booleanexpression(int n);

            lexemes::node * declaration(int n);
            lexemes::node * nameslist(int n);

        //terminals
        lexemes::node * text(int n);
        lexemes::node * number(int n);
        lexemes::variable * variable(int n);

        //high level compare functions
        lexemes::name * name(int n);
        lexemes::node * c_operator(int n, string w);
        //low level compare functions
        bool c_type(int n, int t);
        bool c_string(int n,string w);
        bool c_endofline(int n);
        bool c_endofprogram(int n);
    public:
        lexemes::node * parse(vector<token> list);
};
