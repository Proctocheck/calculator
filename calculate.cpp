#include "tokenH.h"
#include "variableH.h"
#include "std_lib_facilities.h"

/*
----------------------------------------------------------------------------------------

>>> Grammar used in this program to handle expressions and features <<<

Calculator:
Объявление
Переназначение
Выход
Ответ
Помощь

Вывод:
";"   '\n'

Вывод:
"q"   "quit"

Statement:
Объявление
Переназначение
Выражение

Объявление:
"let" Name "=" Выражение

Перенизначение:
"set" Name "=" Выражение

Объявление констант:
"const" Name "=" Выражение

Выражение:
Терм
Выражение "+" Терм
Выражение "-" Терм

Терм:
Перв. выражение
Терм "*" Перв. выражение
терм "/" Перв. выражение
Терм "%" Перв. выражение

Перв. выражение:
Number
Name
"+" Первичное выражение
"-" Первичное выражение
"pow(" Первичное выражение "," Первичное выражение ")" - степень
sinr = '(' Первичное выражение ')'
sing = '(' Первичное выражение * pi / 180 ')'
*/


double assignset(Token_stream& ts, Symbol_table& sym);

double expression(Token_stream& ts, Symbol_table& sym);


double factorial(int a)
{
	int b = 1;
	for (int i = 1; i <= a; i++)
		b *= i;
	return b;
}


double primary(Token_stream& ts, Symbol_table& sym)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression(ts, sym);
		t = ts.get();
		if (t.kind != ')')
			error(") expected");
		return d;
	}
	case '-':
		return -primary(ts, sym);
	case '+':
		return +primary(ts, sym);
	case number:
		return t.value;
	case name:
		return sym.get(t.name);
	case koren:
	{
		double d = primary(ts, sym);
		if (d < 0) error("primary below zero");
		return sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(')
			error("power_primary: '(' expected");

		double d1 = expression(ts, sym);

		t = ts.get();
		if (t.kind != ',')
			error("power_primary: ',' expected");

		double d2 = expression(ts, sym);

		t = ts.get();
		if (t.kind != ')')
			error("power_primary: ')' expected");

		int i = narrow_cast<int>(d2);
		return pow(d1, i);
	}
	case sinxr:
	{
		t = ts.get();
		if (t.kind != '(')
			error("power_primary: '(' expected");

		double d1 = expression(ts, sym);

		t = ts.get();
		if (t.kind != ')')
			error("power_primary: ')' expected");

		return sin(d1); // в радианах
	}
	case sinxd:
	{
		double pi = 3.141592653589793;
		t = ts.get();
		if (t.kind != '(')
			error("power_primary: '(' expected");

		double d1 = expression(ts, sym);

		t = ts.get();
		if (t.kind != ')')
			error("power_primary: ')' expected");

		return sin(d1 * pi / 180); // в радианах
	}
	case factor:
	{
		t = ts.get();
		if (t.kind != '(')
			error("power_primary: '(' expected");

		double d1 = expression(ts, sym);
		int i = narrow_cast<int>(d1);

		t = ts.get();
		if (t.kind != ')')
			error("power_primary: ')' expected");
		if (i <= 0) error("Znachenie factoriala <=0");
		return factorial(i);
	}
	default:
		error("primary expected");
	}
}


double term(Token_stream& ts, Symbol_table& sym)
{
	double left = primary(ts, sym);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '*':
			left *= primary(ts, sym);
			break;
		case '/':
		{
			double d = primary(ts, sym);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = primary(ts, sym);
			if (d == 0) error("divide by zero");
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(d);
			left = i1 % i2;
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}


double expression(Token_stream& ts, Symbol_table& sym)
{
	double left = term(ts,sym);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '+':
			left += term(ts, sym);
			break;

		case '-':
			left -= term(ts, sym);
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}


double declaration(Token_stream& ts, Symbol_table& sym, bool type)
{
	Token t = ts.get();

	if (t.kind != name)
		error("name expected in declaration");

	string var = t.name;
	if (sym.is_declared(var))
		error(var, " declared twice");

	t = ts.get();
	if (t.kind != '=')
		error("'=' missing in declaration of ", var);

	return sym.define(var, expression(ts, sym),type);
}


double assignset(Token_stream& ts, Symbol_table& sym)
{
	Token t = ts.get();
	if (t.kind != name)
		error("no one cosnt has this name");

	string var = t.name;
	if (!sym.is_declared(var))
		error("didn't declared!!!");

	t = ts.get();
	if (t.kind != '=')
		error("'=' missing in declaration of ", var);
	
	return sym.change(var,expression(ts, sym));
}


double statement(Token_stream& ts, Symbol_table& sym)
{
	Token t = ts.get();
	bool type;
	switch (t.kind)
	{
	case let:
	case consta:
		return declaration(ts,sym,t.type);
	case assign:
		return assignset(ts, sym);
	default:
		ts.putback(t);
		return expression(ts, sym);
	}
}


void clean_up_mess(Token_stream& ts1)
{
	ts1.ignore(print);
}


void calculate(Token_stream& ts1, Symbol_table& sym1)
{
	while (true)
		try
		{
		cout << prompt;
		Token t = ts1.get();
		while (t.kind == print)
			t = ts1.get();
		if (t.kind == quit) return;
		else if (t.kind == help) {
			cout << "#################################################__this is calculator__#################################################" <<endl
				 << "quit: 'quit','q'" << endl
				 << "help: 'h','help','Help','HELP'" << endl
				 << "function: fact(int),sin(deg and rad),pow(int,int),sqrt(|x|)(t.e. x>=0)" << endl
				 << "statement:# name = 'value', N name = 'value'" << endl
				 << "operation: '+','-','*','/','%'\n";
		}
		else 
		{
			ts1.putback(t);
			cout << result << statement(ts1, sym1) << endl;
		}
		}
	catch (runtime_error & e)
	{
		cerr << e.what() << endl;
		clean_up_mess(ts1);
	}
}


int main()
{

	try
	{
	Token_stream ts;
	Symbol_table sym;
		sym.define("pi", 3.141592653589793,true);
		sym.define("e", 2.718281828459045,true);
		
		calculate(ts, sym);
	}
	catch (exception & e)
	{
		cerr << "exception: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Oops, unknown exception" << endl;
		return 2;
	}
}