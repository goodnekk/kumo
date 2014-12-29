#include "graphgenerator.h"

void graphgenerator::generate(parsenode * root){
    nodecount=0;
    analyse(root);
    write_graph();
}

int graphgenerator::analyse(parsenode * node){
    nodecount++;
    int thisnode = nodecount;

    lexemetypes t = node->type;
    switch(t){
        case lexemetypes::NUMBER:
            new_label("number: "+(node->value));
            break;
        case lexemetypes::CALL:
            new_label("call");
            break;
        case lexemetypes::VARIABLE:
            new_label("variable: "+(node->value));
            break;
        case lexemetypes::ARGUMENTLIST:
            new_label("arguments");
        default:
            LOG_DEBUG("Graph: unknow lexemetype: ");
            break;
    }

    for(int i=0; i < node->children.size(); i++){
        int othernode = analyse(node->children.at(i));
        new_link(thisnode, othernode);
    }
    return thisnode;
}
void graphgenerator::new_label(string name){
    ostringstream convert;
    convert << nodecount;
    labels.push_back(convert.str()+" [label=\""+name+"\"];");
}

void graphgenerator::new_link(int a, int b){
    ostringstream converta;
    ostringstream convertb;
    converta << a;
    convertb << b;
    links.push_back(converta.str()+"->"+convertb.str());
}

void graphgenerator::write_graph(){
    LOG_DEBUG("digraph parsetree {");
    for(int i=0; i < labels.size(); i++){
        LOG_DEBUG("    "<<labels.at(i));
    }
    LOG_DEBUG("//links");
    for(int i=0; i < links.size(); i++){
        LOG_DEBUG("    "<<links.at(i));
    }
    LOG_DEBUG("}");
}
