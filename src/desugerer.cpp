// author: Marcel Goethals
// Takes a parsetree and transforms high-level constructs into low level constructs
// This simplefies code generation.
#include "desugerer.h"

parsenode * desugerer::desuger(parsenode * root){

    parsenode * answ = analyse(root);
    if(answ){
        root = answ;
    }
    return root;
}

parsenode * desugerer::analyse(parsenode * node){
    lexemetypes t = node->type;

    for(int i=0; i < node->children.size(); i++){
        parsenode * answ = analyse(node->children.at(i));
        if(answ){
            node->children.at(i) = answ;
        }
    }

    parsenode * replace = NULL;
    parsenode * variable = NULL;
    parsenode * arguments = NULL;

    if(t==lexemetypes::EXPRESSION){
        //variable = new parsenode(node->token,lexemetypes::VARIABLE,1);
        //variable->value = node->value;

        //arguments = new parsenode(node->token,lexemetypes::ARGUMENTLIST,1);
        for(int i=0; i < node->children.size(); i++){
            arguments->push(node->children.at(i));
        }

        replace = new parsenode(node->token,lexemetypes::CALL,0);
        replace->value = node->value;
        //replace->push(arguments);
        for(int i=0; i < node->children.size(); i++){
            replace->push(node->children.at(i));
        }

    }
    return replace;
}
