#include"Opening_page.h"
#include"Receptioist.h"
#include"Customer.h"

Open_app::Open_app()
{
	std::cout << " ROLES\n -----\n";
	std::cout << " 1.Receptionist\n 2.Customer\n 3.Exit\n\n";
	std::cout << " Select your role : ";
	std::cin >> option;
	std::cout << "_______________________________________________________________________________________\n\n";
	Role();
}

void Open_app::Role()
{
	switch (get_role_option())
	{
	case 1:
	{
		Receptionist obj(1);
		break;
	}
	case 2:
	{
		Customer obj;
		break;
	}
	default:
		break;
	}
}

int Open_app::get_role_option()
{
	return option;
}