#include "Edit_customer.h"

Edit_customer::Edit_customer()
{
	std::string details,set_condition,sql;
	std::cout << "\n Current Customers are :-\n";
	sql = "select * from customers";
	execute(sql, 0);
	std::cout << "\n EDIT CUSTOMER\n ----------------\n\n";
	std::cout << " Enter the details of the customer you want to edit\n";
	std::cout << " (For example : name='customername',membership='N',etc...)\n\n";
	std::cout << " Enter the details : ";
	std::cin.ignore();
	getline(std::cin, details);
	std::cout << "_______________________________________________________________________________________\n\n";
	std::cout << " Enter the new data of the customer\n";
	std::cout << " (For example : name='customername',membership='N',etc...)\n\n";
	std::cout << " Enter the new data : ";
	getline(std::cin, set_condition);
	sql = "update customers set "+set_condition+" where " + details + ";";
	execute(sql, 1);
	setcolor(0x0a);
	std::cout << " Customer details edited successfully";
	setcolor(0x07);
	std::cout << "\n_______________________________________________________________________________________\n\n";
	sql = "select * from customers";
	execute(sql, 0);
	Search_and_manage_customers obj;
}