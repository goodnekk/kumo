#pragma once

#include "token.h"
#include <vector>

using namespace std;

class preparser{
private:
    vector<token> tokens;
public:
    void preparse(vector<token> t);
};
