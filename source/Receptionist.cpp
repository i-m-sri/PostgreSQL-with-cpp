#include"Receptionist.h"
#include"Receptionist_cars.h"
#include"Receptionist_customers.h"
#include"My_Account.h"

Receptionist::Receptionist(int s)
{
	this->user = s;
	std::cout << " MENU\n ----\n";
	std::cout << " 1.Search,Reserve and Manage car\n 2.Search and Manage customer\n 3.My Account\n 4.Go Back\n\n";
	std::cout << " Enter your option : ";
	std::cin >> menu_option;
	std::cout << " ________________________________________________________________________________________________________\n\n";
	menu(menu_option);
}

void Receptionist::menu(int menu_option)
{
	switch (menu_option)
	{
	case 1:
	{
		Receptionist_cars car(this->user);
		break;
	}
	case 2:
	{
		Receptionist_customers customer(this->user);
		break;
	}
	case 3:
	{
		My_Account a(this->user);
		break;
	}
	case 4:
	{
		Open_app a;
		break;
	}
	default:
		break;
	}
}