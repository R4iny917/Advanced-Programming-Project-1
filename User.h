#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"Data.h"
#include<sstream>
#include<algorithm>
#include"SQLinterpreter.h"
#include <stdio.h>
#include <math.h>
using namespace std;

struct user
{
	string ID;
	string U_name;
	string U_password;
	string U_phonenumber;
	string U_address;
	double balance = 0.0;
	string U_state = "active";
};

class Users
{
public:
	int U_Login(string name, string code);
	void U_Register();
	void U_Menu();
	void Self_Info_Mag(user& someone);
	void Check_Info(user& someone);
	void Modify_Info(user& someone);
	void Recharge(user& someone);
	void Change_Name(user& someone);
	void Change_Phone(user& someone);
	void Change_Address(user& someone);
};

class Buyers :public Users
{
public:
	void Buyer_Menu();
	void Check_Commodity_List();
	void Buy_Commodity(user& someone);
	void Search_Commodity();
	void Check_History_Orders(user& someone);
	void Check_Commodity_Info(user& someone);
};

class Sellers :public Users
{
public:
	void Seller_Menu();
	void Publish_Commodity(user& someone);
	void Check_Commodity(user& someone);
	void Modify_Commodity_Info(user& someone);
	void Off_Commodity(user& someone);
	void Check_History_Orders(user& someone);
};

struct recharge
{
	double money;
	string date;
	string ID;
};

