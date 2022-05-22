#pragma once
#include<iostream>
#include"Open_app.h"
#include"My_profile.h"
#include"Customer_cars.h"

class Customer
{
private:
	int menu_option, user;
public:
	Customer(int);
	void menu(int);
};

