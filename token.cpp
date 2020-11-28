#include "C:\Users\User\source\repos\Calkulator sdacha\Debug\tokenH.h"

void Token_stream::putback(Token t)
{
	if (full)
		error("putback() into a full buffer");

	buffer = t;
	full = true;
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
	{
		if (ch == c) return;
	}
}

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin.get(ch);
		switch (ch)
		{
		case print:
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '=':
		case ',':
			//case '!':
			return Token{ ch };

		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch);
			double val;
			cin >> val;
			return Token{ number, val };
		}
		default:
			if (isalpha(ch) || ch == '_' || ch == '#' || ch == '!')
			{
				string s;
				s += ch;
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
				cin.putback(ch);

				if (s == declkey)				return Token{ let, letb };    //объ€влем переменную
				if (s == assignname)			return Token{ assign };    //измен€ем переменную
				if (s == quit1 || s == quit2)	return Token{ quit };    //выходим из программы
				if (s == korens)				return Token{ koren };    //вычисл€ем кубический корень
				if (s == help1 || s == help2 ||
					s == help3 || s == help4 ||
					s == help5)					return Token{ help };    //выводим справку о программе
				if (s == constanta)				return Token{ consta,constab };    //объ€вл€ем неизмен€емую переменную
				if (s == powers)				return Token{ power };    //возводим два int числа в степень
				if (s == sinxds)				return Token{ sinxd };    //функци€ синус с градусами
				if (s == sinxrs)				return Token{ sinxr };	  //функци€ синус с радианой
				if (s == fact)					return Token{ factor };   //функци€ факториал
				return Token{ name, s };
			}
			else if (isspace(ch)) {
				if (ch == '\n')
					return Token(print);
				else
					return get();
			}
			error("Bad token");
		}
}