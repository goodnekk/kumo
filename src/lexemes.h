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
        int length;
        node(){length = 1;};
        virtual void eval(vector<int> * p){};
    };

    //terminals
    class number: public node {
    public:
        int value;
        number(string characters){
            length = 1;
            //convert to int
            istringstream convert(characters);
            convert >> value;
        };
        void eval(vector<int> * p){
            p->push_back(instructions::PUSH_C);
            p->push_back(value);
        };
    };

    class name: public node{
    public:
        string value;
        name(string v){
            length = 1;
            value = v;
        };
    };

    //nonterminals
    class call: public node{
    public:
        node * argument;
        string name;

        call(node * a, string n){
            argument = a;
            name = n;
            if (a){
                length = 3+a->length;
            } else{
                length = 3;
            }
        };
        void eval(vector<int> * p){
            argument->eval(p);
            p->push_back(instructions::PRINT);
        };
    };

    class arithmetic: public node {
    public:
        node * r;
        node * l;
        int code;
        arithmetic(node * left, node * right, string op){
            l = left;
            r = right;
            length = (l->length)+(r->length)+1;
            if(op=="+"){
                code = instructions::ADD;
            } else if(op=="-"){
                code = instructions::SUB;
            } else if(op=="*"){
                code = instructions::MULT;
            } else if(op=="/"){
                code = instructions::DIV;
            } else{
                code = 0;
                LOG_DEBUG("PARSER ERROR: ivalid arithmatic: "<<op);
            }
        };
        void eval(vector<int> * p){
            r->eval(p);
            l->eval(p);
            p->push_back(code);
        };
    };
}
