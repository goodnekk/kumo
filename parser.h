#pragma once
#include "token.h"
#include "tokentypes.h"
#include "lexemes.h"

#include <iostream>
#include <vector>

using namespace std;

class parser{
    private:
        vector<token> tokens;
        //recursive analysis
        //non terminals
        token getToken(int n);
        lexemes::node * add(int n);

        //terminals
        lexemes::node * number(int n);
        bool plus(int n);

        lexemes::node * test();

    public:
        void parse(vector<token> list);
};
