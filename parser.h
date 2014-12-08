#pragma once
#include "token.h"
#include "tokentypes.h"
#include <vector>

using namespace std;

class parser{
    private:
        vector<token> tokens;
        //recursive analysis
        //non terminals
        token getToken(int n);
        bool add(int n);

        //terminals
        bool number(int n);
        bool plus(int n);

    public:
        void parse(vector<token> list);
};
