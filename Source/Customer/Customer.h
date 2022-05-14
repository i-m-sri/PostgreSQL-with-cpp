#pragma once
#include<iostream>
#include"Postgresql.h"
#include"textcolor.h"
//#include"Opening_page.h"
//#include"VariadicTable.h"

class Customer
{
private:
	int customer_option;
public:
	Customer();
	void customer_page();
	int get_customer_option();
};

