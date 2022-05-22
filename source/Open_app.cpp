#include "Open_app.h"

Open_app::Open_app()
{
	std::cout << " 1.Login\n 2.Sign Up\n 3.Exit\n\n";
	std::cout << " Select your option : ";
	std::cin >> option;
	std::cout << " ________________________________________________________________________________________________________\n\n";
	app_option();
}

void Open_app::app_option()
{
	switch (option)
	{
	case 1:
	{
		Login user;
		break;
	}
	case 2:
	{
		int role;
		std::cout << " ROLES\n -----\n";
		std::cout << " 1.Receptionist\n 2.Customer\n\n";
		std::cout << " Enter your role : ";
		std::cin >> role;
		std::cout << " ________________________________________________________________________________________________________\n\n";
		if (role == 1)
		{
		create_receptionist:
			{
				int code;
				std::cout << " Enter the company code : ";
				std::cin >> code;
				std::cout << " ________________________________________________________________________________________________________\n\n";
				if (code == stoi(get_value("select code from code;")))
				{
					std::string name, number, mail, address, password;
					std::cout << " Enter the name : ";
					std::cin.ignore();
					getline(std::cin, name);
					std::cout << " Enter the mobile number : ";
					std::cin >> number;
					std::cout << " Enter the mail : ";
					std::cin >> mail;
					std::cout << " Enter the address : ";
					std::cin.ignore();
					getline(std::cin, address);
					std::cout << " Enter the password : ";
					std::cin >> password;
					std::cout << " ________________________________________________________________________________________________________\n\n";
					execute("insert into users(name,mobile_number,mail,address,password,type) values('" + name + "'," + number + ",'" + mail + "','" + address + "','" + password + "','receptionist');", 1);
					setcolor(0x0a);
					std::cout << " Account created successfully...!!!\n";
					setcolor(0x07);
					std::cout << " ________________________________________________________________________________________________________\n\n";
					Open_app l;
				}
				else {
					char ch;
					setcolor(0x0c);
					std::cout << " Code you entered is incorrect\n\n";
					setcolor(0x07);
					std::cout << " Do you want to Retry code(y/n) : ";
					std::cin >> ch;
					std::cout << " ________________________________________________________________________________________________________\n\n";
					if (ch == 'y') { goto create_receptionist; }
					else { this->option = 2; app_option(); }
				}
			}
		}
		else
		{
			std::string name, number, mail, address, password;
			std::cout << " Enter the name : ";
			std::cin.ignore();
			getline(std::cin, name);
			std::cout << " Enter the mobile number : ";
			std::cin >> number;
			std::cout << " Enter the mail : ";
			std::cin >> mail;
			std::cout << " Enter the address : ";
			std::cin.ignore();
			getline(std::cin, address);
			std::cout << " Enter the password : ";
			std::cin >> password;
			std::cout << " ________________________________________________________________________________________________________\n\n";
			execute("insert into users(name,mobile_number,mail,address,password) values('" + name + "'," + number + ",'" + mail + "','" + address + "','" + password + "');", 1);
			setcolor(0x0a);
			std::cout << " Account created successfully...!!!\n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
			Open_app l;
		}
		break;
	}
	case 3:
		return;
	default:
		break;
	}
}