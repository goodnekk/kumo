#pragma once

#include <vector>
#include <string>
#include <map>

#include "bytecodes.h"

using namespace std;

class libfunction{
public:
    vector <int> bytecode;
    //void (*function)(int);
    string name;
    libfunction(string n, vector <int> b);
    libfunction();
};

class lib{
public:
    map <string, libfunction> elements;
    void add(libfunction f);
};

class libs{
private:
    string name;
    vector <lib> liblist;
public:
    libs();
    map <string, vector <int> > get();
};
