#include "Customer.h"
#include"Customer_page2.h"

Customer::Customer()
{
	std::cout << " CUSTOMER\n --------\n";
	std::cout << " 1.Sign In\n 2.Sign Up \n 3.Go Back\n\n";
	std::cout << " Select your choice : ";
	std::cin >> customer_option;
	std::cout << "_______________________________________________________________________________________\n\n";
	Customer::customer_page();

}

void Customer::customer_page()
{
	switch (get_customer_option())
	{
	case 1:
	{
		std::string username, password;
		std::cout << " SIGN IN\n -------\n";
		std::cout << " Enter the username : ";
		std::cin.ignore();
		getline(std::cin, username);
		if (username == execute_with_return("select * from customers where name='" + username + "';"))
		{
		password:
			{
				std::cout << "\n Enter the password : ";
				std::cin>> password;
				std::cout << "\n_______________________________________________________________________________________\n\n";
				if (password == execute_with_return("select password from customers where name='" + username + "';"))
				{
					setcolor(0x0a);
					std::cout << " Logged in successfully...!!!\n";
					setcolor(0x07);
					std::cout << "_______________________________________________________________________________________\n\n";
					Customer_page2 page(username);
				}
				else {
					int option;
					setcolor(0x0c);
					std::cout << " OPPS sorry your password is incorrect...!!!\n\n";
					setcolor(0x07);
					std::cout << " 1.Do you want to Retry password? (or)\n 2.Go Back\n\n";
					std::cout << " Select your option : ";
					std::cin >> option;
					std::cout << "_______________________________________________________________________________________\n\n";
					if (option == 1) { goto password; }
					else { Customer obj; }
				}
			}
		}
		else {
			char choice;
			setcolor(0x0c);
			std::cout << "\n User "+username+" does not exit...!!!\n\n";
			setcolor(0x07);
			std::cout<<" 1.Do you want to Retry?(y/n) : ";
			std::cin >> choice;
			std::cout << "_______________________________________________________________________________________\n\n";
			if (choice == 'y') { Customer::customer_page(); }
			else { Customer obj; }
		}
		break;
	}
	case 2:
	{
		std::string name, password, mail, address;
		std::cout << " CREATE ACCOUNT\n --------------\n";
		std::cout << "\n Enter the Name : ";
		std::cin.ignore();
		getline(std::cin, name);
		std::cout << " Enter the password : ";
		std::cin >> password;
		std::cout << " Enter the Mail ID : ";
		std::cin >> mail;
		std::cout << " Enter the Address : ";
		std::cin.ignore();
		getline(std::cin,address);
		execute("insert into customers(name,password,mail,address) values('" + name + "','" + password + "','" + mail + "','" + address + "');", 1);
		setcolor(0x0e);
		std::cout << " Account created successfully\n";
		setcolor(0x07);
		std::cout << "_______________________________________________________________________________________\n\n";
		Customer_page2 obj(name);
		break;
	}
	default:
		break;
	}
}

int Customer::get_customer_option()
{
	return customer_option;
}