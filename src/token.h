#pragma once

#include <string>
#include "log.h"

using namespace std;

class token{
	private:

	public:
		int type;
		string tokenstring;

		token(int ty, string tok);
		void print(int i);
};
