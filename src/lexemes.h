#pragma once
#include <string>
#include <sstream>

#include <vector>
#include <iostream>
#include "instructions.h"

using namespace std;
namespace lexemes{

    //empty node class
    //all nodes inherit from this one
    class node {
    public:
        int length;
        node(){length = 1;};
        virtual void eval(vector<int> * p){};
    };

    //terminals

    //number, converts number string to int
    //pushes a constant onto the stack
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

    //name, contains name string
    class name: public node{
    public:
        string value;
        name(string v){
            length = 1;
            value = v;
        };
    };

    class variable: public node{
    public:
        string value;
        variable(string v){
            length = 1;
            value = v;
        };
        void eval(vector<int> * p){
            p->push_back(instructions::PUSH_R);
            p->push_back(0);//read register
        };
    };

    //nonterminals
    //program, loops through each statement
    class program: public node{
    public:
        vector <node*> list;
        program(vector <node*> l){
            list = l;
        }
        void eval(vector<int> * p){
            for(int i=0; i<list.size(); i++){
                list[i]->eval(p);
            }
        }
    };

    //assignment, stores value in a variable
    class assignment: public node{
    public:
        node * variable;
        node * expression;

        assignment(node * v, node * e){
            variable = v;
            expression = e;
            length = (e->length)+2;
        };
        void eval(vector<int> * p){
            expression->eval(p);
            p->push_back(instructions::POP_R);
            p->push_back(0); //variable point
        }
    };

    //call, evaluates arguments and performs function call
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

    //arithmatic, evaluates a simple mathmatical statement
    //first evaluates it's children
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
                LOG_DEBUG("PARSER ERROR: invalid arithmatic: "<<op);
            }
        };
        void eval(vector<int> * p){
            r->eval(p);
            l->eval(p);
            p->push_back(code);
        };
    };
}
