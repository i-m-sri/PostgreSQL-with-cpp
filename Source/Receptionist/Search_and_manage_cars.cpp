#include "Search_and_manage_cars.h"

Search_and_manage_cars::Search_and_manage_cars()
{
	cout << " SEARCH AND MANAGE CARS\n ----------------------\n\n";
	cout << " 1.Search a Car\n 2.Add a Car \n 3.Edit a Car\n 4.Delete a Car\n 5.Reserve a car\n 6.Bo Back\n\n";
	cout << " Select your option : ";
	cin >> receptionist_operation;
	cout << "_______________________________________________________________________________________\n\n";
	receptionist_page2();
}

void Search_and_manage_cars::receptionist_page2()
{
	string sql;
	switch (get_receptionist_operation())
	{
	case 1:
	{
		search_a_car();
		Search_and_manage_cars c;
		break;
	}
	case 2:
	{
		std::string car_name, car_type, car_price,car_date, sql;
		sql = "select * from cars";
		execute(sql, 2);
		std::cout << " ADD CAR\n -------\n\n";
		std::cout << " Enter the Car name : ";
		std::cin.ignore();
		std::getline(std::cin, car_name);
		std::cout << "\n Enter the Car type : ";
		std::cin >> car_type;
		std::cout << "\n Enter the Car price(In Lakhs) : ";
		std::cin>> car_price;
		std::cout << "\n Enter the Car date : ";
		std::cin >> car_date;
		cout << "_______________________________________________________________________________________\n\n";
		sql = "insert into cars(name,type,price,date) values('" + car_name + "','" + car_type + "'," + car_price + ",'" + car_date +"');";
		execute(sql, 1);
		setcolor(0x0a);
		std::cout << " Car Added...\n";
		setcolor(0x07);
		sql = "select * from cars;";
		execute(sql, 2);
		Search_and_manage_cars c;
		break;
	}
	case 3:
	{
		std::string details, set_condition, sql;
		sql = "select * from cars";
		execute(sql, 2);
		std::cout << " EDIT A CAR\n ----------\n\n";
		std::cout << " Enter the details of the car you want to edit\n";
		std::cout << " (For example : name='carname',type='cartype',etc...)\n\n";
		std::cout << " Enter the Car details : ";
		std::cin.ignore();
		getline(std::cin, details);
		std::cout << " Enter the new data of the car\n";
		std::cout << " (For example : name='carname',type='cartype',etc...)\n\n";
		std::cout << " Enter the new data : ";
		getline(std::cin, set_condition);
		cout << "_______________________________________________________________________________________\n\n";
		sql = "update cars set " + set_condition + " where " + details + ";";
		execute(sql, 1);
		setcolor(0x0a);
		std::cout << " Car Edited...\n";
		setcolor(0x07);
		sql = "select * from cars";
		execute(sql, 2);
		Search_and_manage_cars c;
		break;

	}
	case 4:
	{
		string details;
		sql = "select * from cars";
		execute(sql, 2);
		cout << "\n DELETE CAR\n ----------\n\n";
		cout << " Enter the details of the car you want to delete\n";
		cout << " (For example : name='carname',type='cartype',etc...)\n\n";
		cout << "Enter the car details : ";
		cin.ignore();
		getline(cin, details);
		cout << "_______________________________________________________________________________________\n\n";
		sql = "delete from cars where " + details + ";";
		execute(sql, 1);
		setcolor(0x0a);
		std::cout << " Car Removed...\n";
		setcolor(0x07);
		sql = "select * from cars";
		execute(sql, 2);
		Search_and_manage_cars c;
		break;
	}
	case 5:
	{
		string ID;
		sql = "select * from cars";
		execute(sql, 2);
		cout << "\n RESERVE A CAR\n -------------\n\n";
		cout << " Enter the ID of the car you want to reserve\n\n";
		cout << " Enter the car ID : ";
		cin.ignore();
		getline(cin, ID);
		cout << "_______________________________________________________________________________________\n\n";
		if (std::stoi((execute_with_return("select booking_status from cars where carid=" + ID + ";"))) < 2)
		{
			sql = "update cars set booking_status=booking_status+1 where carid=" + ID + ";";
				execute(sql, 1);
				setcolor(0x0a);
				cout << "\n Car booked successfully";
				setcolor(0x07);
		}
		else {
			setcolor(0x0c);
			cout << "\n Sorry the car you are looking for is already reserved twice...!!!";
			setcolor(0x07);
		}
		Search_and_manage_cars c;
		break;
	}
	case 6:
	{
		Receptionist obj(0);
		break;
	}
	default:
		break;
	}
}

int Search_and_manage_cars::get_receptionist_operation()
{
	return receptionist_operation;
}