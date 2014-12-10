#pragma once

#include <string>
#include <iostream>

using namespace std;

class token{
	private:

	public:
		int type;
		string tokenstring;
		
		token(int ty, string tok);
		void print();
};
