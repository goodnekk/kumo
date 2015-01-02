//author: Marcel Goethals
//Lexer, takes a string and converts it into a vector of tokens.

#include "lexer.h"

bool lexer::isLetter(string c){
	//use this instead of regular expressions, it's faster and simpler and uses less code
	const static string letters[52] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	for(int i=0; i<52; i++){
		if (c==letters[i]){
			return true;
		}
	}
	return false;
}

bool lexer::isNumber(string c){
	const static string numbers[10] = {"0","1","2","3","4","5","6","7","8","9"};
	for(int i=0; i<10; i++){
		if (c==numbers[i]){
			return true;
		}
	}
	return false;
}

bool lexer::isWhitespace(string c){
	if(c==" " or c=="\t"){
		return true;
	}
	return false;
}

bool lexer::isOperator(string c){
	const static string operators[9] = {"+","-","*","/","=","<",">","&","|"};
	for(int i=0; i<9; i++){
		if (c==operators[i]){
			return true;
		}
	}
	return false;
}

bool lexer::isSeparator(string c){
	const static string operators[5] = {"(",")","{","}",","};
	for(int i=0; i<5; i++){
		if (c==operators[i]){
			return true;
		}
	}
	return false;
}

bool lexer::isNewline(string c){
	if(c=="\n"){
		return true;
	}
	return false;
}

//increments to the next character
void lexer::step(){
	if (pointer<data.length()){
		character = data.at(pointer);
		pointer++;
	} else {
		character = "\e";
	}
}

void lexer::pushToken(const int type){
	state=0;
	tokens.push_back(token(type, currentToken));
	currentToken="";
}

vector<token> lexer::getTokens(){
	LOG_DEBUG("Lexed to: "<<tokens.size()<<" tokens");
	for(int i=0; i<tokens.size(); i++){
		tokens.at(i).print(i);
	}
	return tokens;
}

void lexer::analize(){
	//initial state
	if (state==0){
		if(isLetter(character)){
			currentToken+=character;
			state=1;
			step();
		}
		else if(character=="\""){ //strings
			state=2;
			step();
		}
		else if(isNumber(character)){
			currentToken+=character;
			state=3;
			step();
		}
		else if(isWhitespace(character)){
			step();
		}
		else if(isOperator(character)){
			currentToken+=character;
			state =4 ;
			step();
		}
		else if(isSeparator(character)){
			currentToken=character;
			pushToken(tokentypes::SEPARATOR);
			step();
		}
		else if(isNewline(character)){
			pushToken(tokentypes::NEWLINE);
			step();
		}
		else if(character=="\e"){
			return;
		}
		else {

			LOG_ERROR("Lexer found unknown character: "<<character);
			return;
		}
		analize();
		return;
    }

    //name state
    if (state==1){
    	if(isLetter(character)){
    		currentToken+=character;
    		step();
    	} else {
    		pushToken(tokentypes::NAME);
    	}
    	analize();
    	return;
    }

    //string state
    if (state==2){
    	if(character=="\""){
    		pushToken(tokentypes::STRING);
    	} else {
    		currentToken+=character;
    	}
    	step();
    	analize();
    	return;
    }

    //number state
    if (state==3){
    	if(isNumber(character) or character=="."){
    		currentToken+=character;
    		step();
    	} else{
    		pushToken(tokentypes::NUMBER);
    	}
    	analize();
    	return;
    }

	//operator state
	if(state==4){
		if(isOperator(character)){
			currentToken+=character;
			step();
		}
		else{
			pushToken(tokentypes::OPERATOR);
		}
		analize();
		return;
	}
}


void lexer::lex(string input){

	data = input;
	currentToken = "";
	state = 0;
	pointer = 0;
	character = "";

	LOG_DEBUG("Lexing: "<<data);
	step();
	analize();
}
