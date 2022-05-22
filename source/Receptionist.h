#pragma once
#include<iostream>
#include"Open_app.h"

class Receptionist
{
private:
	int menu_option,user;
public:
	Receptionist(int);
	void menu(int);
};

