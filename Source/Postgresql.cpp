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
			std::cout << "_______________________________________________________________________________________\n\n";
		}
		else if (flag == 4)
		{
			pqxx::nontransaction w(database);
			pqxx::result r(w.exec(sql));
			w.commit();
			if (r.empty()) { return; }
			else {
				int i = 1;
				std::cout << " ANNOUNCEMENTS\n -------------\n\n";
				for (pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
				{
					std::string s = "insert into notifications values('Car " + c[1].as<std::string>() + " with id:" + c[0].as<std::string>() + " Returned back to booking'," + c[0].as<std::string>() + ");";
					execute(s, 1);
					pqxx::nontransaction h(database);
					pqxx::result f(h.exec("select message from notifications where carid=" + c[0].as<std::string>() + ";"));
					h.commit();
					pqxx::result::const_iterator b = f.begin();
					setcolor(0x0a);
					std::cout << " "<<i<<") " << b[0].as<std::string>() << "\n\n";
					setcolor(0x07);
					execute("delete from notifications where carid=" + c[0].as<std::string>() + ";", 1);
					execute("update cars set return_time='2000-01-01 00:00:00',booking_status=0 where carid=" + c[0].as<std::string>() + ";", 1);
					i++;
				}
			}
			std::cout << "_______________________________________________________________________________________\n\n";
		}
		else {
			pqxx::nontransaction w(database);
			pqxx::result r(w.exec(sql));
			if (r.empty())
			{
				setcolor(0x0c);
				std::cout << "\n SORRY No Customers match to your input details...!!!";
				setcolor(0x07);
				std::cout << "\n_______________________________________________________________________________________\n\n";
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
				std::cout << "_______________________________________________________________________________________\n\n";
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