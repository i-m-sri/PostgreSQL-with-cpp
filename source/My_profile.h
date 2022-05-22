#pragma once
#include<iostream>
#include"Postgresql.h"
#include"Customer.h"

class My_profile
{
private:
	int profile_management_option, userid;
public:
	My_profile(int);
	void profile_management();
	int get_profile_management_option();
};

