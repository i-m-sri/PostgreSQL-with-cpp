#pragma once
#include<iostream>
#include"Receptionist.h"
#include"Postgresql.h"

class Receptionist_customers
{
private:
	int customers_option,id;
public:
	Receptionist_customers(int);
	void customers_operation(int);
};

