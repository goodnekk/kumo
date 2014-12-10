#pragma once
#include <string>
#include <sstream>

#include <vector>
#include <iostream>
#include "instructions.h"

using namespace std;
namespace lexemes{

    class node {
    public:
        node(){};
        virtual void eval(vector<int> * p){};
    };

    //terminals
    class number: public node {
    public:
        int value;
        number(string characters){
            //convert to int
            istringstream convert(characters);
            convert >> value;
        };
        void eval(vector<int> * p){
            p->push_back(instructions::PUSH_C);
            p->push_back(value);
        };
    };

    //nonterminals
    class addition: public node {
    public:
        node * r;
        node * l;
        addition(node * left, node * right){
            l = left;
            r = right;
        };
        void eval(vector<int> * p){
            r->eval(p);
            l->eval(p);
            p->push_back(instructions::ADD);
        };
    };
}
