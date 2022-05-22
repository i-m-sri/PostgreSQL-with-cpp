#pragma once
#include<iostream>
#include"Postgresql.h"
#include"Receptionist.h"

class My_Account
{
private:
	int account_management_option, userid;
public:
	My_Account(int);
	void account_management();
	int get_account_management_option();
};

