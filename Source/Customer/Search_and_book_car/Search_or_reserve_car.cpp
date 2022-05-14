#include "Search_or_reserve_car.h"
#include"Search_car.h"

Search_or_reserve_car::Search_or_reserve_car(std::string user)
{
	this->user = user;
	std::cout << " SEARCH AND RESERVE CAR\n ----------------------\n";
	std::cout << " 1.Search a car\n 2.Book a car\n 3.Go Back\n\n";
	std::cout << " Choose your option : ";
	std::cin >> customer_operation;
	std::cout << "_______________________________________________________________________________________\n\n";
	Search_or_reserve_car::customer_car_operation(Search_or_reserve_car::get_customer_operation());
}

void Search_or_reserve_car::customer_car_operation(int flag)
{
	std::string sql;
	if(flag==1)
	{
		search_a_car();
		Search_or_reserve_car car(user);
	}
	else if(flag==2) {
		std::string details;
		sql = "select * from cars";
		execute(sql, 2);
			std::string ID;
			std::cout << " BOOK  A CAR\n -----------\n\n";
			std::cout << " Enter the ID of the car you want to reserve\n\n";
			std::cout << " Enter the car ID : ";
			std::cin.ignore();
			getline(std::cin, ID);
			std::cout << "_______________________________________________________________________________________\n\n";
			if (std::stoi((execute_with_return("select booking_status from cars where carid=" + ID + ";"))) < 2)
			{
				sql = "update cars set booking_status=booking_status+1 where carid=" + ID + ";";
				execute(sql, 1);
				setcolor(0x0a);
				std::cout << " Car booked successfully\n";
				setcolor(0x07);
				std::cout << "_______________________________________________________________________________________\n\n";
				Search_or_reserve_car ob(user);
			}
			else {
				setcolor(0x0c);
				std::cout << " Sorry the car you are looking for is already reserved twice...!!!\n";
				setcolor(0x07);
				std::cout << "_______________________________________________________________________________________\n\n";
				Search_or_reserve_car ob(user);
			}
	}
	else {
		Customer_page2 obj(user);
		return;
	}
	booking:
		{
		std::string ID;
			std::cout << " BOOK  A CAR\n -----------\n\n";
			std::cout << " Enter the ID of the car you want to reserve\n\n";
			std::cout << " Enter the car ID : ";
			std::cin.ignore();
			getline(std::cin, ID);
			std::cout << "_______________________________________________________________________________________\n\n";
			if (std::stoi((execute_with_return("select booking_status from cars where carid=" + ID + ";"))) < 2)
			{
				sql = "update cars set booking_status=booking_status+1 where carid=" + ID + ";";
				execute(sql, 1);
				setcolor(0x0a);
				std::cout << " Car booked successfully\n";
				setcolor(0x07);
				std::cout << "_______________________________________________________________________________________\n\n";
				Search_or_reserve_car ob(user);
			}
			else {
				setcolor(0x0c);
				std::cout << " Sorry the car you are looking for is already reserved twice...!!!\n";
				setcolor(0x07);
				std::cout << "_______________________________________________________________________________________\n\n";
				Search_or_reserve_car ob(user);
			}
		}
}

int Search_or_reserve_car::get_customer_operation()
{
	return customer_operation;
}