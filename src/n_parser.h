#pragma once

#include "token.h"
#include "tokentypes.h"

#include "parsenode.h"
#include "lexemetypes.h"

#include "log.h"

#include <vector>

using namespace std;

class parser{
    private:
        vector<token> tokens;

        //recursive analysis
        //non terminals
        token getToken(int n);

        parsenode * codeblock(int n);

        //function calls
        parsenode * call(int n);
        parsenode * argument_list(int n);

        //expressions
        parsenode * expression(int n);
        parsenode * math_expression(int n);

        //terminals
        parsenode * variable(int n);
        parsenode * text(int n);
        parsenode * number(int n);

        //convenience functions
        parsenode * c_operator(int n, string w);
        bool c_type(int n, int t);
        bool c_string(int n,string w);
        bool c_endofline(int n);
        bool c_endofprogram(int n);
    public:
        parsenode * parse(vector<token> list);
};
