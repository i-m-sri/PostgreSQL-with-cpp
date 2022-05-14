#pragma once
#include"Postgresql.h"
#include<iostream>
#include"Search_or_reserve_car.h"
#include"My_profile.h"
#include"Customer.h"

class Customer_page2
{
private:
	int customer_choice;
public:
	std::string user;
	Customer_page2(std::string);
	void customer_page2();
	int get_customer_choice();
};

