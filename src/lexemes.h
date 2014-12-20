#pragma once
#include <string>
#include <sstream>

#include <vector>
#include <iostream>
#include "instructions.h"
#include "program.h"
#include "log.h"

using namespace std;
namespace lexemes{

    //empty node class
    //all nodes inherit from this one
    class node {
    public:
        int length;
        node(){length = 1;};
        virtual void eval(program * p){};
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
        void eval(program * p){
            p->push_instruction(instructions::PUSH_C);
            p->push_instruction(value);
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
        void eval(program * p){
            p->push_instruction(instructions::PUSH_R);
            int number = p->get_variable(value);
            if(number==-1){
                LOG_COMPILE_ERROR("Using '"<<value<<"' before assignment.");
                STOP();
            }
            p->push_instruction(number);//read register
        };
    };

    //nonterminals
    //program, loops through each statement
    class statementlist: public node{
    public:
        vector <node*> list;
        statementlist(vector <node*> l, int len){
            list = l;
            //for(int i=0; i<list.size(); i++){
            //    length+=(list[i]->length);
            //}
            length=len;
        }
        void eval(program * p){
            for(int i=0; i<list.size(); i++){
                list[i]->eval(p);
            }
        }
    };

    //assignment, stores value in a variable
    class assignment: public node{
    public:
        name * variable;
        node * expression;

        assignment(name * v, node * e){
            variable = v;
            expression = e;
            length = (e->length)+2;
        };
        void eval(program * p){
            expression->eval(p);
            p->push_instruction(instructions::POP_R);
            int number = p->assign_variable(variable->value);
            p->push_instruction(number); //variable point
        }
    };

    //call, evaluates arguments and performs function call
    class call: public node{
    public:
        node * argument;
        node * pointername;

        call(node * n, node * a){
            argument = a;
            pointername = n;

            if (a){
                length = 3+a->length;
            } else{
                length = 3;
            }
        };
        void eval(program * p){
            if(argument){
                argument->eval(p);
            }
            pointername->eval(p);
            p->push_instruction(instructions::CALL);
            //p->push_instruction();
        };
    };

    class argumentlist: public node{
    public:
        vector<node*> list;

        argumentlist(vector<node*> a){
            list = a;
            for(int i=0; i<list.size(); i++){
                length+=list[i]->length+1;
            }
            length-=2;//remove last comma, and initial lenght of one
        }
        void eval(program * p){
            //push the arguments on backwards
            for(int i=list.size()-1; i>=0; i--){
                list[i]->eval(p);
            }
        }
    };

    //declaration, defines a function
    class declaration: public node{
    public:
        node * arguments;
        node * stmnt;

        declaration(node * a, node * s){
            arguments = a;
            stmnt = s;
            if (a){
                length = 4+(a->length)+(s->length);
            } else{
                length = 4+(s->length);
            }
        };

        void eval(program * p){
            //move to new function
            int pointer = p->new_function();
            if(arguments){
                arguments->eval(p);
            }
            //create argument variables by poping values from the stack
            //int firstargument = p->assign_variable(argument->value);
            //p->push_instruction(instructions::POP_R);
            //p->push_instruction(firstargument);

            //write function code statements
            stmnt->eval(p); //write the statements to the new block
            p->push_instruction(instructions::RETURN);

            //return to calling function
            p->pop_function();

            //push function pointer onto the stack
            p->push_instruction(instructions::PUSH_C);
            p->push_instruction(pointer);

            //TODO:free the variables for scoping
        };
    };

    class nameslist: public node{
    public:
        vector<name*> list;
        nameslist(vector<name*> l){
            list = l;
            length = (list.size()*2)-1;
        };
        void eval(program * p){
            for(int i=0; i<list.size(); i++){
                p->push_instruction(instructions::POP_R);
                int argument = p->assign_variable(list[i]->value);
                p->push_instruction(argument);
            }
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
        void eval(program * p){
            r->eval(p);
            l->eval(p);
            p->push_instruction(code);
        };
    };
}
