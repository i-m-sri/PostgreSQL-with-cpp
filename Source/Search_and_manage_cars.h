#pragma once
#include<iostream>
#include"Receptioist.h"
#include"Search_car.h"

using namespace std;

class Search_and_manage_cars
{
private:
	int receptionist_operation;
public:
	Search_and_manage_cars();
	void receptionist_page2();
	int get_receptionist_operation();
};

