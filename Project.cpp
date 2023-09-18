#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"User.h"
#include"Admin.h"
#include"Data.h"
using namespace std;
extern vector<user>people;
extern vector<Commodity>Com;
extern vector<Order>Ord;
extern vector<recharge>rechar;
void Main_Menu()
{
	cout << "==============================================================" << endl;
	cout << "1.Administrator Mode" << " " << "2.User Mode" << " " << "3.User Registration" << " " << "4.Exit" << endl;
	cout << "==============================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "Please choose your operation:";
}

void Get_User()
{
	ifstream ifile;
	ifile.open("user.txt", ios::in);
	string help;
	getline(ifile, help);
	if (ifile.is_open())
	{
		while (!ifile.eof())
		{
			user person;
			string temp_balance;
			getline(ifile, person.ID, ',');
			if (ifile.eof())break;
			getline(ifile, person.U_name, ',');
			getline(ifile, person.U_password, ',');
			getline(ifile, person.U_phonenumber, ',');
			getline(ifile, person.U_address, ',');
			getline(ifile, temp_balance, ',');
			getline(ifile, person.U_state);
			stringstream ss; ss << temp_balance; ss >> person.balance; ss.clear();
			people.push_back(person);
		}
	}
	ifile.close();
}

void Get_Order()
{
	ifstream ordfile;
	ordfile.open("order.txt", ios::in);
	string help;
	getline(ordfile, help);
	if (ordfile.is_open())
	{
		while (!ordfile.eof())
		{
			Order new_order;
			string temp_price, temp_number;
			getline(ordfile, new_order.O_ID, ',');
			if (ordfile.eof())break;
			getline(ordfile, new_order.C_ID, ',');
			getline(ordfile, temp_price, ',');
			getline(ordfile, temp_number, ',');
			getline(ordfile, new_order.O_date, ',');
			getline(ordfile, new_order.buyerID, ',');
			getline(ordfile, new_order.sellerID);
			stringstream ss; ss << temp_price; ss >> new_order.unitPrice; ss.clear();
			ss << temp_number; ss >> new_order.number;
			Ord.push_back(new_order);
		}
	}
	ordfile.close();
}

void Get_Commodity()
{
	ifstream comfile;
	comfile.open("commodity.txt", ios::in);
	string help;
	getline(comfile, help);
	if (comfile.is_open())
	{
		while (!comfile.eof())
		{
			Commodity new_commodity;
			string temp_price,number;
			getline(comfile, new_commodity.C_ID, ',');
			if (comfile.eof())break;
			getline(comfile, new_commodity.C_name, ',');
			getline(comfile, temp_price, ',');
			getline(comfile, number, ',');
			getline(comfile, new_commodity.C_description, ',');
			getline(comfile, new_commodity.Seller_ID, ',');
			getline(comfile, new_commodity.C_Date, ',');
			getline(comfile, new_commodity.C_state);
			stringstream ss; ss << temp_price; ss >> new_commodity.C_price; ss.clear();
			ss << number; ss >> new_commodity.C_number;
			Com.push_back(new_commodity);
		}
	}
	comfile.close();
}

void Buyer_Mode(user& someone)
{
	Buyers buyer;
	string option;
	while (true)
	{
		buyer.Buyer_Menu();
	flag:(std::cin>>option).get();
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
			case'1':buyer.Check_Commodity_List(); break;
			case'2':buyer.Buy_Commodity(someone); break;
			case'3':buyer.Search_Commodity(); break;
			case'4':buyer.Check_History_Orders(someone); break;
			case'5':buyer.Check_Commodity_Info(someone); break;
			case'6':cout << endl << endl; return;
			default:cout << "Not a valid request!" << endl; break;
			}
		}
	}
}

void Seller_Mode(user& someone)
{
	Sellers seller;
	string option;
	while (true)
	{
		seller.Seller_Menu();
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
			case'1':seller.Publish_Commodity(someone); break;
			case'2':seller.Check_Commodity(someone); break;
			case'3':seller.Modify_Commodity_Info(someone); break;
			case'4':seller.Off_Commodity(someone); break;
			case'5':seller.Check_History_Orders(someone); break;
			case'6':cout << endl << endl; return;
			default:cout << "Not a valid request!" << endl; break;
			}
		}
	}
}

void User_Registration()
{
	if (people.empty())Get_User();
	Users someone;
	someone.U_Register();
};

void User_Mode()
{
	Users U;
	string name, code;
	if (people.empty())Get_User();
	if (Com.empty())Get_Commodity();
	if (Ord.empty())Get_Order();
	
flag1:
	cout << "Please enter the user's name:";
	std::cin >> name;
	cout << "Please enter the user's code:";
	std::cin >> code;
	if (U.U_Login(name, code) == 1)
		cout << endl << "-----Successful Login-----" << endl << endl << endl;
	else if (U.U_Login(name, code) == 2)
	{
		cout <<"-----Your account has been banned. Now returning to the main menu----" << endl << endl << endl;
		return;
	}
	else if (U.U_Login(name, code) == 0)
	{
		cout << endl << "-----Wrong Login! Please input your name and code again.----" << endl << endl << endl;
		goto flag1;
	}
	int i = 0;
	for (; i < people.size(); ++i)
		if (name == people.at(i).U_name)break;
	user& someone = people.at(i);
	while (true)
	{
		U.U_Menu();
		string option;
	flag2:(std::cin >> option).get();
		if (option.size() != 1)
		{
			cout << "Your input is not legal. Please choose your option again:";
			goto flag2;
		}
		else 
		{	
			char opt = option[0];
			switch (opt)
			{
			case'1':Buyer_Mode(someone); break;
			case'2':Seller_Mode(someone); break;
			case'3':U.Self_Info_Mag(someone); break;
			case'4':cout << endl << endl; return; break;
			default:cout << "Not a valid request!" << endl; break;
			}
		}
	}
}

void Administrator_Mode()
{
	if (people.empty())Get_User();
	if (Com.empty())Get_Commodity();
	if (Ord.empty())Get_Order();
	Administrator admin;
	string name, code;
	cout << "Please enter the administrator's name:";
	getline(std::cin,name);
	cout << "Please enter the administrator's code:";
	std::cin >> code;
	if (admin.Admin_Login(name, code) == true)
		cout << endl << "-----Successful Login-----" << endl << endl << endl;
	else
	{
		cout << endl << "-----Wrong Login! Returning to the main menu.----" << endl << endl << endl;
		return;
	}
	while (true)
	{
		admin.Admin_Menu();
		cout << "Please choose your operation:";
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
			case'1':admin.All_Commodity(); break;
			case'2':admin.Search_Commodity(); break;
			case'3':admin.Delete_Commodity(); break;
			case'4':admin.All_Orders(); break;
			case'5':admin.All_Users(); break;
			case'6':admin.Ban_Users(); break;
			case'7':cout << endl << endl; return; break;
			default:cout << "Not a valid request!" << endl; break;
			}
		}
	}
};

int main()
{
	while (true)
	{
		Main_Menu();
		cout << "Please choose your operation:";
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
			case '1':Administrator_Mode(); break;
			case '2':User_Mode(); break;
			case '3':User_Registration(); break;
			case '4':exit(-1); break;
			default:cout << "Not a valid request!" << endl; break;
			}
		}
	}
	return 0;
}

