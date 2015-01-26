#pragma once

#include <vector>
#include <string>
#include <map>

#include "bytecodes.h"
#include "log.h"
#include "variable.h"

using namespace std;

class libs{
private:
    map <string, vector <int> > liblist;
    vector <void (*)(variable * s, int * sp)> virtuals; //this is a list of function pointers

public:
    libs();

    void load();

    map <string, vector <int> > get();
    void call(int n, variable * s, int * sp);

};
