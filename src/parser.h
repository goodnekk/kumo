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

        parsenode * statement(int n);
        parsenode * assignment(int n);
        //function calls
        parsenode * call(int n);
        parsenode * argument_list(int n);

        //expressions
        parsenode * expression(int n);
            parsenode * declaration(int n);
                parsenode * names_list(int n);

            parsenode * math_expression(int n);
                parsenode * add_sub(int n);
                parsenode * mult_div(int n);
                parsenode * math_operand(int n);
                parsenode * parenthesized(int n);

            parsenode * text_expression(int n);
                parsenode * text_add(int n);
                parsenode * text_operand(int n);

            parsenode * boolean_expression(int n);
                parsenode * boolean_compare(int n);
                parsenode * boolean_operand(int n);


        //terminals
        parsenode * variable(int n);
        parsenode * text(int n);
        parsenode * number(int n);
        parsenode * boolean(int n);

        //convenience functions
        parsenode * c_operator(int n, string w);
        bool c_type(int n, int t);
        bool c_string(int n,string w);
        bool c_endofline(int n);
        bool c_endofprogram(int n);
    public:
        parsenode * parse(vector<token> list);
};
