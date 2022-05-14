#include "Customer_page2.h"

Customer_page2::Customer_page2(std::string username)
{
	user = username;
	std::cout << " MENU\n ----\n";
	std::cout << " 1.Search or Book a Car\n 2.My_Profile\n 3.Go Back\n\n";
	std::cout << " Choose your option : ";
	std::cin >> customer_choice;
	std::cout << "_______________________________________________________________________________________\n\n";
	Customer_page2::customer_page2();
}

void Customer_page2::customer_page2() 
{
	switch (get_customer_choice())
	{
	case 1:
	{
		Search_or_reserve_car car(user);
		break;
	}
	case 2:
	{
		My_profile p(user);
		break;
	}
	case 3:
	{
		Customer c;
		break;
	}
	default:
		break;
	}
}

int Customer_page2::get_customer_choice() 
{
	return customer_choice;
}