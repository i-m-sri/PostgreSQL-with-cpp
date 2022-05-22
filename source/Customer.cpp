#include "Customer.h"

Customer::Customer(int s)
{
	this->user = s;
	std::cout << " MENU\n ----\n";
	std::cout << " 1.Search and Reserve car\n 2.My Profile\n 3.Go Back\n\n";
	std::cout << " Enter your option : ";
	std::cin >> menu_option;
	std::cout << " ________________________________________________________________________________________________________\n\n";
	menu(menu_option);
}

void Customer::menu(int menu_option)
{
	switch (menu_option)
	{
	case 1:
	{
		Customer_cars car(this->user);
		break;
	}
	case 2:
	{
		My_profile customer(this->user);
		break;
	}
	case 3:
	{
		Open_app a;
		break;
	}
	default:
		break;
	}
}