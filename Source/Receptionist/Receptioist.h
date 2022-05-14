#pragma once
#include"Opening_page.h"
#include"textcolor.h"

class Receptionist
{
private:
	int receptionist_option;
public:
	int flag;
	Receptionist(int);
	void receptionist_home_page();
	int get_receptionist_option();
	int receptionist_entry_check(int);
};