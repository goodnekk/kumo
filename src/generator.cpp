//author: Marcel Goethals
//code generator, parses an abstract syntax tree and generates
//a program in the form of a 2d vector
//the first dimension contains functions where 0 is the main function
//the second dimension contains a list of operators in the form of ints
//all possible instructions are listed in instructions.h

#include "generator.h"

vector< vector<int> > generator::generate(lexemes::node * a){
    LOG_DEBUG("Generator: started");
    a->eval(&p);
    return p.get_list();
}
