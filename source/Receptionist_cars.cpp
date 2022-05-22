#include "Receptionist_cars.h"
#include"Search_car.h"

Receptionist_cars::Receptionist_cars(int i)
{
	this->id = i;
	std::cout << " CARS MENU\n ---------\n";
	std::cout << " 1.Search a car\n 2.Reserve a car\n 3.Add a car\n 4.Edit a car\n 5.Delete a car\n 6.Cancel Reservation\n 7.Return booked car\n 8.Go Back\n\n";
	std::cout << " Enter the option : ";
	std::cin >> cars_option;
	std::cout << " ________________________________________________________________________________________________________\n\n";
	car_operation(cars_option);
}

void Receptionist_cars::car_operation(int option)
{
	switch (option)
	{
	case 1:
	{
		search_a_car();
		Receptionist r(this->id);
		break;
	}
	case 2:
	{
		std::string userid,carid;
		std::string sql = "select * from cars";
		execute(sql, 2);
		std::cout << " Enter the user ID : ";
		std::cin >> userid;
		execute("select history from messages where userid=" + userid, 3);
		check_inbox(userid,0);
		if (stoi(get_value("select reservation_count from users where id=" + userid))<2)
		{
			std::cout << " Enter the car ID : ";
			std::cin >> carid;
			std::cout << " ________________________________________________________________________________________________________\n\n";
			if (get_value("select running_time from cars where carid=" + carid) == "00:00:00")
			{
				std::string carname = get_value("select name from cars where carid=" + carid);
				execute("update cars set running_time=current_time where carid="+carid, 1);
				if (get_value("select return_time from cars where carid=" + carid) == "2000-01-01 00:00:00")
				{
					char ch;
					std::cout << " The car you looking for is now available for booking\n\n";
					std::cout << " Do you want to book it(y/n) : ";
					std::cin >> ch;
					std::cout << " ________________________________________________________________________________________________________\n\n";
					if (ch == 'y')
					{
						std::string days;
						std::cout << " Enter the number of days you want to rent this car : ";
						std::cin >> days;
						execute("update cars set return_time=current_date+" + days + ",current_holder="+userid+" where carid = " + carid, 1);
						std::thread book_a_car(execute,"insert into messages(userid,history,carid) values("+userid+",'Booked "+carname+" with id:"+carid+" on:'||current_timestamp,"+carid+");",1);
						book_a_car.join();
						std::cout << " ________________________________________________________________________________________________________\n\n";
						setcolor(0x0a);
						std::cout << " Car booked successfully\n";
						setcolor(0x07);
						execute("update users set booking_count=booking_count+1 where id=" + userid, 1);
						std::cout << " ________________________________________________________________________________________________________\n\n";
						execute("update cars set running_time='00:00:00' where carid=" + carid, 1);
						Receptionist_cars r(this->id);
					}
					else {
						char ch2;
						std::cout << " Do you want to reserve this car(y/n) : ";
						std::cin >> ch2;
						std::cout << " ________________________________________________________________________________________________________\n\n";
						if (ch2 == 'y')
						{
							setcolor(0x0a);
							std::cout << " Car reserved successfully\n";
							setcolor(0x07);
							execute("update cars set running_time='00:00:00' where carid=" + carid, 1);
							execute("update users set reservation_count=reservation_count+1 where id=" + userid, 1);
							execute("insert into messages(userid,history,carid,time) values(" + userid + ",'Reserved " + carname + " with id:" + carid + " on '||current_timestamp," + carid + ",current_timestamp);", 1);
							std::cout << " ________________________________________________________________________________________________________\n\n";
							Receptionist_cars r(this->id);
						}
						else { 
							execute("update cars set running_time='00:00:00' where carid=" + carid, 1);
							Receptionist_cars r(this->id);
						}
					}

				}
				else {
					char ch3;
					setcolor(0x0c);
					std::cout << " The car you looking for is in use by other user\n\n";
					setcolor(0x07);
					std::cout << " Do you want to reserve this car(y/n) : ";
					std::cin >> ch3;
					std::cout << " ________________________________________________________________________________________________________\n\n";
					if (ch3 == 'y')
					{
						setcolor(0x0a);
						std::cout << " Car reserved successfully\n";
						setcolor(0x07);
						execute("update cars set running_time='00:00:00' where carid=" + carid, 1);
						execute("update users set reservation_count=reservation_count+1 where id=" + userid, 1);
						execute("insert into messages(userid,history,carid,time) values(" + userid + ",'Reserved " + carname + " with id:" + carid + " on '||current_timestamp," +carid+",current_timestamp);", 1);
						std::cout << " ________________________________________________________________________________________________________\n\n";
						Receptionist_cars r(this->id);
					}
					else { 
						execute("update cars set running_time='00:00:00' where carid=" + carid, 1);
						Receptionist_cars r(this->id);
					}
				}
			}
			else {
				setcolor(0x0c);
				std::cout << " Someone else is looking for the same car now please wait for sometime and try again later or look for other cars";
				setcolor(0x07);
				std::cout << " ________________________________________________________________________________________________________\n\n";
				Receptionist_cars c(this->id);
			}
		}
		else {
			setcolor(0x0c);
			std::cout << " Sorry your reservation has reached its maximum limit\n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
			Receptionist_cars cr(this->id);
		}
		break;
	}
	case 3:
	{
		std::string name, type, price, date;
		std::cout << " ADD CAR\n -------\n";
		std::cout << " Enter the car name : ";
		std::cin.ignore();
		getline(std::cin, name);
		std::cout << " Enter the car type : ";
		std::cin>>type;
		std::cout << " Enter the car price(in lakhs) : ";
		std::cin>>price;
		std::cout << " Enter the car date(yyyy-mm-dd) : ";
		std::cin>>date;
		std::cout << " ________________________________________________________________________________________________________\n\n";
		execute("insert into cars(name,type,price,date) values('"+name+"','"+type+"',"+price+",'"+date+"');", 1);
		setcolor(0x0a);
		std::cout << " Car added ...\n";
		setcolor(0x07);
		execute("select * from cars", 2);
		Receptionist_cars c(this->id);
		break;
	}
	case 4:
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
		std::cout << "\n Enter the new data of the car\n";
		std::cout << " (For example : name='carname',type='cartype',etc...)\n\n";
		std::cout << " Enter the new data : ";
		getline(std::cin, set_condition);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		sql = "update cars set " + set_condition + " where " + details + ";";
		execute(sql, 1);
		setcolor(0x0a);
		std::cout << " Car Edited...\n";
		setcolor(0x07);
		sql = "select * from cars";
		execute(sql, 2);
		Receptionist_cars c(this->id);
		break;

	}
	case 5:
	{
		std::string details,sql;
		sql = "select * from cars";
		execute(sql, 2);
		std::cout << "\n DELETE CAR\n ----------\n\n";
		std::cout << " Enter the details of the car you want to delete\n";
		std::cout << " (For example : name='carname',type='cartype',etc...)\n\n";
		std::cout << "Enter the car details : ";
		std::cin.ignore();
		getline(std::cin, details);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		sql = "delete from cars where " + details + ";";
		execute(sql, 1);
		setcolor(0x0a);
		std::cout << " Car Removed...\n";
		setcolor(0x07);
		sql = "select * from cars";
		execute(sql, 2);
		Receptionist_cars c(this->id);
		break;
	}
	case 6:
	{
		std::string userid,carid;
		std::cout << " Enter the user ID : ";
		std::cin >> userid;
		execute("select history from messages where userid=" + userid, 3);
		std::cout << " Enter the id of the car you want to cancel reservation : ";
		std::cin >> carid;
		if (get_value("select history from messages where userid=" + userid + " and carid=" + carid)[0] == 'R')
		{
			execute("update users set reservation_count=reservation_count-1 where id=" + userid, 1);
			execute("delete from messages where userid=" + userid + " and carid=" + carid + ";", 1);
			execute("update cars set return_time='2000-01-01 00:00:00',current_holder=NULL where carid=" + carid + ";", 1);
			std::cout << " ________________________________________________________________________________________________________\n\n";
			setcolor(0x0a);
			std::cout << " Reservation cancelled...!!!\n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
		else
		{
			std::cout << " ________________________________________________________________________________________________________\n\n";
			setcolor(0x0c);
			std::cout << " You have not Reserved this car please enter any Reserved car id to cancel reservation\n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
		Receptionist_cars c(this->id);
		break;
	}
	case 7:
	{
		std::string carid,userid;
		std::cout << " Enter the user id : ";
		std::cin >> userid;
		execute("select history from messages where userid=" + userid, 3);
		std::cout << " Enter the id of the car you want to return : ";
		std::cin >> carid;
		if (get_value("select history from messages where userid=" + userid + " and carid=" + carid)[0] == 'B')
		{
			std::string carname = get_value("select name from cars where carid=" + carid);
			execute("update users set booking_count=booking_count-1 where id=" + userid, 1);
			execute("update cars set return_time='2000-01-01 00:00:00',current_holder=NULL where carid=" + carid + ";", 1);
			std::thread return_car(execute, "delete from messages where userid=" + userid + " and carid=" + carid + ";", 1);
			return_car.join();
			std::thread send_notifications(execute, "update messages set notification='Your reserved car " + carname + " with id:" + carid + " is now available for booking' where carid=" + carid + ";", 1);
			send_notifications.join();
			std::cout << " ________________________________________________________________________________________________________\n\n";
			setcolor(0x0a);
			std::cout << " Car Returned...!!!\n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
		else
		{
			std::cout << " ________________________________________________________________________________________________________\n\n";
			setcolor(0x0c);
			std::cout << " You have not Booked this car please enter any booked car id to return\n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
		Receptionist_cars c(this->id);
		break;
	}
	case 8:
	{
		Receptionist r(this->id);
		break;
	}
	default:
		break;
	}	
}