#pragma once
#include<iostream>
#include"Receptionist.h"
#include"Postgresql.h"

class Receptionist_cars
{
private:
	int cars_option,id;
public:
	Receptionist_cars(int);
	void car_operation(int);
};

