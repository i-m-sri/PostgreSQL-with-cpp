#pragma once
#include<iostream>
#include"Postgresql.h"
#include"Customer_page2.h"

class My_profile
{
private:
	int profile_management_option;
public:
	std::string profile_name;
	My_profile(std::string);
	void profile_management();
	int get_profile_management_option();
};

