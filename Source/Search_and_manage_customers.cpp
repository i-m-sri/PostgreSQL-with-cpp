#include "Search_and_manage_customers.h"
#include"Add_a_customer.h"
#include"Edit_customer.h"

Search_and_manage_customers::Search_and_manage_customers()
{
	cout << " SEARCH AND MANAGE CUSTOMERS\n ---------------------------\n";
	cout << " 1.Search a Customer\n 2.Add a Customer \n 3.Edit a Customer\n 4.Delete a Customer\n 5.Go Back\n\n";
	cout << " Select your option : ";
	cin >> receptionist_operation;
	cout << "_______________________________________________________________________________________\n\n";
	receptionist_page2();
}

void Search_and_manage_customers::receptionist_page2()
{
	string sql;
	switch (get_receptionist_operation())
	{
	case 1:
	{
		string details;
		sql = "select * from customers";
		execute(sql, 0);
		cout << "\n SEARCH CUSTOMERS\n ----------------\n\n";
		cout << " Enter the details of the customer\n";
		cout << " (For example name='customer name')\n\n";
		cout << " Enter the customer details : ";
		cin.ignore();
		getline(cin, details);
		cout << "_______________________________________________________________________________________\n\n";
		sql = "select * from customers where "+details+";";
		cout << " The Customers matching to your details are:-\n";
		execute(sql,0);
		Search_and_manage_customers obj;
		break;
	}
	case 2:
	{
		Add_a_customer customer;
		break;
	}
	case 3:
	{
		Edit_customer customer;
		break;
	}
	case 4:
	{
		string details;
		sql = "select * from customers";
		execute(sql, 0);
		cout << "\n DELETE CUSTOMER\n ----------------\n\n";
		cout << " Enter the details of the customer you want to delete\n";
		cout << " (For example : name='customername',membership='N',etc...)\n\n";
		cout << "Enter the details : ";
		cin.ignore();
		getline(cin, details);
		cout << "_______________________________________________________________________________________\n\n";
		sql = "delete from customers where " + details + ";";
		execute(sql, 1);
		setcolor(0x0a);
		cout << " Customer deleted successfully...!!!\n\n";
		setcolor(0x07);
		std::cout << "_______________________________________________________________________________________\n";
		sql = "select * from customers";
		execute(sql, 0);
		Search_and_manage_customers obj;
		break;
	}
	case 5:
	{
		Receptionist obj(0);
		break;
	}
	default:
		break;
	}
}

int Search_and_manage_customers::get_receptionist_operation()
{
	return receptionist_operation;
}