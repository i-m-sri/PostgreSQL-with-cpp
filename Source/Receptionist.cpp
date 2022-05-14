#include"Receptioist.h"
#include"Search_and_manage_customers.h"
#include"Opening_page.h"
#include"Search_and_manage_cars.h"
#include"My_Account.h"

Receptionist::Receptionist(int n)
{
	flag = n;
	if (receptionist_entry_check(flag))
	{
		std::cout << " RECEPTIONIST\n ------------\n";
		std::cout << " 1.Search and Manage Customers\n 2.Search and Manage Cars\n 3.My Account\n 4.Go Back\n\n";
		std::cout << " Select your option : ";
		std::cin >> receptionist_option;
		std::cout << "_______________________________________________________________________________________\n\n";
		receptionist_home_page();
	}
	else {
		int option;
		setcolor(0x0c);
		std::cout << " OPPS your password is wrong...!!!\n\n";
		setcolor(0x07);
		std::cout << " 1.Do you want to Retry password? (or)\n 2.Go Back\n\n";
		std::cout << " Selection your option : ";
		std::cin >> option;
		std::cout << "_______________________________________________________________________________________\n\n";
		if (option == 1) { Receptionist r(1); }
		else { Open_app app; }
	}
}

void Receptionist::receptionist_home_page()
{
	switch (get_receptionist_option())
	{
	case 1:
	{
		Search_and_manage_customers obj;
		break;
	}
	case 2:
	{
		Search_and_manage_cars obj;
		break;
	}
	case 3:
	{
		My_Account obj;
		break;
	}
	case 4:
	{
		Open_app app;
		break;
	}
	default:
		break;
	}
}

int Receptionist::get_receptionist_option()
{
	return receptionist_option;
}

int Receptionist::receptionist_entry_check(int flag) 
{
	if (flag)
	{
		std::string password;
		std::cout << " Enter the password : ";
		std::cin >> password;
		std::cout << "_______________________________________________________________________________________\n\n";
		if (password == execute_with_return("select password from receptionist;")) 
		{ 
			setcolor(0x0a);
			std::cout << " Logged In successfully...!!!";
			setcolor(0x07);
			std::cout << "\n_______________________________________________________________________________________\n\n";
			return 1; 
		}
		else { return 0; }
	}
	else {
		return 1;
	}
}

