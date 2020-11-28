#include "variableH.h";
#include "tokenH.h";

double Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s)
		{
			return var_table[i].value;
		}
	error("get: undefined name ", s);
}

bool Symbol_table::is_declared(string s) const
{
	for (int i = 0; i < var_table.size(); ++i)
	{
		if (var_table[i].name == s) return true;
	}
	return false;
}

double Symbol_table::define(string var, double val, bool c) //поменять на bool
{
	if (is_declared(var))
		error(var, " declared twice");
	var_table.push_back(Variable{ var, val , c});
	return val;
}

double Symbol_table::change(string var, double val)
{
	if (!is_declared(var))
		error("set: undefined name ", var);
	
	for (int i = 0; i < var_table.size(); ++i)
	{
		if (var_table[i].type)
			if (var_table[i].name == var)
				error("set: can't change the value of a constant");

		if (var_table[i].name == var) var_table[i].value = val;
	}
	return val;
}