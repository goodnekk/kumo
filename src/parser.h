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
        lexemes::node * statement(int n);

        lexemes::node * call(int n);
        lexemes::node * expression(int n);
        lexemes::node * add(int n);

        //terminals
        lexemes::node * number(int n);


        //high level compare functions
        lexemes::name * name(int n);
        lexemes::node * c_operator(int n, string w);
        //low level compare functions
        bool c_type(int n, int t);
        bool c_string(int n,string w);

    public:
        lexemes::node * parse(vector<token> list);
};
