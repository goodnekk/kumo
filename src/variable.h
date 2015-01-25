#pragma once

#include <string>
#include <sstream>

#include "log.h"

using namespace std;

enum class variabletypes {
    EMPTY,
    NUMBER,
    TEXT,
    BOOLEAN,
    POINTER
};

class variable{
private:
    variabletypes type;

    int pointer;
    float number;
    string text;
    bool boolean;

public:
    variable();
    variable(float n);

    variable(variabletypes t, int i);
    variable(variabletypes t, string s);
    variabletypes get_type();
    float get_number();
    int get_pointer();

    void say();
};
