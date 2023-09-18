#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Data.h"
#include"User.h"
#include<vector>
class SQL
{
public:
	void SQL_commodity_select();
	void SQL_commodity_name_select(string name);
	void SQL_order_select();
	void SQL_user_select();
	void SQL_commodity_ID_select(string ID);
	void SQL_commodity_state_update(Commodity& com);
	void SQL_user_state_update(string ID);
	void SQL_commodity_price_update(Commodity& com);
	void SQL_commodity_description_update(Commodity& com);
	void SQL_commodity_num_update(Commodity& com);
	void SQL_commodity_values_insert(Commodity& com);
	void SQL_order_values_insert(Order& ord);
};
