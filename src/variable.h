#pragma once
#include <string>
#include "log.h"

using namespace std;

class variable{
private:
    int type;

    float number;
    string text;
    bool boolean;

public:
    variable();
    variable(int n);
    variable(bool n);
    variable(string n);
    int get();
    string get_text();
    int get_type();
};
