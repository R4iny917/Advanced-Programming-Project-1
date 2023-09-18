#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"SQLinterpreter.h"
#include"Data.h"
#include"User.h"
using namespace std;
extern vector<Commodity>Com;
extern vector<Order>Ord;
extern vector<user>people;
extern vector<recharge>rechar;
string temp_date()
{
	time_t t = time(0);
	tm* now = localtime(&t);
	stringstream ss;
	string date, temp;
	ss << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday;
	ss >> date; ss.clear();
	date = date + " ";
	ss << now->tm_hour;
	ss >> temp; ss.clear();
	if (temp.size() == 1)temp = "0" + temp;
	if (temp.size() == 0)temp = "00";
	date = date + temp + ":";
	temp.clear(); ss.clear();
	ss << now->tm_min;
	ss >> temp;
	if (temp.size() == 1)temp = "0" + temp;
	if (temp.size() == 0)temp = "00";
	date = date + temp + ":";
	temp.clear(); ss.clear();
	ss << now->tm_sec;
	ss >> temp;
	if (temp.size() == 1)temp = "0" + temp;
	if (temp.size() == 0)temp = "00";
	date = date + temp + ": ";
	temp.clear();
	return date;
};
void SQL::SQL_commodity_select()
{
	string date = temp_date();
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	string commond = "SELECT * FROM commodity";
	ofile << date << commond<<endl;
	ofile.close();
}
void SQL::SQL_commodity_name_select(string name)
{
	string date = temp_date();
	string commond = "SELECT * FROM commodity WHERE name CONTAINS ";
	commond += name;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond<<endl;
	ofile.close();
}
void SQL::SQL_order_select()
{
	string date = temp_date();
	string commond = "SELECT * FROM order";
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
};
void SQL::SQL_user_select()
{
	string date = temp_date();
	string commond = "SELECT * FROM user";
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
};
void SQL::SQL_commodity_ID_select(string ID)
{
	string date = temp_date();
	string commond = "SELECT * FROM commodity WHERE comomdityID CONTAINS ";
	commond += ID;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
};


void SQL::SQL_commodity_state_update(Commodity& com)
{
	string date = temp_date();
	string commond = "UPDATE commodity SET commodity state = removed WHERE commodityID = ";
	commond += com.C_ID;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
};
void SQL::SQL_user_state_update(string ID)
{
	string date = temp_date();
	string commond1 = "UPDATE commodity SET commodity state = removed WHERE sellerID = ";
	commond1 += ID;
	string commond2 = "UPDATE user SET user state = banned WHERE userID = ";
	commond2 += ID;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond1 << endl;
	ofile << date << commond2 << endl;
	ofile.close();
};
void SQL::SQL_commodity_price_update(Commodity& com)
{
	string date = temp_date();
	string commond = "UPDATE commodity SET price = ";
	string temp_price;stringstream ss; 
	ss << fixed << setprecision(1) << com.C_price;
	ss >> temp_price;
	commond = commond + temp_price +" WHERE commodityID = "+com.C_ID;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
};
void SQL::SQL_commodity_description_update(Commodity& com)
{
	string date = temp_date();
	string commond = "UPDATE commodity SET description = ";
	commond = commond + com.C_description + " WHERE commodityID = " + com.C_ID;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
}
void SQL::SQL_commodity_num_update(Commodity& com)
{
	string date = temp_date();
	string commond = "UPDATE commodity SET number =  ";
	commond += com.C_ID;
	commond += " WHERE commodityID = ";
	commond += com.C_ID;
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << endl;
	ofile.close();
	if (com.C_number == 0)
	{
		string new_commond = "UPDATE commodity SET commodity state = removed WHERE commodityID = ";
		new_commond += com.C_ID;
		ofile.open("commond.txt", ios::app);
		ofile << date << new_commond << endl;
		ofile.close();
	}
};

void SQL::SQL_commodity_values_insert(Commodity& com)
{
	string date = temp_date();
	string commond = "INSERT INTO commodity VALUES ";
	string temp_price;
	stringstream ss; ss << fixed << setprecision(1) << com.C_price;
	ss >> temp_price;
	ss.clear();
	ss << com.C_number;
	string temp_num; ss >> temp_num;
	string temp = "(" + com.C_name + "," + temp_price + "," + temp_num + "," + com.C_description + ")";
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << temp << endl;
	ofile.close();
};
void SQL::SQL_order_values_insert(Order& ord)
{
	string date = temp_date();
	string commond = "INSERT INTO order VALUES ";
	stringstream ss; string temp_price; string temp_num;
	ss << fixed <<setprecision(1)<<ord.unitPrice; ss >> temp_price; ss.clear();
	ss << ord.number; ss >> temp_num; ss.clear();
	string ord_info = "(" + ord.O_ID + "," + ord.C_ID + "," + temp_price + "," + temp_num + "," + ord.O_date + "," + ord.buyerID + "," + ord.sellerID + ")";
	ofstream ofile;
	ofile.open("commonds.txt", ios::app);
	ofile << date << commond << ord_info << endl;
	ofile.close();
};
