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

				if (s == declkey)				return Token{ let, letb };    //�������� ����������
				if (s == assignname)			return Token{ assign };    //�������� ����������
				if (s == quit1 || s == quit2)	return Token{ quit };    //������� �� ���������
				if (s == korens)				return Token{ koren };    //��������� ���������� ������
				if (s == help1 || s == help2 ||
					s == help3 || s == help4 ||
					s == help5)					return Token{ help };    //������� ������� � ���������
				if (s == constanta)				return Token{ consta,constab };    //��������� ������������ ����������
				if (s == powers)				return Token{ power };    //�������� ��� int ����� � �������
				if (s == sinxds)				return Token{ sinxd };    //������� ����� � ���������
				if (s == sinxrs)				return Token{ sinxr };	  //������� ����� � ��������
				if (s == fact)					return Token{ factor };   //������� ���������
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