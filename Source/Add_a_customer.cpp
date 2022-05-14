#include "Add_a_customer.h"

Add_a_customer::Add_a_customer()
{
	std::string customer_name, customer_mail, customer_address, membership,sql;
	sql = "select * from customers";
	execute(sql, 0);
	std::cout << "\n ADD CUSTOMER\n ----------------\n\n";
	std::cout << " Enter the Customer name : ";
	std::cin.ignore();
	std::getline(std::cin, customer_name);
	std::cout << "\n Enter the Customer mail id : ";
	std::cin >> customer_mail;
	std::cout << "\n Enter the Customer address : ";
	std::cin.ignore();
	std::getline(std::cin, customer_address);
	std::cout << "\n Do this customer has membership privilege(Y/N) : ";
	std::cin >> membership;
	sql = "insert into customers(name,password,mail,address,membership) values('" + customer_name + "','" + customer_name + "@rg','" + customer_mail + "','" + customer_address + "','" + membership + "');";
	setcolor(0x0a);
	std::cout << "\n\n Customer Added...\n";
	setcolor(0x07);
	std::cout << "_______________________________________________________________________________________\n";
	execute(sql, 1);
	sql = "select * from customers;";
	execute(sql, 0);
	Search_and_manage_customers obj;
}