//author: Marcel Goethals
//code generator, parses an abstract syntax tree and generates
//a program in the form of a vector.

#include "generator.h"

vector<int> generator::generate(lexemes::node * a){
    LOG_DEBUG("Generator: started");
    a->eval(&p);
    return p.get_list();
}
