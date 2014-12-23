#pragma once
#include <string>
#include <sstream>

#include <vector>
#include <iostream>
#include "log.h"

#include "instructions.h"
#include "program.h"
#include "variable.h"

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
            int index = p->push_constant(variable(value));
            p->push_instruction(instructions::PUSH_C);
            p->push_instruction(index);
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
            int number = p->get_variable(value);
            if(number==-1){
                LOG_COMPILE_ERROR("Unknown variable '"<<value<<"', maybe it is used before asignment, or outside scope.");
                STOP();
            }
            p->push_instruction(instructions::PUSH_R);
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
        variable * pointername;

        call(variable * n, node * a){
            argument = a;
            pointername = n;

            if (a){
                length = 3+a->length;
            } else{
                length = 3;
            }
        };

        void eval(program * p){

            int startpoint = p->get_position();
            if(argument){
                argument->eval(p);
            }
            if(pointername->value == "if"){
                p->push_instruction(instructions::ISTRUE); //0
                p->push_instruction(1);                    //1
                p->push_instruction(instructions::CALL);   //2
            } else if(pointername->value == "while"){
                p->push_instruction(instructions::ISTRUE); //0
                p->push_instruction(3);                    //1
                p->push_instruction(instructions::CALL);   //2
                p->push_instruction(instructions::GOTO);
                p->push_instruction(startpoint);
            } else if(pointername->value == "return"){
                p->push_instruction(instructions::RETURN);
            } else {
                pointername->eval(p);
                p->push_instruction(instructions::CALL);
            }
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
            length-=2;//remove last comma, and initial length of one
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

        declaration(node * a, node * s, bool paren){
            arguments = a;
            stmnt = s;
            length = 2+(s->length);
            if(paren){ //add another two just if there are argument parenthesis
                length +=2;
                if (a){
                    length +=(a->length);
                }
            }
        };

        void eval(program * p){
            //move to new function
            int pointer = p->new_function();
            int scope = p->new_scope();

            if(arguments){
                arguments->eval(p);
            }
            //create argument variables by poping values from the stack
            //write function code statements
            stmnt->eval(p); //write the statements to the new block
            p->push_instruction(instructions::RETURN);

            //return to calling function
            p->pop_function();
            p->pop_scope(scope);
            //push function pointer onto the stack
            p->push_instruction(instructions::PUSH_C);
            p->push_instruction(pointer);
        };
    };

    class nameslist: public node{
    public:
        vector<name*> list;
        nameslist(vector<name*> l){
            list = l;
            length = (list.size()*2)-1; //(name, name, name) remove last comma
        };
        void eval(program * p){
            for(int i=0; i<list.size(); i++){
                p->push_instruction(instructions::POP_R);
                int argument = p->force_variable(list[i]->value);
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
