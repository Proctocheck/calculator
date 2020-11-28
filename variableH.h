#ifndef H13
#define H13

#include "std_lib_facilities.h"

struct Variable
{
	string name;
	double value,value1,value2;
	bool type;
	string file;

	Variable(string n, double v, bool c)
		: name{ n }, value{ v }, type{c}
	{ }
	Variable(double v)
		: value{ v }
	{ }
};

class Symbol_table {
public:
	double get(string s);
	bool is_declared(string s) const;
	double define(string var, double val, bool c);
	double change(string var, double val);
private:
	vector<Variable> var_table;
};


#endif // H13