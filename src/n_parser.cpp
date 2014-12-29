#include "n_parser.h"


parsenode * parser::parse(vector<token> list){
    LOG_DEBUG("Parser: Started");
    tokens = list;
    parsenode * a = call(0);
    if(a) {
        LOG_DEBUG("Parser: Correctly parsed");
        return a;
    }
    else {
        LOG_COMPILE_ERROR("Parser failed, incomplete parse.");
        STOP();
    }
}
//get the next token from the vector
token parser::getToken(int n){
    if (n<tokens.size())
        return tokens[n];
    else
        return token(tokentypes::NOTASGN,"");
}

parsenode * parser::codeblock(int n){
    LOG_DEBUG("Parser: try codeblock "<<n);

}


//call     foo()      bar(4,5,4,"yes",true)
parsenode * parser::call(int n){
    LOG_DEBUG("Parser: try call "<<n);
    //check foo(
    parsenode * a = variable(n);
    parsenode * b = c_operator(n+1,"(");

    if(a&&b){
        parsenode * node = new parsenode(lexemetypes::CALL,2);
        node->push(a);

        //keeps track of length of argument list
        int argumentlength = 0;

        //check arguments
        parsenode * c = argumentlist(n+2);
        if(c){
            //add arguments and update argumentlist
            node->push(c);
            argumentlength = (c->length);
        } else {
            delete c;
        }


        parsenode * d = c_operator(n+2+argumentlength,")");
        if(d){
            return node;
        } else {
            delete node;
            delete d;
        }
    }
    delete a;
    delete b;
    return NULL;
}

//argumentlist seperated by comma's: 4,54,foo(),blaa,"text"
parsenode * parser::argumentlist(int n){
    LOG_DEBUG("Parser: try argumentlist "<<n);

    bool cont = true;
    parsenode * node = new parsenode(lexemetypes::ARGUMENTLIST,0);

    while(cont) {
        //if we find an expression add to list
        parsenode * a = number(n); //FIXME: should be expression
        if(a) {
            node->push(a);

            //if we find comma increse lenght
            parsenode * b = c_operator(n+(a->length), ",");
            if(b){

                node->length+=1;
                n+=1+(a->length);
            } else {//if not end list and return
                cont = false;
            }
        } else { //if there is no expression fail
            delete a;
            delete node;
            return NULL;
        }
    }
    return node;
}

//variable: a  b  foo  bar  length
parsenode * parser::variable(int n){
    LOG_DEBUG("Parser: try variable "<<n);
    if(c_type(n,tokentypes::NAME)){
        parsenode * node = new parsenode(lexemetypes::VARIABLE,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

//constant text:    "hello world"    "how are ya?"
parsenode * parser::text(int n){
    LOG_DEBUG("Parser: try string "<<n);
    if (c_type(n,tokentypes::STRING)) {
        parsenode * node =  new parsenode(lexemetypes::TEXT,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

//constant number: 5   5.3  20000
parsenode * parser::number(int n){
    LOG_DEBUG("Parser: try number "<<n);
    if (c_type(n,tokentypes::NUMBER)) {
        parsenode * node = new parsenode(lexemetypes::NUMBER,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

//convenience function that checks operators like: * + ( ) ,
parsenode * parser::c_operator(int n, string w){
    LOG_DEBUG("Parser: try operator '"<<w<<"' "<<n);
    if (c_type(n,tokentypes::OPERATOR) && c_string(n,w)) {
        parsenode * node = new parsenode(lexemetypes::OPERATOR,1);
        node->value = w;
        return node;
    }
    return NULL;
}

//convenience function that checks type of a token
bool parser::c_type(int n, int t){
    if (getToken(n).type == t) {
        return true;
    }
    return false;
}

//convenience function that checks value string of a token
bool parser::c_string(int n, string w){
    if(getToken(n).tokenstring == w){
        return true;
    }
    return false;
}

//convenience function that returns true if the end of line was reached
bool parser::c_endofline(int n){
    LOG_DEBUG("Parser: try NEWLINE "<<n);
    if(c_type(n,tokentypes::NEWLINE)){
        return true;
    }
    return false;
}

//convenience function that returns true if the end of the program was reached
bool parser::c_endofprogram(int n){
    if(c_type(n,tokentypes::NOTASGN)){
        return true;
    }
    return false;
}
