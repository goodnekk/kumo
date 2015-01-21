#pragma once

#include <vector>
#include <string>
#include <map>

#include "bytecodes.h"
#include "log.h"

using namespace std;

class libs{
private:
    map <string, vector <int> > liblist;
    vector <void (*)()> virtuals; //this is a list of function pointers

public:
    libs();
    map <string, vector <int> > get();
};
