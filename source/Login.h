#pragma once
#include<iostream>
#include"Receptionist.h"
#include"Customer.h"

class Login
{
private :
	std::string username, password;
public:
	Login();
	void username_check(std::string);
	void role_selection();
};

