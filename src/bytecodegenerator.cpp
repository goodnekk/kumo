#include "bytecodegenerator.h"

void bytecodegenerator::generate(parsenode * root){
    block(root);
}


void bytecodegenerator::block(parsenode * node){
    for(int i=0; i < node->children.size(); i++){
        call(node->children.at(i));
    }
}

void bytecodegenerator::call(parsenode * node){

}

void bytecodegenerator::variable(parsenode * node){

}

void bytecodegenerator::loadStdlib(){
    variables.push_back("+");
}
