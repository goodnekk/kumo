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

    switch(node->type){
        case lexemetypes::BLOCK:
            block(node);
            children(node);
            break;
        case lexemetypes::ASSIGNMENT:
            children(node);
            assignment(node);
            break;
        case lexemetypes::VARIABLE:
            var(node);
            break;
        case lexemetypes::CALL:
            children(node);
            call(node);
            break;
        case lexemetypes::DECLARATION:
            children(node);
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
        case lexemetypes::NAMESLIST:
            nameslist();
            children(node);
            break;
        case lexemetypes::NAME:
            name(node);
            break;
    }
}

void bytecodegenerator::children(parsenode * node){
    for(int i=0; i < node->children.size(); i++){
        analize(node->children.at(i));
    }
}

void bytecodegenerator::block(parsenode * node){
    LOG_DEBUG("Generator: new block");
    vector<int> a; //FIXME: there must be another way...
    code.push_back(a);

    vector<string> b;
    locals.push_back(b);

    argsize.push_back(arguments.size());

    blockStack.push_back(code.size()-1);

}

void bytecodegenerator::assignment(parsenode * node){
    if(locals.size()>1){
        int a = -1;
        LOG_DEBUG("Assigning Local variable "<<node->value);
        for(int i =0; i<locals[blockStack[blockStack.size()-1]].size(); i++){
            if(locals[blockStack[blockStack.size()-1]][i]==node->value){
                a = i;
            }
        }
        if(a==-1){
            locals[blockStack[blockStack.size()-1]].push_back(node->value);
            a = locals[blockStack[blockStack.size()-1]].size()-1;
        }
        pushCode(bytecodes::POP_L);
        pushCode(a);
    } else {
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
}


void bytecodegenerator::var(parsenode * node){
    for(int i =0; i<arguments.size(); i++){
        if(arguments[i]==node->value){
            pushCode(bytecodes::PUSH_L);
            pushCode(-3-(arguments.size()-1)+i); //skip over activation frame
            return;
        }
    }
    if(locals.size()>1){
        for(int i =0; i<locals[blockStack[blockStack.size()-1]].size(); i++){
            if(locals[blockStack[blockStack.size()-1]][i]==node->value){
                pushCode(bytecodes::PUSH_L);
                pushCode(i);
                return;
            }
        }
    } else{
        for(int i =0; i<variables.size(); i++){
            if(variables[i]==node->value){
                pushCode(bytecodes::PUSH_R);
                pushCode(i);
                return;
            }
        }
    }

    LOG_ERROR("Variable "<<node->value<<" is used before declaration");
    STOP();
}

void bytecodegenerator::call(parsenode * node){
    //find function in templates
    if(!(templateTable.find(node->value) == templateTable.end())){
        pushCode(templateTable[node->value]);
        return;
    } else { //find function in variables
        for(int i=0; i<variables.size(); i++){
            if(node->value == variables[i]){
                pushCode(bytecodes::CALL);
                pushCode(i); //Function Pointer
                pushCode(localsize[i]); //space for locals
                return;
            }
        }
        LOG_ERROR("Unknown function "<<node->value);
        STOP();
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

    //push a return function at the end to make sure
    pushCode(bytecodes::RETURN);
    pushCode(argsize[blockStack[blockStack.size()-1]]); //how many arguments to pop off

    //return to the last block
    int lastBlock = blockStack[blockStack.size()-1];
    blockStack.pop_back();

    localsize.push_back(locals[locals.size()-1].size());
    //return to the last scope
    locals.pop_back();


    //push the function pointer onto the stack
    pushCode(bytecodes::PUSH_C);
    constants.push_back(variable(variabletypes::POINTER, lastBlock));
    pushCode(constants.size()-1);

    LOG_DEBUG("Generator: Pointer["<<constants.size()-1<<"] = "<<lastBlock);
}

void bytecodegenerator::nameslist(){
    arguments.clear();
}

void bytecodegenerator::name(parsenode * node){
    arguments.push_back(node->value);
}

void bytecodegenerator::loadStdlib(){
    library.load();
    templateTable = library.get();
}

void bytecodegenerator::pushCode(int command){
    LOG_DEBUG("Generator: "<<command);
    code[blockStack[blockStack.size()-1]].push_back(command);
}

void bytecodegenerator::pushCode(vector <int> commands){
    for(int i=0; i < commands.size(); i++){
        pushCode(commands.at(i));
    }
}
