#include"Postgresql.h"
#include"VariadicTable.h"
#include"textcolor.h"

void execute(std::string sql, int flag)
{
	try {
		int i = 1;
		pqxx::connection database("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
		if (flag==1)
		{
			pqxx::work w(database);
			w.exec(sql);
			w.commit();
		}
		else if (flag == 2)
		{
			pqxx::nontransaction w(database);
			pqxx::result r(w.exec(sql));
			if (r.empty())
			{
				setcolor(0x0c);
				std::cout << "\n SORRY No Cars match to your input details...!!!";
				setcolor(0x07);
				std::cout << "\n_______________________________________________________________________________________\n\n";
			}
			else {
				setcolor(0x0e);
				std::cout << "\n Cars List \n";
				VariadicTable<int, int,std::string, std::string, std::string, std::string,int> vt({ "S.no","carid","Name","Type","Price(Lakhs)","Date","Booking_status"}, 10);
				for (auto c = r.begin(); c != r.end(); c++)
				{
					vt.addRow(i, c[0].as<int>(), c[1].as<std::string>(), c[2].as<std::string>(), c[3].as<std::string>(),c[4].as<std::string>(), c[5].as<int>());
					i++;
				}
				vt.print(std::cout);
				setcolor(0x07);
				std::cout << "_______________________________________________________________________________________\n\n";
			}
		}
		else if (flag == 3)
		{
			setcolor(0x0e);
			pqxx::nontransaction w(database);
			pqxx::result r(w.exec(sql));
			VariadicTable<int, std::string, std::string, std::string, std::string> vt({ "S.no","Name","Password","Mail","Address" }, 10);
			pqxx::result::const_iterator c = r.begin();
			vt.addRow(1, c[0].as<std::string>(),c[1].as<std::string>(),c[2].as<std::string>(),c[3].as<std::string>());
			vt.print(std::cout);
			setcolor(0x07);
			std::cout << "_______________________________________________________________________________________\n";
		}
		else {
			pqxx::nontransaction w(database);
			pqxx::result r(w.exec(sql));
			if (r.empty())
			{
				setcolor(0x0c);
				std::cout << "\n SORRY No Customers match to your input details...!!!";
				setcolor(0x07);
				std::cout << "\n_______________________________________________________________________________________\n";
			}
			else {
				setcolor(0x0e);
				std::cout << "\n Customers List \n";
				VariadicTable<int, std::string, std::string, std::string, std::string> vt({ "S.no","Name","Mail","Address","Membership" }, 10);
				for (auto c = r.begin(); c != r.end(); c++)
				{
					vt.addRow(i, c[0].as<std::string>(), c[2].as<std::string>(), c[3].as<std::string>(), c[4].as<std::string>());
					i++;
				}
				vt.print(std::cout);
				setcolor(0x07);
				std::cout << "_______________________________________________________________________________________\n";
			}
		}
	}
	catch (const std::exception& e) {        //any errors or failure throws will be catched and displayed
		std::cerr << e.what() << std::endl;
	}
}

std::string execute_with_return(std::string sql)
{
	try {
		pqxx::connection database("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
		pqxx::nontransaction w(database);
		pqxx::result r(w.exec(sql));
		if (r.empty())
		{
			return "";
		}
		else {
			pqxx::result::const_iterator c = r.begin();
			return c[0].as<std::string>();
		}
	}
	catch (const std::exception& e) {        //any errors or failure throws will be catched and displayed
		std::cerr << e.what() << std::endl;
	}
}