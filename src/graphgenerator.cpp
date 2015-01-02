//author: Marcel Goethals
//Graph generator, takes a parsetree and turns it into a graph in DOT format
//This file can be read in graphviz or some other program.

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
        case lexemetypes::BLOCK:
            new_label("block");
            break;
        case lexemetypes::ASSIGNMENT:
            new_label("assignment");
            break;
        case lexemetypes::DECLARATION:
            new_label("declaration");
            break;
        case lexemetypes::BOOLEAN:
            new_label("boolean: "+(node->value));
            break;
        case lexemetypes::TEXT:
            new_label("text: "+(node->value));
            break;
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
            break;
        case lexemetypes::EXPRESSION:
            new_label("arithmatic:"+(node->value));
            break;
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
    ofstream myfile;
    myfile.open ("../parsetree.gv");

    myfile <<"digraph parsetree {"<<endl;
    for(int i=0; i < labels.size(); i++){
        myfile <<"    "<<labels.at(i)<<endl;
    }
    myfile <<"//links"<<endl;
    for(int i=0; i < links.size(); i++){
        myfile <<"    "<<links.at(i)<<endl;
    }
    myfile <<"}"<<endl;
    myfile.close();
}
