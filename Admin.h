#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include"Data.h"
#include"User.h"
using namespace std;

class Administrator
{
public:
	bool Admin_Login(string name, string code);
	void Admin_Menu();
	void All_Commodity();
	void Search_Commodity();
	void Delete_Commodity();
	void All_Orders();
	void All_Users();
	void Ban_Users();
private:
	string admin_name = "admin";
	string admin_code = "123456";
};

