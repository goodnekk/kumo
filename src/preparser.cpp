//Author: Marcel Goethals
//Preparser converts syntactic sugar into more fundamental constructs
//for example arithmatic like: "6*4" is syntactic sugar for *(6,4)
//text->spellchecker->stext becomes text.onchange({stext = spellchecker(text)})
//
//
//
#include "preparser.h"

void preparser::preparse(vector<token> t) {
    tokens = t;
    bool cont = true;
    int n = 0;
    while(cont){
        check_construct(n);
        n++;
        if(getToken(n).type==tokentypes::NOTASGN){
            cont=false;
        }
    }


    get_tokens();
}

token preparser::getToken(int n){
    if (n<tokens.size()) {
        return tokens[n];
    } else {
        return token(tokentypes::NOTASGN,"");
    }
}

void preparser::check_construct(int n) {
    //variable * variable
    bool a = variable(n);
    bool b = op(n+1);
    bool c = variable(n+2);
    if(a&&b&&c){
        token ta = getToken(n);
        token tb = getToken(n+1);
        token tc = getToken(n+2);

        //consume the construct
        tokens.erase(tokens.begin()+n);
        tokens.erase(tokens.begin()+n);
        tokens.erase(tokens.begin()+n);

        //insert the reformed construct
        tokens.insert(tokens.begin()+n,tb);
        tokens.insert(tokens.begin()+n+1,token(tokentypes::OPERATOR,"("));
        tokens.insert(tokens.begin()+n+2,ta);
        tokens.insert(tokens.begin()+n+3,token(tokentypes::OPERATOR,","));
        tokens.insert(tokens.begin()+n+4,tc);
        tokens.insert(tokens.begin()+n+5,token(tokentypes::OPERATOR,")"));
    }
}

bool preparser::variable(int n) {
    if (getToken(n).type == tokentypes::NAME) {
        return true;
    }
    return false;
}

bool preparser::op(int n) {
    if (getToken(n).type == tokentypes::OPERATOR && getToken(n).tokenstring == "*") {
        return true;
    }
    return false;
}

void preparser::get_tokens(){
    LOG_DEBUG("Preparsed to: "<<tokens.size()<<" tokens");
    for(int i=0; i<tokens.size(); i++){
        tokens.at(i).print(i);
    }
}
