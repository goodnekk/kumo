#pragma once

#include "tokentypes.h"

#include "token.h"
#include <vector>

using namespace std;

class preparser{
private:
    vector<token> tokens;
    token getToken(int n);
    bool variable(int n);
    bool op(int n);
    void check_construct(int n);
    void get_tokens();
public:
    void preparse(vector<token> t);
};
