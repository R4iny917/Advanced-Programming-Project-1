#pragma once
#include<iostream>
#include<string>
using namespace std;

struct Commodity
{
	string C_ID ;
	string C_name;
	double C_price = 0.0;
	string C_description;
	int C_number = 0;
	string Seller_ID;
	string C_Date;
	string C_state = "onSale";
};

struct Order
{
	string O_ID ;
	string C_ID;
	double unitPrice = 0.0;
	int number = 0;
	string O_date;
	string sellerID;
	string buyerID;
};

