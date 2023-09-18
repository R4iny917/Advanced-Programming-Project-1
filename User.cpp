#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<ctime>
#include"User.h"
#include"Data.h"
#include<iomanip>
#include<map>
#include<algorithm>
#include"Calculator.h"
#include <stdio.h>
#include <math.h>
using namespace std;

vector<user>people;
vector<Commodity>Com;
vector<Order>Ord;
vector<recharge>rechar;

bool comp(const Commodity& a, const Commodity& b)
{
	return a.C_price > b.C_price;
}
bool bomp(const Commodity& a, const Commodity& b)
{
	return a.C_price > b.C_price;
}
bool comp3(const Commodity& a, const Commodity& b)
{
	return a.C_number > b.C_number;
}
int Users::U_Login(string name, string code)
{
	for (int i = 0; i < people.size(); ++i)
	{
		if (name == people.at(i).U_name && code == people.at(i).U_password && people.at(i).U_state == "active")
			return 1;
		if (name == people.at(i).U_name && code == people.at(i).U_password && people.at(i).U_state == "inactive")
			return 2;
	}
	return 0;
};
void Users::U_Register()
{
	string pw1, pw2;
	user person;
	cout << "Please enter you user name:";
flag:
	cin >> person.U_name;
	for (int i = 0; i < people.size(); ++i)
		if (people.at(i).U_name == person.U_name)
		{
			cout << "The name has already existed,please reenter your name:";
			goto flag;
		}
	cout << "Please enter your phonenumber:"; cin >> person.U_phonenumber;
	cout << "Please enter your address:"; cin >> person.U_address;
flag1:
	cout << "Please enter your password:"; cin >> pw1;
	cout << "Please enter your password again:"; cin >> pw2;
	if (pw1 != pw2)
	{
		cout << "What you have entered are not same."; goto flag1;
	}
	cout << "You have registered successfully!"<<endl;
	person.U_password = pw1;
	int i = people.size()+1;
	int p = i / 100; int q = (i / 10) % 10; i = i % 10;
	stringstream ss;
	ss << p << q << i;
	string str1, str2, str3;
	ss >> str1 >> str2 >> str3;
	string ID;
	ID = "U" + str1 + str2 + str3;
	person.ID = ID;
	people.push_back(person);
	ofstream ofile;
	ofile.open("user.txt", ios::app);
	if(person.ID =="U001")ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	ofile << person.ID << "," << person.U_name << "," << person.U_password << "," << person.U_phonenumber << "," << person.U_address <<","<<person.balance<<","<<person.U_state << endl;
	ofile.close();
};
void Users::U_Menu()
{
	cout << "==============================================================" << endl;
	cout << "1.Buyer Mode" << " " << "2.Seller Mode" << " " << "3.Self Infomation Management" << " " << "4.Exit" << endl;
	cout << "==============================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "Please choose your operation:";
};
void Users::Self_Info_Mag(user& someone)
{
	while (true)
	{
		cout << "==========================================================================" << endl;
		cout << "1.Check Information 2.Modify Information 3.Recharge 4.Return to main Menu " << endl;
		cout << "==========================================================================" << endl;
		cout << endl << endl << "Please choose your operation:";
		string option;
	flag:(std::cin >> option).get();
		if (option.size() != 1)
		{
			cout << "Your input is not legal. Please choose your option again:";
			goto flag;
		}
		else
		{
			char opt = option[0];
			switch (opt)
			{
			case '1':Check_Info(someone); break;
			case '2':Modify_Info(someone); break;
			case '3':Recharge(someone); break;
			case '4':return;
			default:cout << "Not a valid request" << endl; break;
			}
		}
	}
};
void Users::Check_Info(user& someone)
{
	ifstream ifile;
	ifile.open("recharge.txt", ios::in);
	if (ifile.is_open())
	{
		rechar.clear();
		while (!ifile.eof())
		{
			recharge new_recharge;
			string temp_money;
			getline(ifile, temp_money, ',');
			if (ifile.eof())break;
			getline(ifile, new_recharge.date, ',');
			getline(ifile, new_recharge.ID);
			stringstream ss; ss << temp_money; ss >> new_recharge.money;
			rechar.push_back(new_recharge);
		}
	}
	ifile.close();
	string calculation ="0"; int x = 0;
	string record;
	for(int i = 0; i < rechar.size();++i)
		if (rechar.at(i).ID == someone.ID)
		{
			x = 1;
			if (x == 1)
			{
				calculation += '+';
			}
			stringstream ss;
			ss << rechar.at(i).money;
			ss >> record;
			calculation += record;
		}
	//cout << calculation << endl;
	map<int, vector<double>>map_order;
	map<int, vector<double>>::iterator iter;
	int y = 0;
	//cout << Ord.at(4).unitPrice << endl;
	for (int i = 0; i < Ord.size(); ++i)
	{
		if (Ord.at(i).buyerID == someone.ID)
		{
			for (iter = map_order.begin(); iter != map_order.end(); ++iter)
			{
				if (iter->first == Ord.at(i).number)
				{
					//cout << -Ord.at(i).unitPrice << endl;
					double temp = -Ord.at(i).unitPrice;
					iter->second.push_back(temp);
					y = 1;
				}
			}
			if (y == 0)
			{
				//cout << -Ord.at(i).unitPrice << endl;
				vector<double>new_vec;
				new_vec.push_back(-Ord.at(i).unitPrice);
				map_order.insert(make_pair(Ord.at(i).number, new_vec));
			}
		}
		if (Ord.at(i).sellerID == someone.ID)
		{
			for (iter = map_order.begin(); iter != map_order.end(); ++iter)
			{
				if (iter->first == Ord.at(i).number)
				{
					//cout << Ord.at(i).unitPrice << endl;
					iter->second.push_back(Ord.at(i).unitPrice);
					y = 1;
				}
			}
			if (y == 0)
			{
				//cout << Ord.at(i).unitPrice << endl;
				vector<double>new_vec;
				new_vec.push_back(Ord.at(i).unitPrice);
				map_order.insert(make_pair(Ord.at(i).number, new_vec));
			}
		}
		y = 0;
	}
	int n = -1;
	stringstream ss;string temp;
	for (iter = map_order.begin(); iter != map_order.end(); ++iter)
	{
		if (x == 1)calculation += "+";
		ss <<iter->first;
		ss >> temp;
		ss.clear();
		calculation = calculation + temp +"*(";
		temp.clear();
		ss << iter->second.back();
		ss >> temp;
		calculation += temp;
		temp.clear(); ss.clear();
		iter->second.pop_back();
		while (!iter->second.empty())
		{
			ss << iter->second.back();
			ss >> temp;
			if(iter->second.back()<0) calculation += temp;
			else 
				calculation = calculation = calculation + "+" + temp;
			ss.clear();
			temp.clear();
			iter->second.pop_back();
		}
		calculation += ")";
	}
	//cout << calculation << endl;
	Calculator ca;
	ca.setData(calculation);
	ca.Change();
	ca.Compute();
	someone.balance = ca.Getm_result();
	cout << "*************************" << endl;
	cout << "User name:" << someone.U_name << endl;
	cout << "Telephone number:" << someone.U_phonenumber << endl;
	cout << "Address:" << someone.U_address << endl;
	cout << "Balance:" << fixed << setprecision(1) << someone.balance << endl;
	cout << "*************************" << endl;
	ofstream ofile;
	ofile.open("user.txt", ios::out);
	ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	for (int i = 0; i < people.size(); ++i)
		ofile << people.at(i).ID << "," << people.at(i).U_name << "," << people.at(i).U_password << "," << people.at(i).U_phonenumber << "," << people.at(i).U_address << "," << people.at(i).balance << "," << people.at(i).U_state << endl;
	ofile.close();
};
void Users::Modify_Info(user& someone)
{
	cout << "Which information do you want to modify(1.User name 2.Phone number 3.Address):";
	char choice;
	(cin >> choice).get();
	switch (choice)
	{
	case '1': Change_Name(someone); break; 
	case '2': Change_Phone(someone); break;
	case '3': Change_Address(someone); break; 
	default:cout << "Wrong Operation." << endl; break;
	}
};
void Users::Recharge(user& someone)
{
	cout << "Please recharge your money:"; double money; 
	cin >> money;
	if (money <= 0 ||fmod(money*10,1) != 0)
	{
		while (money <= 0)
		{
			cout << "Your input is not legal. Please recharge your money again:";
			cin >> money;
		}
	}
	money = round(money * 10) / 10.0;
	someone.balance += money;
	cout << "Successfully!Now your balance is:" << fixed << setprecision(1) << someone.balance << endl << endl;
	ofstream ofile;
	ofile.open("user.txt", ios::out);
	ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	for (int i = 0; i < people.size(); ++i)
		ofile << people.at(i).ID << "," << people.at(i).U_name << "," << people.at(i).U_password << "," << people.at(i).U_phonenumber << "," << people.at(i).U_address << "," << people.at(i).balance << "," << people.at(i).U_state << endl;
	ofile.close();
	string date;
	time_t t = std::time(0);
	tm* now = std::localtime(&t);
	stringstream ss;
	ss << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
	ss >> date;
	recharge new_recharge;
	new_recharge.date = date; new_recharge.ID = someone.ID; new_recharge.money = money;
	ofile.open("recharge.txt", ios::app);
	ofile << money << ',' << date <<','<<someone.ID<< endl;
	ofile.close();
	rechar.push_back(new_recharge);
};
void Users::Change_Name(user& someone)
{
	cout << "Please modify your name:";
	string name; 
flag:getline(cin,name);
	for(int i = 0; i < people.size();++i)
		if (name == people.at(i).U_name)
		{
			cout << "This name has been occupied.Please retype your name:" ;
			goto flag;
		}
	someone.U_name = name;
	cout << "Successful!" << endl;
	ofstream ofile;
	ofile.open("user.txt", ios::out);
	ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	for(int i = 0; i < people.size();++i)
		ofile << people.at(i).ID << "," << people.at(i).U_name << "," << people.at(i).U_password << "," << people.at(i).U_phonenumber << "," << people.at(i).U_address << "," << people.at(i).balance << "," << people.at(i).U_state << endl;
	ofile.close();
};
void Users::Change_Phone(user& someone)
{
	cout << "Please modify your phone number:";
	string new_number; cin >> new_number;
	someone.U_phonenumber = new_number;
	cout << "Successful!" << endl;
	ofstream ofile;
	ofile.open("user.txt", ios::out);
	ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	for (int i = 0; i < people.size(); ++i)
		ofile << people.at(i).ID << "," << people.at(i).U_name << "," << people.at(i).U_password << "," << people.at(i).U_phonenumber << "," << people.at(i).U_address << "," << people.at(i).balance << "," << people.at(i).U_state << endl;
	ofile.close();
};
void Users::Change_Address(user& someone)
{
	cout << "Please modify your address:";
	string new_address; getline(cin, new_address);
	someone.U_address = new_address;
	cout << "Successful!" << endl;
	ofstream ofile;
	ofile.open("user.txt", ios::out);
	ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	for (int i = 0; i < people.size(); ++i)
		ofile << people.at(i).ID << "," << people.at(i).U_name << "," << people.at(i).U_password << "," << people.at(i).U_phonenumber << "," << people.at(i).U_address << "," << people.at(i).balance << "," << people.at(i).U_state << endl;
	ofile.close();
};


