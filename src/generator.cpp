//author: Marcel Goethals
//code generator, parses an abstract syntax tree and generates
//a program in the form of a 2d vector
//the first dimension contains functions where 0 is the main function
//the second dimension contains a list of operators in the form of ints
//all possible instructions are listed in instructions.h

#include "generator.h"
#include "instructions.h"

vector< vector<int> > generator::generate(lexemes::node * a){
    LOG_DEBUG("Generator: started");
    standardfunctions();
    a->eval(&p);
    return p.get_list();
}

void generator::standardfunctions(){
    ifstatement();
    whilestatement();
    virtual_function("say",0);
    virtual_function("ask",1);
}

void generator::ifstatement(){
    int pointer = p.new_function();
    //write function code statements
    p.push_instruction(instructions::ISTRUE);
    p.push_instruction(instructions::CALL);
    p.push_instruction(instructions::RETURN);
    //return to calling function
    p.pop_function();

    //push function pointer onto the stack
    p.push_instruction(instructions::PUSH_C);
    p.push_instruction(pointer);

    //push function pointer from stack to hashtable
    int reg = p.assign_variable("if");
    p.push_instruction(instructions::POP_R);
    p.push_instruction(reg);
}

void generator::whilestatement(){
    int pointer = p.new_function();
    //write function code statements
    p.push_instruction(instructions::ISTRUE);
    p.push_instruction(instructions::CALL);
     //call body
    p.push_instruction(instructions::RETURN);

    //return to calling function
    p.pop_function();

    //push function pointer onto the stack
    p.push_instruction(instructions::PUSH_C);
    p.push_instruction(pointer);

    //push function pointer from stack to hashtable
    int reg = p.assign_variable("while");
    p.push_instruction(instructions::POP_R);
    p.push_instruction(reg);
}

void generator::say(){
    int pointer = p.new_function();
    //write function code statements
    p.push_instruction(instructions::PUSH_C);
    p.push_instruction(0);
    p.push_instruction(instructions::V_CALL);
    p.push_instruction(instructions::RETURN);
    //return to calling function
    p.pop_function();

    //push function pointer onto the stack
    p.push_instruction(instructions::PUSH_C);
    p.push_instruction(pointer);

    //push function pointer from stack to hashtable
    int reg = p.assign_variable("say");
    p.push_instruction(instructions::POP_R);
    p.push_instruction(reg);
}

void generator::virtual_function(string name, int virtualpointer){
    int pointer = p.new_function();
    //write function code statements
    p.push_instruction(instructions::PUSH_C);
    p.push_instruction(virtualpointer);
    p.push_instruction(instructions::V_CALL);
    p.push_instruction(instructions::RETURN);
    //return to calling function
    p.pop_function();

    //push function pointer onto the stack
    p.push_instruction(instructions::PUSH_C);
    p.push_instruction(pointer);

    //push function pointer from stack to hashtable
    int reg = p.assign_variable(name);
    p.push_instruction(instructions::POP_R);
    p.push_instruction(reg);
}
