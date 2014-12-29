#pragma once

#include <string>
#include <vector>

#include "lexemetypes.h"

class parsenode {
public:
    //
    string value;

    int length;
    lexemetypes type;
    vector <parsenode*> children;
    parsenode(lexemetypes t, int l){
        type = t;
        length = l;
    };
    void push(parsenode * c){
        children.push_back(c);
        length += c->length;
    };
};