void Buyers::Buyer_Menu()
{
	cout << "===================================================================================================================" << endl;
	cout << "1.Commodity list 2.Buy commodity 3.Search commodity 4.Check history orders 5.Check commodity infomation 6.Exit"<< endl;
	cout << "===================================================================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "Please choose your operation:";
};
void Buyers::Check_Commodity_List()
{
	cout << "Please select your view order(1.date 2.descending 3.ascending):"; int num; cin >> num;
	if (num == 1) 
	{
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		for (int i = 0; i < Com.size(); ++i)
			if (Com.at(i).C_state == "onSale")
			{
				cout << Com.at(i).C_ID << "           " << Com.at(i).C_name;
				for (int j = 0; j < 20 - Com.at(i).C_name.size(); ++j)cout << " ";
				cout << fixed << setprecision(1) << Com.at(i).C_price;
				stringstream ss; string temp_balance; ss << fixed << setprecision(1) << Com.at(i).C_price; ss >> temp_balance;
				for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
				cout << Com.at(i).C_Date;
				for (int j = 0; j < 15 - Com.at(i).C_Date.size(); ++j)cout << " ";
				cout << Com.at(i).Seller_ID << endl;
			}
		cout << "***********************************************************************" << endl << endl;
	}
	else if (num == 2)
	{
		vector<Commodity>des_com;
		for (int i = 0; i < Com.size(); ++i)
			des_com.push_back(Com.at(i));
		sort(des_com.begin(), des_com.end(), bomp);
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		for (int i = 0; i < Com.size(); ++i)
			if (des_com.at(i).C_state == "onSale")
			{
				cout << des_com.at(i).C_ID << "           " << des_com.at(i).C_name;
				for (int j = 0; j < 20 - des_com.at(i).C_name.size(); ++j)cout << " ";
				cout << fixed << setprecision(1) << des_com.at(i).C_price;
				stringstream ss; string temp_balance; ss << fixed << setprecision(1) << des_com.at(i).C_price; ss >> temp_balance;
				for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
				cout << des_com.at(i).C_Date;
				for (int j = 0; j < 15 - des_com.at(i).C_Date.size(); ++j)cout << " ";
				cout << des_com.at(i).Seller_ID << endl;
			}
		cout << "***********************************************************************" << endl << endl;
	}
	else if (num == 3)
	{
		vector<Commodity>asc_com;
		for (int i = 0; i < Com.size(); ++i)
			asc_com.push_back(Com.at(i));
		sort(asc_com.begin(), asc_com.end(), comp);
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		for (int i = 0; i < Com.size(); ++i)
			if (asc_com.at(i).C_state == "onSale")
			{
				cout << asc_com.at(i).C_ID << "           " << asc_com.at(i).C_name;
				for (int j = 0; j < 20 - asc_com.at(i).C_name.size(); ++j)cout << " ";
				cout << fixed << setprecision(1) << asc_com.at(i).C_price;
				stringstream ss; string temp_balance; ss << fixed << setprecision(1) << asc_com.at(i).C_price; ss >> temp_balance;
				for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
				cout << asc_com.at(i).C_Date;
				for (int j = 0; j < 15 - asc_com.at(i).C_Date.size(); ++j)cout << " ";
				cout << asc_com.at(i).Seller_ID << endl;
			}
		cout << "***********************************************************************" << endl << endl;
	}
	SQL interpreter;
	interpreter.SQL_commodity_select();
}
void Buyers::Buy_Commodity(user& someone)
{
	string ID, date; int num;
	time_t t = std::time(0);
	tm* now = std::localtime(&t);
	stringstream ss;
	ss << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
	ss >> date; ss.clear();
	cout << "Please choose your commodity ID:"; cin >> ID;
	cout << "Please choose your quantity:"; cin >> num;
	int i = 0;
	for (int j = 0; j < Com.size(); ++j)
	{
		if (Com.at(j).C_ID == ID)
		{
			i = j;
			break;
		}
	}
	cout << "******************************" << endl;
	cout << "Transaction warning!" << endl;
	cout << "Transaction date:" << date << endl;
	cout << "Transaction quantity:" << num << endl;
	double temp = someone.balance - Com.at(i).C_price * num;
	if (temp < 0)
	{
		cout << "Transaction state: Failed" << endl;
		cout << "Your balance is not enough." << endl;
	}
	else if (Com.at(i).C_state == "removed")cout << "The commodities have been removed." << endl;
	else if (num > Com.at(i).C_number)cout << "The commodities are not enough." << endl;
	else
	{
		cout << "Transaction state: Successful." << endl;
		cout << "Your balance:" << fixed << setprecision(1) << temp << endl;
		temp = round(temp * 10) / 10.0;
		someone.balance = temp;
		int k = 0;
		for (int j = 0; j < people.size(); ++j)
		{
			if (Com.at(i).C_ID == people.at(j).ID)
			{
				k = i; break;
			}
		}
		people.at(k).balance += Com.at(i).C_price * num;
		Com.at(i).C_number -= num;
		if (Com.at(i).C_number == 0)Com.at(i).C_state = "removed";
		SQL interpreter;
		interpreter.SQL_commodity_num_update(Com.at(i));
		ofstream ofile;
		ofile.open("user.txt", ios::out);
		ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
		for (int j = 0; j < people.size(); ++j)
			ofile << people.at(j).ID << "," << people.at(j).U_name << "," << people.at(j).U_password << "," << people.at(j).U_phonenumber << "," << people.at(j).U_address << "," << people.at(j).balance << "," << people.at(j).U_state << endl;
		ofile.close();
		ofile.open("commodity.txt", ios::out);
		ofile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
		for (int j = 0;  j< Com.size(); ++j)
			ofile << Com.at(j).C_ID << ',' << Com.at(j).C_name << ',' << Com.at(j).C_price << ',' << Com.at(j).C_number << ',' << Com.at(j).C_description << ',' << Com.at(j).Seller_ID << ',' << Com.at(j).C_Date << ',' << Com.at(j).C_state << endl;
		ofile.close();
		ofstream outfile;
		outfile.open("order.txt", ios::app);
		int m;
		m = Ord.size() + 1;
		int p = m / 100; int q = (m / 10) % 10; m = m % 10;
		ss << p << q << m;
		string str1, str2, str3;
		ss >> str1 >> str2 >> str3;
		ID = "T" + str1 + str2 + str3;
		Order new_order;
		new_order.O_ID = ID; new_order.C_ID = Com.at(i).C_ID; new_order.unitPrice = Com.at(i).C_price;
		new_order.number = num; new_order.O_date = date; new_order.buyerID = someone.ID; new_order.sellerID = Com.at(i).Seller_ID;
		if(new_order.O_ID == "T001")outfile<<"orderID,commodityID,unitPrice,number,date,sellerID,buyerID"<<endl;
		outfile << new_order.O_ID << ',' << new_order.C_ID << ',' << new_order.unitPrice << ',' << new_order.number << ',' << new_order.O_date << ',' << new_order.buyerID << ',' << new_order.sellerID << endl;
		outfile.close();
		Ord.push_back(new_order);
		interpreter.SQL_order_values_insert(new_order);
	}
	cout << "******************************" << endl << endl;
}
void Buyers::Search_Commodity()
{
	cout << "Please input commodity name:"; string name; getline(cin, name);
	SQL interpreter;
	interpreter.SQL_commodity_name_select(name);
	cout << "***********************************************************************" << endl;
	int m = 0; int n = 0;
	vector<Commodity>temp_Com;
	for (int i = 0; i < Com.size(); ++i)
		temp_Com.push_back(Com.at(i));
	for (int i = 0; i < temp_Com.size(); ++i)
	{
		if (temp_Com.at(i).C_name.find(name) != string::npos)temp_Com.at(i).C_number = 25;
		else temp_Com.at(i).C_number = 0;
	}
	for (int i = 0; i < temp_Com.size(); ++i)
	{
		int k = 0; int l = 0;
		for (int j = 0; j < temp_Com.at(i).C_name.size(); ++j)
		{
			while (name[l] == temp_Com.at(i).C_name[j + l] || name[l] + 32 == temp_Com.at(i).C_name[j + l] || name[l] == temp_Com.at(i).C_name[j + l] + 32)
			{
				if (name[l] == temp_Com.at(i).C_name[j + l])
					k += 3;
				if (name[l] + 32 == temp_Com.at(i).C_name[j + l] || name[l] == temp_Com.at(i).C_name[j + l] + 32)
					k += 1;
				++l;
				if (l == name.size() || (l + j) == temp_Com.at(i).C_name.size())break;
			}
			j = j + l;
			l = 0;
		}
		temp_Com.at(i).C_number += k;
	}
	sort(temp_Com.begin(), temp_Com.end(), comp3);
	for (int i = 0; i < Com.size(); ++i)
	{
		if (temp_Com.at(i).C_number > 3 && temp_Com.at(i).C_state =="onSale")
		{
			++m; ++n; if (m == 1)cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
			cout << temp_Com.at(i).C_ID << "           " << temp_Com.at(i).C_name;
			for (int j = 0; j < 20 - temp_Com.at(i).C_name.size(); ++j)cout << " ";
			cout << fixed << setprecision(1) << temp_Com.at(i).C_price;
			stringstream ss; string temp_balance; ss << fixed << setprecision(1) << temp_Com.at(i).C_price; ss >> temp_balance;
			for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
			cout << temp_Com.at(i).C_Date;
			for (int j = 0; j < 15 - Com.at(i).C_Date.size(); ++j)cout << " ";
			cout << temp_Com.at(i).Seller_ID <<endl;
		}
	}
	if (n == 0)cout << "Your commodity hasn't been found. Going to return to main menu." << endl;
	cout << "***********************************************************************" << endl << endl << endl;
};
void Buyers::Check_History_Orders(user& someone)
{
	cout << "************************************************************************************" << endl;
	cout << "OrderID   CommodityID   Unit price   Quantity   Date          SellerID   BuyerID" << endl;
	for (int i = 0; i < Ord.size(); ++i)
	{
		if (Ord.at(i).buyerID == someone.ID)
		{
			cout << Ord.at(i).O_ID << "      " << Ord.at(i).C_ID << "          " << fixed << setprecision(1) << Ord.at(i).unitPrice;
			stringstream ss; string price; ss << fixed << setprecision(1) << Ord.at(i).unitPrice; ss >> price;
			for (int j = 0; j < 13 - price.size(); ++j)cout << " ";
			cout << Ord.at(i).number;
			ss.clear(); string num; ss << Ord.at(i).number; ss >> num;
			for (int j = 0; j < 11 - num.size(); ++j)cout << " ";
			cout << Ord.at(i).O_date;
			for (int j = 0; j < 14 - Ord.at(i).O_date.size(); ++j)cout << " ";
			cout << Ord.at(i).sellerID << "       " << Ord.at(i).buyerID << endl;
		}
	}
	cout << "************************************************************************************" << endl<< endl;
	SQL interpreter;
	interpreter.SQL_order_select();
};
void Buyers::Check_Commodity_Info(user& someone)
{
	cout << "Please input commodity ID:"; string ID; cin >> ID; int i = 1024;
	SQL interpreter;
	interpreter.SQL_commodity_ID_select(ID);
	for (int j = 0; j < Com.size(); ++j)
	{
		if (Com.at(j).C_ID == ID)
		{
			i = j;
			break;
		}
	}
	if (i == 1024)cout << "Wrong ID." << endl;
	else if(Com.at(i).C_state =="onSale" || someone.ID == Com.at(i).Seller_ID)
	{
		cout << "******************************************************" << endl;
		cout << "Commodity ID:" << Com.at(i).C_ID << endl;
		cout << "Commodity name:" << Com.at(i).C_name << endl;
		cout << "Commodity price:" << fixed << setprecision(1) << Com.at(i).C_price << endl;
		cout << "Published Date:" << Com.at(i).C_Date << endl;
		cout << "Commodity description:" << Com.at(i).C_description << endl;
		cout << "Commodity seller:" << Com.at(i).Seller_ID << endl;
		cout << "******************************************************" << endl << endl;
	}
	else if (Com.at(i).C_state == "removed")
	{
		cout << "The commodities have been removed.Please wait until the seller stock the commodities." << endl << endl;
	}
};

