#ifndef H12
#define H

//#include <C:\Users\User\source\repos\seminars\q\std_lib_facilities.h>;

#include "std_lib_facilities.h"


struct Token
{
	char kind;
	double value;
	string name;
	bool type;

	Token(char ch)
		: kind{ ch }, value{ 0 }
	{ }
	Token(char k, bool ch)
		: kind{ k }, type{ ch }, value{ 0 }
	{ }

	Token(char ch, double val)
		: kind{ ch }, value{ val }
	{ }
	Token(char ch, string var)  // var
		:kind{ ch }, name{ var }
	{ }
};

class Token_stream
{
	bool full{ false };
	Token buffer{ '\0' };
public:
	Token_stream() {};

	Token get();
	void putback(Token t);
	void ignore(char ñ);
};
// Token.kind const
const char quit = 'q';
const char factor = 'F';
const char print = ';';
const char number = '8';
const char name = 'a';
const char consta = '!';
const char let = 'L';
const char help = 'H';
const char assign = 'N';
const char power = 'P';
const char koren = 'S';
const char sinxd = '$';
const char sinxr = '@';
const char degtorad = 'd';
const char radtodeg = 'r';

const bool constab = true;
const bool letb = false;

const string powers = "pow";
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string quit1 = "quit";
const string quit2 = "q";
const string help1 = "help";
const string help2 = "HELP";
const string help3 = "Help";
const string help4 = "h";
const string help5 = "H";
const string assignname = "set";
const string korens = "sqrt";
const string constanta = "const";
const string sinxrs = "sinr";
const string sinxds = "sind";
const string fact = "fact";
const string degtoradk = "degtorad";
const string radtodegk = "radtodeg"; 


#endif // H12