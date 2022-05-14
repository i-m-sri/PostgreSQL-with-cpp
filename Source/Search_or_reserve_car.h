#pragma once
#include"Postgresql.h"
#include<iostream>
#include"Customer_page2.h"
#include"textcolor.h"

class Search_or_reserve_car
{
private:
	int customer_operation;
public:
	std::string user;
	Search_or_reserve_car(std::string);
	void customer_car_operation(int);
	int get_customer_operation();
};

