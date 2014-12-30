#pragma once

#include <string>
#include <vector>

#include "lexemetypes.h"

using namespace std;

class parsenode {
public:
    //
    string value;

    int token;
    int length;
    
    lexemetypes type;
    vector <parsenode*> children;
    parsenode(int tok, lexemetypes ty, int l){
        token = tok;
        type = ty;
        length = l;
    };
    void push(parsenode * c){
        children.push_back(c);
        length += c->length;
    };
};