void Sellers::Seller_Menu()
{
	cout << "======================================================================================================================" << endl;
	cout << "1.Publish Commodity 2.Check Commodity 3.Modify Commodity Infomation 4.Off Commodity 5.Check Historical Order 6.Exit" << endl;
	cout << "======================================================================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "Please choose your operation:";
};
void Sellers::Publish_Commodity(user& someone)
{
	string name; string c_description; string date; double c_price; int c_num;
	cout << "Please input commodity name:";getline(cin, name);
flag1:cout << "Please input commodity price:";
	cin >> c_price; if (c_price <= 0) { cout << "Your input is not legal."; goto flag1; }
flag2:cout << "Please input commodity quantity:"; 
	(cin >> c_num).get(); if (c_num <= 0) { cout << "Your input is not legal."; goto flag2; }
	cout << "Please input commodity description:"; getline(cin, c_description);
	Commodity new_c;
	time_t t = std::time(0);
	tm* now = std::localtime(&t);
	stringstream ss;
	ss << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
	ss >> date;
	new_c.C_name = name; new_c.C_price = c_price; new_c.C_number = c_num; new_c.C_Date = date; new_c.C_description = c_description;new_c.Seller_ID = someone.ID;
	string ID; int i;
	i = Com.size()+ 1;
	int p = i / 100; int q = (i / 10) % 10; i = i % 10;
	ss << p << q << i;
	string str1, str2, str3;
	ss >> str1 >> str2 >> str3;
	ID = "M" + str1 + str2 + str3;
	new_c.C_ID = ID;
	cout << endl << "Please confirm your commodity information is right!" << endl;
	cout << "******************************************************" << endl;
	cout << "Commodity name:" << name << endl;
	cout << "Commodity price:" << fixed << setprecision(1) << c_price << endl;
	cout << "Commodity quantity:" << c_num << endl;
	cout << "Commodity description:" << c_description << endl;
	cout << "******************************************************" << endl << endl;
	char choice;
	cout << "Do you want to publish commodity?(y/n)"; cin >> choice;
	if (choice == 'y')
	{
		cout << "Successfully!" << endl;
		Com.push_back(new_c);
		ofstream outfile;
		outfile.open("commodity.txt", ios::app);
		if (new_c.C_ID == "M001")outfile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
		outfile << ID << ',' << name << ',' << c_price << ',' << c_num << ',' << c_description << ',' << someone.ID << ',' << date << ',' << "onSale" << endl;
		outfile.close();
		SQL interpreter;
		interpreter.SQL_commodity_values_insert(new_c);
	}
	else cout << "Failed." << endl;
};
void Sellers::Check_Commodity(user& someone)
{
	cout << "Please select your view order(1.date 2.descending 3.ascending):"; int num; cin >> num;
	if (num == 1)
	{
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   State" << endl;
		for (int i = 0; i < Com.size(); ++i)
			if (Com.at(i).Seller_ID ==someone.ID &&Com.at(i).C_state == "onSale")
			{
				cout << Com.at(i).C_ID << "           " << Com.at(i).C_name;
				for (int j = 0; j < 20 - Com.at(i).C_name.size(); ++j)cout << " ";
				cout << fixed << setprecision(1) << Com.at(i).C_price;
				stringstream ss; string temp_balance; ss << fixed << setprecision(1) << Com.at(i).C_price; ss >> temp_balance;
				for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
				cout << Com.at(i).C_Date;
				for (int j = 0; j < 15 - Com.at(i).C_Date.size(); ++j)cout << " ";
				cout << Com.at(i).C_state << endl;
			}
		cout << "***********************************************************************" << endl << endl;
	}
	else if (num == 2)
	{
		vector<Commodity>des_com;
		for (int i = 0; i < Com.size(); ++i)
			des_com.push_back(Com.at(i));
		sort(des_com.begin(), des_com.end(), bomp);
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   State" << endl;
		for (int i = 0; i < Com.size(); ++i)
			if (des_com.at(i).Seller_ID == someone.ID&&des_com.at(i).C_state == "onSale")
			{
				cout << des_com.at(i).C_ID << "           " << des_com.at(i).C_name;
				for (int j = 0; j < 20 - des_com.at(i).C_name.size(); ++j)cout << " ";
				cout << fixed << setprecision(1) << des_com.at(i).C_price;
				stringstream ss; string temp_balance; ss << fixed << setprecision(1) << des_com.at(i).C_price; ss >> temp_balance;
				for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
				cout << des_com.at(i).C_Date;
				for (int j = 0; j < 15 - des_com.at(i).C_Date.size(); ++j)cout << " ";
				cout << des_com.at(i).C_state<< endl;
			}
		cout << "***********************************************************************" << endl << endl;
	}
	else if (num == 3)
	{
		vector<Commodity>asc_com;
		for (int i = 0; i < Com.size(); ++i)
			asc_com.push_back(Com.at(i));
		sort(asc_com.begin(), asc_com.end(), comp);
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   State" << endl;
		for (int i = 0; i < Com.size(); ++i)
			if (asc_com.at(i).Seller_ID == someone.ID&&asc_com.at(i).C_state == "onSale")
			{
				cout << asc_com.at(i).C_ID << "           " << asc_com.at(i).C_name;
				for (int j = 0; j < 20 - asc_com.at(i).C_name.size(); ++j)cout << " ";
				cout << fixed << setprecision(1) << asc_com.at(i).C_price;
				stringstream ss; string temp_balance; ss << fixed << setprecision(1) << asc_com.at(i).C_price; ss >> temp_balance;
				for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
				cout << asc_com.at(i).C_Date;
				for (int j = 0; j < 15 - asc_com.at(i).C_Date.size(); ++j)cout << " ";
				cout << asc_com.at(i).C_state << endl;
			}
		cout << "***********************************************************************" << endl << endl;
	}
	SQL interpreter;
	interpreter.SQL_commodity_select();
};
void Sellers::Modify_Commodity_Info(user& someone)
{
	cout << "Please input commodity ID:"; string ID; cin >> ID;
	int j = 1024; 
	bool state = true;
	for (int i = 0; i < Com.size(); ++i)
	{
		if (ID == Com.at(i).C_ID)
		{
			j = i;
			break;
		}
	}
	if (j == 1024)cout << "Wrong ID" << endl;
	else if (Com.at(j).C_state == "removed")cout << "The commodity has been taken off the shelves." << endl;
	else if (Com.at(j).Seller_ID != someone.ID)cout << "The commodity is not yours. Check whether you enter the wrong ID." << endl;
	else
	{
		string  description;
		double newprice;
		int new_num = Com.at(j).C_number;
		newprice = Com.at(j).C_price;
		description = Com.at(j).C_description;
		cout << "Please choose what you want to modify(1.price 2.description 3.number):"; string choice; (cin >> choice).get();
		if (choice == "1")
		{
			cout << "Please modify commodity price:"; 
			cin >> newprice;	
		}
		else if (choice == "2")
		{
			cout << "Please modify commodity description:"; 
			getline(cin, description);
		}
		else if (choice == "3")
		{
			cout << "Please stock your commodity:";
			cin >> new_num;
		}
		else 
		{
			state = false;
		}
		if (state == true)
		{
			cout << "**************************************************" << endl;
			cout << "Commodity ID:" << Com.at(j).C_ID << endl;
			cout << "Commodity name:" << Com.at(j).C_name << endl;
			cout << "Commodity price:" << fixed << setprecision(1) << newprice << endl;
			cout << "Commodity description" << description << endl;
			cout << "Commodity number:" << new_num << endl;
			cout << "**************************************************" << endl;
			cout << "Confirm?(y/n)"; string choice1; cin >> choice1;
			if (choice1 == "y")
			{
				Com.at(j).C_price = newprice;
				Com.at(j).C_description = description;
				Com.at(j).C_number += new_num;
				cout << "Successful!" << endl;
				ofstream ofile;
				ofile.open("commodity.txt", ios::out);
				ofile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
				for(int i = 0; i < Com.size();++i)
					ofile << Com.at(i).C_ID<< ',' << Com.at(i).C_name << ',' << Com.at(i).C_price << ',' << Com.at(i).C_number << ',' << Com.at(i).C_description << ',' <<Com.at(i).Seller_ID << ',' << Com.at(i).C_Date << ',' << Com.at(i).C_state << endl;
				ofile.close();
				SQL interpreter;
				if (choice == "1")interpreter.SQL_commodity_price_update(Com.at(j));
				if (choice == "2")interpreter.SQL_commodity_description_update(Com.at(j));
			}
			else if (choice1 == "n")cout << "Failed" << endl;
			else state = false;
		}
	}
	if (state == false)cout << "Wrong operation." << endl;
};
void Sellers::Off_Commodity(user& someone)
{
	cout << "Please input commodity ID:"; string ID; cin >> ID;
	int i = 1024;
	for (int j = 0; j < Com.size(); ++j)
	{
		if (ID == Com.at(j).C_ID)
		{
			i = j;
			break;
		}
	}
	if (i == 1024) cout << "Wrong operation." << endl;
	else if (someone.ID != Com.at(i).Seller_ID)cout << "The commodity is not yours. Check whether you enter the wrong ID." << endl;
	else if (Com.at(i).C_state == "removed")cout << "The commodity has been taken off the shelves." << endl;
	else 
	{
		cout << "********************************************************************************" << endl;
		cout << "Commodity ID   Name            Price   On Sale Date   Number   Seller ID  State" << endl;
		cout << Com.at(i).C_ID << "           " << Com.at(i).C_name;
		for (int j = 0; j < 16 - Com.at(i).C_name.size(); ++j)cout << " ";
		cout << fixed << setprecision(1) << Com.at(i).C_price;
		stringstream ss; string temp_balance; ss << fixed << setprecision(1) << Com.at(i).C_price; ss >> temp_balance;
		for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
		cout << Com.at(i).C_Date;
		for (int j = 0; j < 15 - Com.at(i).C_Date.size(); ++j)cout << " ";
		cout << Com.at(i).C_number; ss.clear(); string temp_num; ss << Com.at(i).C_number; ss >> temp_num;
		for (int j = 0; j < 9 - temp_num.size(); ++j)cout << " ";
		cout << Com.at(i).Seller_ID << "       "<<Com.at(i).C_state<<endl;
		cout << "********************************************************************************" << endl << endl;
		cout << "Please choose(y/n):"; string choice; cin >> choice;
		if (choice == "y") 
		{
			cout << "Successful!" << endl<<endl;
			Com.at(i).C_state = "removed";
			SQL interpreter;
			interpreter.SQL_commodity_state_update(Com.at(i));
			ofstream ofile;
			ofile.open("commodity.txt", ios::out);
			ofile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
			for (int i = 0; i < Com.size(); ++i)
				ofile << Com.at(i).C_ID << ',' << Com.at(i).C_name << ',' << Com.at(i).C_price << ',' << Com.at(i).C_number << ',' << Com.at(i).C_description << ',' << Com.at(i).Seller_ID << ',' << Com.at(i).C_Date << ',' << Com.at(i).C_state << endl;
			ofile.close();
		}
		else
			cout << " Failed." << endl;
	}
}
void Sellers::Check_History_Orders(user& someone)
{
	cout << "************************************************************************************" << endl;
	cout << "OrderID   CommodityID   Unit price   Quantity   Date          SellerID   BuyerID" << endl;
	for (int i = 0; i < Ord.size(); ++i)
	{
		if (someone.ID == Ord.at(i).sellerID)
		{
			cout << Ord.at(i).O_ID << "      " << Ord.at(i).C_ID << "          " << fixed << setprecision(1) << Ord.at(i).unitPrice;
			stringstream ss; string price; ss << fixed << setprecision(1) << Ord.at(i).unitPrice; ss >> price;
			for (int j = 0; j < 13 - price.size(); ++j)cout << " ";
			cout << Ord.at(i).number;
			ss.clear(); string num; ss << Ord.at(i).number; ss >> num;
			for (int j = 0; j < 11 - num.size(); ++j)cout << " ";
			cout << Ord.at(i).O_date;
			for (int j = 0; j < 14 - Ord.at(i).O_date.size(); ++j)cout << " ";
			cout << Ord.at(i).sellerID << "       " << Ord.at(i).buyerID << endl;
		}
	}
	cout << "************************************************************************************" << endl<<endl;
	SQL interpreter;
	interpreter.SQL_order_select();
};






