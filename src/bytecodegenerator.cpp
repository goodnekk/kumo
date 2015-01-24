#include "bytecodegenerator.h"

program bytecodegenerator::generate(parsenode * root){
    loadStdlib();
    analize(root);
    pushCode(bytecodes::END);
    program p;
    p.code = code;
    p.constants = constants;
    p.library = library;
    return p;
}

void bytecodegenerator::analize(parsenode * node){
    for(int i=0; i < node->children.size(); i++){
        analize(node->children.at(i));
    }

    switch(node->type){
        case lexemetypes::ASSIGNMENT:
            assignment(node);
            break;
        case lexemetypes::VARIABLE:
            var(node);
            break;
        case lexemetypes::CALL:
            call(node);
            break;
        case lexemetypes::DECLARATION:
            declaration(node);
            break;
        case lexemetypes::NUMBER:
            constant(node);
            break;
        case lexemetypes::TEXT:
            constant(node);
            break;
        case lexemetypes::BOOLEAN:
            constant(node);
            break;
    }
}

void bytecodegenerator::assignment(parsenode * node){
    //first check if exists
    int a = -1;
    for(int i =0; i<variables.size(); i++){
        if(variables[i]==node->value){
            a = i;
        }
    }
    //else create new
    if(a==-1){
        variables.push_back(node->value);
        a = variables.size()-1;
    }

    pushCode(bytecodes::POP_R);
    pushCode(a);
}


void bytecodegenerator::var(parsenode * node){
    for(int i =0; i<variables.size(); i++){
        if(variables[i]==node->value){
            pushCode(bytecodes::PUSH_R);
            pushCode(i);
            return;
        }
    }
    LOG_ERROR("Variable "<<node->value<<" is used before declaration");
}

void bytecodegenerator::call(parsenode * node){
    if(templateTable.find(node->value) == templateTable.end()){
        LOG_ERROR("Unknown function "<<node->value);
        STOP();
    } else {
        pushCode(templateTable[node->value]);
    }
}

void bytecodegenerator::constant(parsenode * node){
    pushCode(bytecodes::PUSH_C);
    variabletypes t;
    if(node->type==lexemetypes::NUMBER){
        t = variabletypes::NUMBER;
    }
    if (node->type==lexemetypes::TEXT){
        t = variabletypes::TEXT;
    }
    if (node->type==lexemetypes::BOOLEAN){
        t = variabletypes::BOOLEAN;
    }
    constants.push_back(variable(t, node->value));
    pushCode(constants.size()-1);
    LOG_DEBUG("Generator: Constant["<<constants.size()-1<<"] = "<<node->value);
}

void bytecodegenerator::declaration(parsenode * node){

}

void bytecodegenerator::loadStdlib(){
    templateTable = library.get();
}

void bytecodegenerator::pushCode(int command){
    LOG_DEBUG("Generator: "<<command);
    code.push_back(command);
}

void bytecodegenerator::pushCode(vector <int> commands){
    for(int i=0; i < commands.size(); i++){
        pushCode(commands.at(i));
    }
}
