#pragma once

#include "lexemetypes.h"
#include "parsenode.h"
#include "log.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class graphgenerator{
private:
    int nodecount;

    vector <string> labels;
    vector <string> links;

    int analyse(parsenode * node);
    void new_label(string name);
    void new_link(int a, int b);
    void write_graph();
public:
    void generate(parsenode * root);

};
