#include<iostream>
#include<string>
#include<sstream>
#include<stack>
#include"Calculator.h"
using namespace std;

bool IsPop(char a, char b)
{
	if (b == '(') return false;
	if (a == '*' || a == '/')
	{
		if (b == '+' || b == '-')
			return false;
		else
			return true;
	}
	return true;
}
void Calculator::legalty()
{
	string judge = calculation;
	int dot = 0;
	int number = 0;
	for (int i = 0; i < judge.size(); ++i)
	{
		if (isdigit(judge[i]))
		{
			while (judge[i] != ' ')
			{
				if (judge[i] == '.')++dot;
				if (judge[i] == '.' && !isdigit(judge[i + 1]))number = 1;
				++i;
			}
			if (dot > 1 || number == 1)state = false;
		}
		dot = 0;
	}
}
void Calculator::Change()
{
	string postfix;
	stack<char> symbol;
	for (int i = 0; i < calculation.size(); ++i)
	{
		if (isdigit(calculation[i]) && calculation[i + 1] == ' ')
		{
			++i;
			int measure = 0;
			while (i < calculation.size() && !isdigit(calculation[i]))
			{
				if (calculation[i] == '+' || calculation[i] == '-' || calculation[i] == '*' || calculation[i] == '/' || calculation[i] == ')')
					++measure;
				++i;
			}
			if (measure == 0)state = false;
		}
		if (calculation[i] == '.' && calculation[i + 1] == ' ')state = false;
	}
	int index = 0;
	if (!calculation.empty())
	{
		while ((index = calculation.find(' ', index)) != string::npos)
		{
			calculation.erase(index, 1);
		}
	}
	for (int i = 0; i < calculation.size() - 1; ++i)
		if ((calculation[i] == '(' && calculation[i + 1] == ')' )|| (calculation[i] == ')' &&calculation[i + 1] == '('))
			state = false;
	int  j = 0, k = 0, l = 0;
	for (int i = 0; i < calculation.size(); ++i)
	{
		char temp = calculation[i];
		if (i == 0 && calculation[0] == '-' && isdigit(calculation[1]))
		{
			postfix.push_back('-'); ++i;
			while (isdigit(calculation[i]) || calculation[i] == '.')
			{
				postfix.push_back(calculation[i]);
				++i;
			}
			postfix.push_back(' ');
			--i; ++l;
		}
		else if (temp == '(' && calculation[i + 1] == '-')
		{
			++j;
			symbol.push('('); ++i;
			postfix.push_back('-'); ++i;
			while (isdigit(calculation[i]) || calculation[i] == '.')
			{
				postfix.push_back(calculation[i]);
				++i;
			}
			postfix.push_back(' ');
			--i; ++l;

		}
		else if (temp == '(')
		{
			symbol.push(temp);
			++j;
		}
		else if (temp == ')')
		{
			--j;
			while (symbol.empty() == false && symbol.top() != '(')
			{
				postfix.push_back(symbol.top());
				postfix.push_back(' ');
				symbol.pop();
			}
			if (!symbol.empty())symbol.pop();
		}
		else if (isdigit(temp))
		{
			while (isdigit(calculation[i]) || calculation[i] == '.')
			{
				postfix.push_back(calculation[i]);
				++i;
			}
			postfix.push_back(' ');
			--i; ++l;
		}
		else
		{
			switch (temp)
			{
			case '+':case '-':case '*':case '/':
				if (symbol.empty())
				{
					symbol.push(temp);
					--l;
				}
				else
				{
					if (IsPop(temp, symbol.top()))
					{
						while (!symbol.empty() && symbol.top() != '(')
						{
							postfix.push_back(symbol.top());
							postfix.push_back(' ');
							symbol.pop();
						}
					}
					symbol.push(temp);
					--l;
				}

				break;
			default:{state = false; break; }
			}
		}
	}
	while (!symbol.empty())
	{
		if (symbol.top() == '(' || symbol.top() == ')')state = false;
		postfix.push_back(symbol.top());
		postfix.push_back(' ');
		symbol.pop();
	}
	if (l <= 0 || j != 0) this->state = false;
	//cout << postfix << endl;
	//cout << state<<endl;
	this->calculation = postfix;
}
void Calculator::Compute()
{
	stack<double> st;
	stringstream ss;
	string final = calculation;
	while (!final.empty())
	{
		ss << final;
		if (isdigit(final[0]))
		{
			double tmp;
			ss >> tmp;
			while (final[0] != ' ')
				final.erase(0, 1);
			final.erase(0, 1);
			st.push(tmp);
		}
		else if (final[0] == '-' && isdigit(final[1]))
		{
			double tmp;
			ss >> tmp;
			while (final[0] != ' ')
				final.erase(0, 1);
			final.erase(0, 1);
			st.push(tmp);
		}
		else
		{
			double tmp = 0;
			char str;
			ss >> str;
			final.erase(0, 2);
			switch (str)
			{
			case '+':
				if (st.size() < 2)state = false;
				else {
					tmp += st.top();
					st.pop();
					tmp += st.top();
					st.pop();
					st.push(tmp);
				}
				break;
			case '-':
				if (st.size() < 2)state = false;
				else {
					tmp -= st.top();
					st.pop();
					tmp += st.top();
					st.pop();
					st.push(tmp);
				}
				break;
			case '*':
				if (st.size() < 2)state = false;
				else {
					tmp = st.top();
					st.pop();
					tmp *= st.top();
					st.pop();
					st.push(tmp);
				}
				break;
			case '/':
				if (st.size() < 2)state = false;
				else {
					tmp = st.top();
					st.pop();
					if (tmp != 0)
					{
						tmp = st.top() / tmp;
						st.pop();
						st.push(tmp);
					}
					else
						state = false;
				}
				break;
			default:break;
			}
		}
		ss.clear();
	}
	if (st.size() > 1)state = false;
	if (state == true)
	{
		result = st.top();
		st.pop();
	}
}
