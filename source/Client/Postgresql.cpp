#include "Postgresql.h"

std::string get_value(std::string query)
{
	long status;
	SOCKET sock;
	SOCKADDR_IN address;
	WSAData WSD;
	WORD Dllversion;
	Dllversion = MAKEWORD(2, 1);
	status = WSAStartup(Dllversion, &WSD);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_family = AF_INET;
	address.sin_port = htons(3000);
	std::string sql;
	connect(sock, (SOCKADDR*)&address, sizeof(address));
	sql = "6" + query;
	const char* s = sql.c_str();
	status = send(sock, s, 1024, NULL);
	char rply[50]="";
	status = recv(sock, rply, 50, NULL);
	if (strcmp(rply,"xxx")==0)
	{  
		closesocket(sock);
		WSACleanup();
		return "";
	}
	else 
	{
		std::string s = rply;
		closesocket(sock);
		WSACleanup();
		return s;
	}
}

void execute(std::string query, int flag)
{
	long status;
	SOCKET sock;
	SOCKADDR_IN address;
	WSAData WSD;
	WORD Dllversion;
	Dllversion = MAKEWORD(2, 1);
	status = WSAStartup(Dllversion, &WSD);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_family = AF_INET;
	address.sin_port = htons(3000);
	std::string sql;
	int i = 1;
	try{
	connection database("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
	if (flag == 1)
	{
		connect(sock, (SOCKADDR*)&address, sizeof(address));
		sql = "1" + query;
		const char* s = sql.c_str();
		status = send(sock, s, 1024, NULL);
	}
	else if (flag == 2)
	{
		connect(sock, (SOCKADDR*)&address, sizeof(address));
		sql = "2" + query;
		const char* s = sql.c_str();
		status = send(sock, s, 1024, NULL);
		char rply[1000] = "";
		status = recv(sock,rply, 1000, NULL);
		if (strcmp(rply,"xxx")==0)
		{
			setcolor(0x0c);
			std::cout << "\n SORRY No Cars match to your input details...!!!";
			setcolor(0x07);
			std::cout << "\n________________________________________________________________________________________________________\n\n";
		}
		else
		{
			std::string cardetails[5];
			setcolor(0x0e);
			std::cout << "\n Cars List \n";
			VariadicTable<int, std::string, std::string, std::string, std::string, std::string> vt({ "S.no","carid","Name","Type","Price(Lakhs)","Date" }, 10);
			char* ptr;
			ptr = strtok(rply, "|");
			while (ptr != NULL)
			{
				for (int k = 0; k < 5; k++)
				{
					cardetails[k] = ptr;
					ptr = strtok(NULL, " | ");
				}
				vt.addRow(i++, cardetails[0], cardetails[1], cardetails[2], cardetails[3], cardetails[4]);
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
		connect(sock, (SOCKADDR*)&address, sizeof(address));
		sql = "0" + query;
		const char* s = sql.c_str();
		status = send(sock, s, 1024, NULL);
		char rply[1000] = "";
		status = recv(sock, rply, sizeof(rply), NULL);
		if (strcmp(rply, "xxx") == 0)
		{
			std::cout << " No history of purchase\n";
			std::cout << " ________________________________________________________________________________________________________\n\n";
		}
		else
		{
			std::string s="";
			for (int i = 0; i < strlen(rply); i++)
			{
				if (rply[i] != '|')
				{
					s += rply[i];
				}
				else
				{
					std::cout << " " << u << ") " + s << std::endl;
					s = "";
					u++;
				}
			}
			std::cout << " ________________________________________________________________________________________________________\n\n"; 
		}
	}
	else if (flag == 4)
	{
		/*nontransaction w(database);
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
		}*/
		connect(sock, (SOCKADDR*)&address, sizeof(address));
		sql = query;
		const char* s = sql.c_str();
		status = send(sock, s, 1024, NULL);
		char rply[1000] = "";
		status = recv(sock, rply, 1000, NULL);
		/**std::cout << rply << "\n\n";
		for (int g = 0; g < strlen(rply); g++)
		{
			if (rply[g] == ' ')
			{
				rply[g] = '_';
			}
		}
		std::cout << rply << "\n\n";*/
		if (strcmp(rply, "xxx") == 0)
		{
			setcolor(0x0c);
			std::cout << "\n SORRY No Customers match to your input details...!!!";
			setcolor(0x07);
			std::cout << "\n________________________________________________________________________________________________________\n\n";
		}
		else
		{
			std::string customerdetails[6],temp="";
			int a = 0;
			setcolor(0x0e);
			std::cout << "\n Customers List \n";
			VariadicTable<int, std::string, std::string, std::string, std::string, std::string, std::string> vt({ "S.no","ID","Name","Mobile","Mail","Address","Reservation Count" }, 10);
			for (int j = 0; j < strlen(rply); j++)
			{
				if (rply[j] != '|')
					temp += rply[j];
				else
				{
					customerdetails[a++] = temp;
					temp = "";
					if (a == 6)
					{
						vt.addRow(i, customerdetails[0], customerdetails[1], customerdetails[2], customerdetails[3], customerdetails[4],customerdetails[5]);
						a = 0;
					}
				}
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
	closesocket(sock);
	WSACleanup();
}

void check_inbox(std::string id, int flag)
{
	long status;
	SOCKET sock;
	SOCKADDR_IN address;
	WSAData WSD;
	WORD Dllversion;
	Dllversion = MAKEWORD(2, 1);
	status = WSAStartup(Dllversion, &WSD);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_family = AF_INET;
	address.sin_port = htons(3000);
	std::string sql = "0select notification from messages where userid=" + id;
	connect(sock, (SOCKADDR*)&address, sizeof(address));
	const char* s = sql.c_str();
	status = send(sock, s, 1024, NULL);
	char rply[300];
	status = recv(sock, rply, sizeof(rply), NULL);
	if (rply[0] == 'x') { return; }
	else 
	{
		int u = 1;
		if (rply[0] != 'N')
		{
			std::cout << "\n NOTIFICATIONS\n -------------\n";
			std::string s = "";
			for (int i = 0; i < strlen(rply); i++)
			{
				if (rply[i] != ',')
				{
					s += rply[i];
				}
				else
				{
					std::cout << " " << u << ") " + s <<std::endl;
					u++;
					s = "";
				}
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
	closesocket(sock);
	WSACleanup();
}