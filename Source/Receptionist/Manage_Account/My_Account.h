#pragma once
#include<iostream>
#include"Postgresql.h"
#include"Receptioist.h"

class My_Account
{
private:
	int account_management_option;
public:
	My_Account();
	void account_management();
	int get_account_management_option();
};

