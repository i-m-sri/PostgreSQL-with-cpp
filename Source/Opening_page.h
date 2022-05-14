#pragma once
#include<iostream>
#include"Postgresql.h"
#include"VariadicTable.h"

class Open_app
{
private:
	int option;
public:
	Open_app();
	void Role();
	int get_role_option();
};