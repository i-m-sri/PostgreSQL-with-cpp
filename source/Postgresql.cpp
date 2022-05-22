#include "Postgresql.h"

std::string get_value(std::string query)
{
	connection database("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
	nontransaction w(database);
	result r(w.exec(query));
	if (r.empty()){return "";}
	else {
		result::const_iterator c = r.begin();
		return c[0].as<std::string>(); 
	}
}

void execute(std::string query, int flag)
{
	int i = 1;
	try{
	connection database("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
	if (flag == 1)
	{
		work w(database);
		w.exec(query);
		w.commit();
	}
	else if (flag == 2)
	{
		nontransaction w(database);
		result r(w.exec(query));
		if (r.empty())
		{
			setcolor(0x0c);
			std::cout << "\n SORRY No Cars match to your input details...!!!";
			setcolor(0x07);
			std::cout << "\n________________________________________________________________________________________________________\n\n";
		}
		else {
			setcolor(0x0e);
			std::cout << "\n Cars List \n";
			VariadicTable<int, int, std::string, std::string, std::string, std::string> vt({ "S.no","carid","Name","Type","Price(Lakhs)","Date" }, 10);
			for (auto c = r.begin(); c != r.end(); c++)
			{
				vt.addRow(i, c[0].as<int>(), c[1].as<std::string>(), c[2].as<std::string>(), c[3].as<std::string>(), c[4].as<std::string>());
				i++;
			}
			vt.print(std::cout);
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
	}
	else if (flag == 3)
	{
		int u = 1;
		std::cout << "\n HISTORY\n -------\n";
		nontransaction w(database);
		result r(w.exec(query));
		if (r.empty())
		{
			std::cout << " No history of purchase\n";
			std::cout << " ________________________________________________________________________________________________________\n\n";
			return;
		}
		for (result::const_iterator c = r.begin(); c != r.end(); c++)
		{
			std::cout << " " << u << ") " +c[0].as<std::string>()<< std::endl;
			u++;
		}
		std::cout << " ________________________________________________________________________________________________________\n\n";
	}
	else if (flag == 4)
	{
		nontransaction w(database);
		result r(w.exec(query));
		if (r.empty())
		{
			setcolor(0x0c);
			std::cout << "\n SORRY No Customers match to your input details...!!!";
			setcolor(0x07);
			std::cout << "\n________________________________________________________________________________________________________\n\n";
		}
		else {
			setcolor(0x0e);
			std::cout << "\n Users List \n";
			VariadicTable<int, int, std::string, std::string,std::string, std::string, int> vt({ "S.no","ID","Name","Mobile","Mail","Address","Reservation Count" }, 10);
			for (auto c = r.begin(); c != r.end(); c++)
			{
				vt.addRow(i, c[0].as<int>(), c[1].as<std::string>(), c[2].as<std::string>(), c[3].as<std::string>(), c[4].as<std::string>(),c[7].as<int>());
				i++;
			}
			vt.print(std::cout);
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
	}
	else if (flag == 5)
	{
		nontransaction w(database);
		result r(w.exec(query));
		if (r.empty()) { return; }
		else {
			std::string carname;
			for (result::const_iterator c = r.begin(); c != r.end(); c++)
			{
				carname = get_value("select name from cars where carid=" + to_string(c[0].as<int>()));
				execute("update users set booking_count=booking_count-1 where id=" + to_string(c[1].as<int>()), 1);
				execute("update cars set return_time='2000-01-01 00:00:00',current_holder=NULL where carid=" + to_string(c[0].as<int>()) + ";", 1);
				std::thread return_car(execute, "delete from messages where userid=" + to_string(c[1].as<int>()) + " and car id=" + to_string(c[0].as<int>()) + ";", 1);
				return_car.join();
				std::thread send_notifications(execute, "update messages set notification='Your reserved car " + carname + " with id:" + to_string(c[0].as<int>()) + " is now available for booking' where carid=" + to_string(c[0].as<int>()) + ";", 1);
				send_notifications.join();
			}
		}
	}
    }
	catch (const std::exception& e) {        
		std::cerr << e.what() << std::endl;
	}
}

void check_inbox(std::string id, int flag)
{
	connection database("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
	nontransaction w(database);
	result r(w.exec("select notification from messages where userid="+id));
	if (r.empty()) { return; }
	else {
		int u = 1;
		result::const_iterator c = r.begin();
		if (c[0].as<std::string>() != "NIL") {
			std::cout << "\n NOTIFICATIONS\n -------------\n";
			for (result::const_iterator c = r.begin(); c != r.end(); c++)
			{
				std::cout << " " << u << ") " + c[0].as<std::string>() << std::endl;
				u++;
			}
			std::cout << " ________________________________________________________________________________________________________\n\n";
			if (flag) 
			{
				std::cout << " Do you want to mark these notications as read(y/n) : ";
				char choice;
				std::cin >> choice;
				std::cout << " ________________________________________________________________________________________________________\n\n";
				if (choice == 'y')
				{
					execute("update messages set notification='NIL' where userid=" + id, 1);
				}
			}
		}
	}
}