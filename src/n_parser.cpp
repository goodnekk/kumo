#include "n_parser.h"


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
                parsenode * node = new parsenode(n,lexemetypes::ASSIGNMENT,1);
                node->push(a);
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
    parsenode * b = c_operator(n+1,"(");

    if(a&&b){
        delete b; //don't need it anymore
        parsenode * node = new parsenode(n,lexemetypes::CALL,2);
        node->push(a);

        //keeps track of length of argument list
        int argumentlength = 0;

        //check arguments
        parsenode * c = argument_list(n+2);
        if(c){
            //add arguments and update argumentlist
            node->push(c);
            argumentlength = (c->length);
        }

        parsenode * d = c_operator(n+2+argumentlength,")");
        if(d){
            delete d; //don't need it anymore
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
    parsenode * node = new parsenode(n,lexemetypes::ARGUMENTLIST,0);

    while(cont) {
        //if we find an expression add to list
        parsenode * a = expression(n);
        if(a) {
            node->push(a);

            //if we find comma increse lenght
            parsenode * b = c_operator(n+(a->length), ",");
            if(b){
                delete b; //don't need it anymore
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

    parsenode * b = boolean_expression(n);
    if(b){
        return b;
    }

    parsenode * c = math_expression(n);
    if(c){
        return c;
    }
    //TODO: if c is terminal, check for text alternative
    parsenode * d = text_expression(n);
    if(d){
        return d;
    }

    return NULL;
}

parsenode * parser::declaration(int n){
    LOG_DEBUG("Parser: try declaration "<<n);

    bool paren = false;

    parsenode * a = c_operator(n, "(");
    parsenode * b = names_list(n+1);
    if(a){
        if(b){
            n += b->length+1;
        } else {
            n += 1;
            delete b;
        }

        parsenode * c = c_operator(n, ")");
        if(c){
            n+=1;
            paren = true;
        } else {
            //TODO: Expected paren
            delete a;
            delete b;
            return NULL;
        }
    } else {
        delete a;
        delete b;
        b = NULL;
    }

    parsenode * d = c_operator(n, "{");
    if(d){
        parsenode * e = codeblock(n+1);
        if(e){
            parsenode * f = c_operator(n+1+(e->length), "}");
            if(f){
                int length = 2;
                if(paren){length+=2;}

                parsenode * node = new parsenode(n,lexemetypes::DECLARATION,length);
                node->push(e);
                if(b){node->push(b);}
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
    parsenode * node = new parsenode(n,lexemetypes::ARGUMENTLIST,0);

    while(cont) {
        //if we find an expression add to list
        parsenode * a = variable(n);
        if(a) {
            node->push(a);

            //if we find comma increse lenght
            parsenode * b = c_operator(n+(a->length), ",");
            if(b){
                delete b; //don't need it anymore
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

//mathexpression
parsenode * parser::math_expression(int n){
    LOG_DEBUG("Parser: try math expression "<<n);

    parsenode * a = add_sub(n);
    if(a){
        return a;
    }

    return NULL;
}

parsenode * parser::add_sub(int n){
    LOG_DEBUG("Parser: try add/subtract "<<n);
    parsenode * a = mult_div(n);
    if(a){
        string op = "+";
        parsenode * b = c_operator(n+(a->length),op);
        if(!b){
            op = "-";
            b = c_operator(n+(a->length),op);
        }
        if(b){
            parsenode * c = add_sub(n+(a->length)+1);
            if(c){
                parsenode * node = new parsenode(n,lexemetypes::ARITHMETIC,1);
                node->value = op;
                node->push(a);
                node->push(c);
                return node;
            }
        }
        return a;
    }
    return NULL;
}

parsenode * parser::mult_div(int n){
    LOG_DEBUG("Parser: try multiply/divide "<<n);
    parsenode * a = math_operand(n);
    if(a){
        string op = "*";
        parsenode * b = c_operator(n+(a->length),op);
        if(!b){
            op = "/";
            b = c_operator(n+(a->length),op);
        }
        if(b){
            parsenode * c = mult_div(n+(a->length)+1);
            if(c){
                parsenode * node = new parsenode(n,lexemetypes::ARITHMETIC,1);
                node->value = op;
                node->push(a);
                node->push(c);
                return node;
            }
        }
        return a;
    }
    return NULL;
}

parsenode * parser::math_operand(int n){
    LOG_DEBUG("Parser: try operand "<<n);
    parsenode * a = number(n);
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

    parsenode * d = parenthesized(n);
    if(d){
        return d;
    }
    return NULL;
}

parsenode * parser::parenthesized(int n){
    LOG_DEBUG("Parser: try parenthesized "<<n);
    parsenode * a = c_operator(n,"(");
    if(a){
        parsenode * b = add_sub(n+1);
        if(b){
            parsenode * c = c_operator(n+1+b->length,")");
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

parsenode * parser::text_expression(int n){
    LOG_DEBUG("Parser: try text expression "<<n);
    parsenode * a = text_add(n);
    if(a){
        return a;
    }
    return NULL;
}

parsenode * parser::text_add(int n){
    parsenode * a = text_operand(n);
    if(a){
        string op = "+";
        parsenode * b = c_operator(n+(a->length),op);
        if(b){
            parsenode * c = text_add(n+(a->length)+1);
            if(c){
                parsenode * node = new parsenode(n,lexemetypes::TEXTOPERATION,1);
                node->push(a);
                node->push(c);
                return node;
            } else {
                //TODO: expected text error
                delete b;
            }
        }
        return a;
    }
}

parsenode * parser::text_operand(int n){
    parsenode * a = text(n);
    if(a){
        return a;
    }

    parsenode * b = number(n);
    if(b){
        return b;
    }

    parsenode * c = call(n);
    if(c){
        return c;
    }

    parsenode * d = variable(n);
    if(d){
        return d;
    }
    return NULL;
}

parsenode * parser::boolean_expression(int n){
    LOG_DEBUG("Parser: try boolean expression "<<n);
    parsenode * a = boolean_compare(n);
    if(a){
        return a;
    }
    return NULL;
}

parsenode * parser::boolean_compare(int n){
    LOG_DEBUG("Parser: try boolean compare "<<n);
    parsenode * a = boolean_operand(n);
    if(a){
        parsenode * b = c_operator(n+1,"=");
        parsenode * c = c_operator(n+2,"=");
        if(b&&c){
            delete b;
            delete c;
            parsenode * d = boolean_compare(n+3);
            if(d){
                parsenode * node = new parsenode(n,lexemetypes::BOOLEANOPERATION,2);
                node->value = "==";
                node->push(a);
                node->push(d);
                return node;
            }
        }
        return a;
    }
    return NULL;
}

parsenode * parser::boolean_operand(int n){
    parsenode * a = boolean(n);
    if(a){
        return a;
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
