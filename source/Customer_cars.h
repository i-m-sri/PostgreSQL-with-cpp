#pragma once
#include"Search_car.h"
#include"Customer.h"
#include<iostream>
#include"Postgresql.h"

class Customer_cars
{
private:
	int cars_option, id;
public:
	Customer_cars(int);
	void car_operation(int);
};

