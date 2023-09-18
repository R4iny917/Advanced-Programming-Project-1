#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<stack>
#include<iomanip>
using namespace std;

class Calculator
{
public:
	Calculator() { result = 0; }
	~Calculator() {  }
	void setData(string& calculation) { this->calculation = calculation; }
	void Change();
	void Compute();
	double Getm_result() { return result; }
	bool get_state() { return state; }
	double Complete()
	{
		string calculation;
		getline(cin, calculation);
		setData(calculation);
		Change();
		if (get_state() == false)cout << "Wrong Operation!" << endl;
		else
		{
			legalty();
			Compute();
			if (get_state() == false) cout << "Wrong Operation!" << endl;
			else
			{
				double m; stringstream ss;
				ss << fixed << setprecision(1) << Getm_result();
				ss >> m;
				return m;
			}
		}
	}
	void legalty();
private:
	double result;
	bool state = true;
	string calculation;
};