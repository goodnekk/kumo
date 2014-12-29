#pragma once
#include "token.h"
#include "tokentypes.h"

#include "parsenode.h"
#include "lexemetypes.h"

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
        parsenode * codeblock(int n);
        parsenode * statement(int n);

            parsenode * assignment(int n);

            parsenode * call(int n);
            parsenode * argumentlist(int n);

            parsenode * expression(int n);
            parsenode * mathexpression(int n);
                parsenode * addsub(int n);
                parsenode * multdiv(int n);
                parsenode * parenthesized(int n);
                parsenode * operand(int n);

            parsenode * textexpression(int n);
            parsenode * booleanexpression(int n);

            parsenode * declaration(int n);
            parsenode * nameslist(int n);

        //terminals
        parsenode * text(int n);
        parsenode * number(int n);
        parsenode * variable(int n);

        //high level compare functions
        parsenode * name(int n);
        parsenode * c_operator(int n, string w);
        //low level compare functions
        bool c_type(int n, int t);
        bool c_string(int n,string w);
        bool c_endofline(int n);
        bool c_endofprogram(int n);
    public:
        parsenode * parse(vector<token> list);
};
