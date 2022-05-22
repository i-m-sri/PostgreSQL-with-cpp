#include "Receptionist_customers.h"

Receptionist_customers::Receptionist_customers(int j)
{
	this->id = j;
	std::cout << " CARS MENU\n ---------\n";
	std::cout << " 1.Search a customer\n 2.Add a customer account\n 3.Edit a customer account\n 4.Delete a customer account\n 5.Go Back\n\n";
	std::cout << " Enter the option : ";
	std::cin >> customers_option;
	std::cout << " ________________________________________________________________________________________________________\n\n";
	customers_operation(customers_option);
}

void Receptionist_customers::customers_operation(int option)
{
	switch (option)
	{
	case 1:
	{
		std::string details;
		std::cout << " SEARCH CUSTOMER\n ---------------\n\n";
		execute("select * from users where type='customer';", 4);
		std::cout << " Enter the details of the customer you want to search\n";
		std::cout << " (For example: name='customer name' or id=customerid)\n\n";
		std::cout << " Enter the details : ";
		std::cin.ignore();
		getline(std::cin, details);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		execute("select * from users where " + details + ";", 4);
		Receptionist_customers c1(this->id);
		break;
	}
	case 2:
	{
		std::cout << " ADD CUSTOMER\n ------------\n\n";
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
		execute("select * from users where type='customer';", 4);
		Receptionist_customers c2(this->id);
		break;
	}
	case 3:
	{
		std::string details,new_details;
		std::cout << " EDIT CUSTOMER\n -------------\n\n";
		execute("select * from users where type='customer';", 4);
		std::cout << " Enter the details of the customer you want to edit\n";
		std::cout << " (For example: name='customer name' or id=customerid)\n\n";
		std::cout << " Enter the details : ";
		std::cin.ignore();
		getline(std::cin, details);
		std::cout << "\n Enter the new details of the customer you want to edit\n";
		std::cout << " (For example: name='customer name' or id=customerid)\n\n";
		std::cout << " Enter the new details : ";
		getline(std::cin,new_details);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		execute("update users set "+new_details+" where "+details+";", 1);
		setcolor(0x0a);
		std::cout << " Account edited successfully...!!!\n";
		setcolor(0x07);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		execute("select * from users where type='customer';", 4);
		Receptionist_customers c3(this->id);
		break;
	}
	case 4:
	{
		std::string details;
		std::cout << " DELETE CUSTOMER\n ---------------\n\n";
		execute("select * from users where type='customer';", 4);
		std::cout << " Enter the details of the customer you want to delete\n";
		std::cout << " (For example: name='customer name' or id=customerid)\n\n";
		std::cout << " Enter the details : ";
		std::cin.ignore();
		getline(std::cin, details);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		execute("delete from users where " + details + ";", 1);
		setcolor(0x0a);
		std::cout << " Customer account deleted successfully...!!!\n";
		setcolor(0x07);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		execute("select * from users where type='customer';", 4);
		Receptionist_customers c4(this->id);
		break;
	}
	case 5:
	{
		Receptionist rp(this->id);
		break;
	}
	default:
		break;
	}
}