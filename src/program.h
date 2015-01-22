#pragma once

#include <vector>
#include "variable.h"
#include "libs.h"

using namespace std;

class program{
public:
    vector <int> code;
    vector <variable> constants;
    libs library;
};
