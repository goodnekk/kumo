#include "parser.h"


parsenode * parser::parse(vector<token> list){
    LOG_DEBUG("Parser: Started");
    tokens = list;
    parsenode * a = codeblock(0);
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

//codeblock: statements followed by newlines
parsenode * parser::codeblock(int n){
    LOG_DEBUG("Parser: try codeblock "<<n);
    bool cont = true;
    parsenode * node = new parsenode(n,lexemetypes::BLOCK,0);
    while(cont) {
        parsenode * a = statement(n);
        if(a){
            node->push(a);
            if(c_endofline(n+(a->length))){
                n+=(a->length)+1;
                node->length+=1;
            } else {
                cont = false;
            }
        } else {
            if(c_endofline(n)){
                n+=1; //skip empty line
                node->length+=1;
            } else{
                cont = false;//end of codeblock
            }
        }
    }
    return node;
}

//statement
parsenode * parser::statement(int n){
    parsenode * a = assignment(n);
    if(a){
        return a;
    }

    parsenode * b = expression(n);
    if(b){
        return b;
    }

    return NULL;
}

//assignment:   a = 3*3      b = foo()
parsenode * parser::assignment(int n){
    LOG_DEBUG("Parser: try assignment "<<n);
    parsenode * a = variable(n);
    if(a){
        parsenode * b = c_operator(n+1,"=");
        if(b){
            parsenode * c = expression(n+2);
            if(c){
                parsenode * node = new parsenode(n,lexemetypes::ASSIGNMENT,2);
                node->value = a->value;
                delete a;
                node->push(c);
                return node;
            }
        }
    }
    return NULL;
}

//call     foo()      bar(4,5,4,"yes",true)
parsenode * parser::call(int n){
    LOG_DEBUG("Parser: try call "<<n);
    //check foo(
    parsenode * a = variable(n);
    if(!a){
        a = v_operator(n); //operator as variable
    }
    bool b = c_separator(n+1,"(");

    if(a&&b){
        parsenode * node = new parsenode(n,lexemetypes::CALL,3);
        node->value = a->value;
        delete a;

        //keeps track of length of argument list
        int argumentlength = 0;

        //check arguments
        parsenode * c = argument_list(n+2);
        if(c){
            //add arguments and update argumentlist
            for(int i=0; i < c->children.size(); i++){
                node->push(c->children.at(i));
            }
            //node->push(c);
            argumentlength = (c->length);
            delete c;
        }

        bool d = c_separator(n+2+argumentlength,")");
        if(d){
            return node;
        } else {
            delete node;
        }
    }

    return NULL;
}

//argumentlist seperated by comma's: 4,54,foo(),blaa,"text"
parsenode * parser::argument_list(int n){
    LOG_DEBUG("Parser: try argumentlist "<<n);

    bool cont = true;
    parsenode * node = new parsenode(n,lexemetypes::NAMESLIST,0);

    while(cont) {
        //if we find an expression add to list
        parsenode * a = expression(n);
        if(a) {
            node->push(a);

            //if we find comma increse lenght
            bool b = c_separator(n+(a->length), ",");
            if(b){
                node->length+=1;
                n+=1+(a->length);
            } else {//if not end list and return
                cont = false;
            }
        } else { //if there is no expression fail
            delete node;
            return NULL;
        }
    }
    return node;
}

//expression

parsenode * parser::expression(int n){
    LOG_DEBUG("Parser: try expression "<<n);
    parsenode * a = declaration(n);
    if(a){
        return a;
    }

    parsenode * b = logical_expression(n,0);
    if(b){
        return b;
    }

    return NULL;
}

parsenode * parser::declaration(int n){
    LOG_DEBUG("Parser: try declaration "<<n);

    bool paren = false;

    bool a = c_separator(n, "(");
    parsenode * b = names_list(n+1);
    if(a){
        if(b){
            n += b->length+1;
        } else {
            n += 1;
            delete b;
        }

        bool c = c_separator(n, ")");
        if(c){
            n+=1;
            paren = true;
        } else {
            //TODO: Expected paren
            delete b;
            return NULL;
        }
    } else {
        delete b;
        b = NULL;
    }

    bool d = c_separator(n, "{");
    if(d){
        parsenode * e = codeblock(n+1);
        if(e){
            bool f = c_separator(n+1+(e->length), "}");
            if(f){
                int length = 2;
                if(paren){length+=2;}

                parsenode * node = new parsenode(n,lexemetypes::DECLARATION,length);
                if(b){node->push(b);}
                node->push(e);
                return node;

            } else {
                //TODO: Expected }
                return NULL;
            }
        }
    }
    return NULL;
}

//argumentlist seperated by comma's: 4,54,foo(),blaa,"text"
parsenode * parser::names_list(int n){
    LOG_DEBUG("Parser: try names list "<<n);

    bool cont = true;
    parsenode * node = new parsenode(n,lexemetypes::NAMESLIST,0);

    while(cont) {
        //if we find an expression add to list
        parsenode * a = name(n);
        if(a) {
            node->push(a);

            //if we find comma increse lenght
            bool b = c_separator(n+(a->length), ",");
            if(b){
                node->length+=1;
                n+=1+(a->length);
            } else {//if not end list and return
                cont = false;
            }
        } else { //if there is no expression fail
            delete node;
            return NULL;
        }
    }
    return node;
}

parsenode * parser::logical_expression(int n, int op){
    LOG_DEBUG("Parser: try add/subtract "<<n);

    //recursively loop through all possible math operators
    string operators[5] = {"+","-","/","*","=="};

    parsenode * a = NULL;
    if(op<4){
        a = logical_expression(n,op+1);
    } else {
        a = logical_operand(n);
    }

    if(a){
        parsenode * b = c_operator(n+(a->length),operators[op]);
        if(b){
            parsenode * c = logical_expression(n+(a->length)+1,op);
            if(c){
                parsenode * node = new parsenode(n,lexemetypes::CALL,1);
                node->value = operators[op];
                node->push(a);
                node->push(c);
                return node;
            }
        }
        return a;
    }
    return NULL;
}

parsenode * parser::logical_operand(int n){
    LOG_DEBUG("Parser: try operand "<<n);
    parsenode * a = constant(n);
    if(a){
        return a;
    }

    parsenode * b = call(n);
    if(b){
        return b;
    }

    parsenode * c = variable(n);
    if(c){
        return c;
    }

    parsenode * d = logical_parenthesized(n);
    if(d){
        return d;
    }
    return NULL;
}

parsenode * parser::logical_parenthesized(int n){
    LOG_DEBUG("Parser: try parenthesized "<<n);
    bool a = c_separator(n,"(");
    if(a){
        parsenode * b = logical_expression(n+1,0);
        if(b){
            bool c = c_separator(n+1+b->length,")");
            if(c){
                b->length+=2;
                return b;
            } else {
                LOG_COMPILE_ERROR("Unballanced parenthesis, expected ')'");
                STOP();
                return NULL;
            }
        }
    }
    return NULL;
}

//variable: a  b  foo  bar  length
parsenode * parser::variable(int n){
    LOG_DEBUG("Parser: try variable "<<n);
    if(c_type(n,tokentypes::NAME)){
        parsenode * node = new parsenode(n,lexemetypes::VARIABLE,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

//variable: a  b  foo  bar  length
parsenode * parser::name(int n){
    LOG_DEBUG("Parser: try argument "<<n);
    if(c_type(n,tokentypes::NAME)){
        parsenode * node = new parsenode(n,lexemetypes::NAME,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}


//constants
parsenode * parser::constant(int n){
    parsenode * a = text(n);
    if(a){
        return a;
    }

    parsenode * b = number(n);
    if(b){
        return b;
    }

    parsenode * c = boolean(n);
    if(c){
        return c;
    }

}
//constant text:    "hello world"    "how are ya?"
parsenode * parser::text(int n){
    LOG_DEBUG("Parser: try string "<<n);
    if (c_type(n,tokentypes::STRING)) {
        parsenode * node =  new parsenode(n,lexemetypes::TEXT,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

//constant number: 5   5.3  20000
parsenode * parser::number(int n){
    LOG_DEBUG("Parser: try number "<<n);
    if (c_type(n,tokentypes::NUMBER)) {
        parsenode * node = new parsenode(n,lexemetypes::NUMBER,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

parsenode * parser::boolean(int n){
    LOG_DEBUG("Parser: try boolean literal "<<n);
    parsenode * e = variable(n);
    if(e){
        if(e->value=="true" || e->value=="false"){
            parsenode * node = new parsenode(n,lexemetypes::BOOLEAN,1);
            node->value = e->value;
            return node;
        }
    }
}

parsenode * parser::v_operator(int n){
    LOG_DEBUG("Parser: try operator as variable "<<n);
    if (c_type(n,tokentypes::OPERATOR)) {
        parsenode * node = new parsenode(n,lexemetypes::VARIABLE,1);
        node->value = getToken(n).tokenstring;
        return node;
    }
    return NULL;
}

//convenience function that checks operators like: * + ( ) ,
parsenode * parser::c_operator(int n, string w){
    LOG_DEBUG("Parser: try operator '"<<w<<"' "<<n);
    if (c_type(n,tokentypes::OPERATOR) && c_string(n,w)) {
        parsenode * node = new parsenode(n,lexemetypes::OPERATOR,1);
        node->value = w;
        return node;
    }
    return NULL;
}

//convenience function that checks operators like: * + ( ) ,
bool parser::c_separator(int n, string w){
    LOG_DEBUG("Parser: try separator '"<<w<<"' "<<n);
    if (c_type(n,tokentypes::SEPARATOR) && c_string(n,w)) {
        return true;
    }
    return false;
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
