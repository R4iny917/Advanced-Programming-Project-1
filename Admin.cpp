#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include"Admin.h"
#include"Data.h"
#include"User.h"
#include<algorithm>

using namespace std;

extern vector<Commodity>Com;
extern vector<Order>Ord;
extern vector<user>people;
extern vector<recharge>rechar;
bool comp4(const Commodity& a, const Commodity& b)
{
	return a.C_number > b.C_number;
}
bool comp1(const Commodity& a, const Commodity& b)
{
	return a.C_price < b.C_price;
}
bool comp2(const Commodity& a, const Commodity& b)
{
	return a.C_price > b.C_price;
}
bool Administrator::Admin_Login(string name, string code)
{
	if (name == admin_name && code == admin_code)return true;
	else return false;
}
void Administrator::Admin_Menu()
{
	cout << "============================================================================================================" << endl;
	cout << "1.Check all commodity 2.Search commodity 3.Offsale 4.Check all orders 5.Check all users 6.Ban user 7.Exit" << endl;
	cout << "============================================================================================================" << endl;
};
void Administrator::All_Commodity()
{
	cout << "Please select your view order(1.date 2.descending 3.ascending):"; int num; cin >> num;
	if (num == 1)
	{
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		for (int i = 0; i < Com.size(); ++i)
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
		sort(des_com.begin(), des_com.end(), comp2);
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		for (int i = 0; i < Com.size(); ++i)
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
		sort(asc_com.begin(), asc_com.end(), comp1);
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		for (int i = 0; i < Com.size(); ++i)
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
};
void Administrator::Search_Commodity()
{
	cout << "Please input commodity name:"; string name; flag:getline(cin, name);
	SQL interpreter;
	interpreter.SQL_commodity_name_select(name);
	if (name.size() < 2)
	{
		cout << "The keyword is too short. Please enter again:";
		goto flag;
	}
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
	sort(temp_Com.begin(), temp_Com.end(), comp4);
	for (int i = 0; i < Com.size(); ++i)
	{
		if (temp_Com.at(i).C_number > 3)
		{
			++m; ++n; if (m == 1)cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
			cout << temp_Com.at(i).C_ID << "           " << temp_Com.at(i).C_name;
			for (int j = 0; j < 20 - temp_Com.at(i).C_name.size(); ++j)cout << " ";
			cout << fixed << setprecision(1) << temp_Com.at(i).C_price;
			stringstream ss; string temp_balance; ss << fixed << setprecision(1) << temp_Com.at(i).C_price; ss >> temp_balance;
			for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
			cout << temp_Com.at(i).C_Date;
			for (int j = 0; j < 15 - Com.at(i).C_Date.size(); ++j)cout << " ";
			cout << temp_Com.at(i).Seller_ID << endl;
		}
	}
	if (n == 0)cout << "Your commodity hasn't been found. Going to return to main menu." << endl;
	cout << "***********************************************************************" << endl << endl << endl;
};
void Administrator::Delete_Commodity()
{
	cout << "Please input commodity ID:"; string ID; cin >> ID; int i = 1024;
	for (int j = 0; j < Com.size(); ++j)
	{
		if (Com.at(j).C_ID == ID)
		{
			i = j;
			break;
		}
	}
	if (i == 1024)cout << "The ID doesn't exist." << endl;
	else 
	{
		cout << "***********************************************************************" << endl;
		cout << "Commodity ID   Name                Price   On Sale Date   Seller ID" << endl;
		cout << Com.at(i).C_ID << "           " << Com.at(i).C_name;
		for (int j = 0; j < 20 - Com.at(i).C_name.size(); ++j)cout << " ";
		cout << fixed << setprecision(1) << Com.at(i).C_price;
		stringstream ss; string temp_balance; ss << fixed << setprecision(1) << Com.at(i).C_price; ss >> temp_balance;
		for (int j = 0; j < 8 - temp_balance.size(); ++j)cout << " ";
		cout << Com.at(i).C_Date;
		for (int j = 0; j < 15 - Com.at(i).C_Date.size(); ++j)cout << " ";
		cout << Com.at(i).Seller_ID << endl;
		cout << "***********************************************************************" << endl;
		cout << "Please choose(y/n):"; string choice; cin >> choice;
		if (choice == "y")
		{
			cout << "Successful!"<<endl;
			Com.at(i).C_state = "removed";
			SQL interperter;
			interperter.SQL_commodity_state_update(Com.at(i));
			ofstream ofile;
			ofile.open("commodity.txt", ios::out);
			ofile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
			for (int i = 0; i < Com.size(); ++i)
				ofile << Com.at(i).C_ID << ',' << Com.at(i).C_name << ',' << Com.at(i).C_price << ',' << Com.at(i).C_number << ',' << Com.at(i).C_description << ',' << Com.at(i).Seller_ID << ',' << Com.at(i).C_Date << ',' << Com.at(i).C_state << endl;
			ofile.close();
		}
		else if (choice == "n") cout << "Cancelled."<<endl;
		else cout << "Wrong opertion." << endl;
	}
};
void Administrator::All_Orders()
{
	cout << "************************************************************************************" << endl;
	cout << "OrderID   CommodityID   Unit price   Quantity   Date          SellerID   BuyerID" << endl;
	for (int i = 0; i < Ord.size(); ++i)
	{
		cout << Ord.at(i).O_ID << "      " << Ord.at(i).C_ID << "          " << fixed << setprecision(1) << Ord.at(i).unitPrice;
		stringstream ss; string price; ss << fixed << setprecision(1) << Ord.at(i).unitPrice; ss >> price;
		for (int j = 0; j < 13 - price.size(); ++j)cout << " ";
		cout << Ord.at(i).number;
		ss.clear(); string num; ss << Ord.at(i).number; ss >> num;
		for (int j = 0; j < 11-num.size(); ++j)cout << " ";
		cout << Ord.at(i).O_date;
		for (int j = 0; j < 14 - Ord.at(i).O_date.size(); ++j)cout << " ";
		cout<< Ord.at(i).sellerID << "       " << Ord.at(i).buyerID << endl;
	}
	cout << "************************************************************************************" << endl;
	SQL interpreter;
	interpreter.SQL_order_select();
};
void Administrator::All_Users()
{
	cout << "*******************************************************************" << endl;
	cout << "User ID   User name   Phone number   Address   Balance   State"<<endl;
	for (int i = 0; i < people.size(); ++i)
	{
		cout << people.at(i).ID << "      " << people.at(i).U_name;
		for (int j = 0; j < 12 - people.at(i).U_name.size(); ++j)cout <<" ";
		cout << people.at(i).U_phonenumber;
		for (int j = 0; j < 15 - people.at(i).U_phonenumber.size(); ++j)cout <<" ";
		cout << people.at(i).U_address;
		for (int j = 0; j < 10 - people.at(i).U_address.size(); ++j)cout <<" ";
		cout << fixed << setprecision(1) << people.at(i).balance;
		stringstream ss; string temp_balance; ss << fixed << setprecision(1) << people.at(i).balance; ss >> temp_balance;
		for (int j = 0; j < 10 - temp_balance.size(); ++j)cout <<" ";
		cout<< people.at(i).U_state << endl;
	}
	cout << "*******************************************************************" << endl;
	SQL interpreter;
	interpreter.SQL_user_select();
};
void Administrator::Ban_Users()
{
	cout << "Please input User ID:"; string ID; cin >> ID;
	int i = 1024;
	for (int j = 0; j < people.size(); ++j)
	{
		if (people.at(j).ID== ID)
		{
			i = j;
			break;
		}
	}
	if (i == 1024)cout << "The ID dosen't exist." << endl;
	else 
	{
		cout << "Are you sure to ban the user?" << endl;
		cout << "****************************************************************" << endl;
		cout << "User ID   User name   Phone number   Address   Balance   State" << endl;
		cout << people.at(i).ID << "      " << people.at(i).U_name;
		for (int j = 0; j < 12 - people.at(i).U_name.size(); ++j)cout << " ";
		cout << people.at(i).U_phonenumber;
		for (int j = 0; j < 15 - people.at(i).U_phonenumber.size(); ++j)cout << " ";
		cout << people.at(i).U_address;
		for (int j = 0; j < 10 - people.at(i).U_address.size(); ++j)cout << " ";
		cout << fixed << setprecision(1) << people.at(i).balance;
		stringstream ss; string temp_balance; ss << fixed << setprecision(1) << people.at(i).balance; ss >> temp_balance;
		for (int j = 0; j < 10 - temp_balance.size(); ++j)cout << " ";
		cout << people.at(i).U_state << endl;
		cout << "****************************************************************" << endl;
		cout << "Please choose(y/n):"; string choice; cin >> choice;
		if (choice == "y")
		{
			people.at(i).U_state = "inactive";
			cout << "Successful." << endl;
			for (int j = 0; j < Com.size(); ++j)
				if (people.at(i).ID == Com.at(j).Seller_ID)Com.at(j).C_state = "removed";
			SQL interpreter;
			interpreter.SQL_user_state_update(people.at(i).ID);
			ofstream ofile;
			ofile.open("user.txt", ios::out);
			ofile << "userID,username,password,phoneNumber,address,balance,userState" << endl;
			for (int i = 0; i < people.size(); ++i)
				ofile << people.at(i).ID << "," << people.at(i).U_name << "," << people.at(i).U_password << "," << people.at(i).U_phonenumber << "," << people.at(i).U_address << "," << people.at(i).balance << "," << people.at(i).U_state << endl;
			ofile.close();
			ofile.open("commodity.txt", ios::out);
			ofile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
			for(int i = 0; i < Com.size();++i)
				ofile << Com.at(i).C_ID << ',' << Com.at(i).C_name << ',' << Com.at(i).C_price << ',' << Com.at(i).C_number << ',' << Com.at(i).C_description << ',' << Com.at(i).Seller_ID << ',' << Com.at(i).C_Date << ',' << Com.at(i).C_state << endl;
			ofile.close();
		}
		else cout << "Failed." << endl;
	}
};

