#include"VariadicTable.h"
#include<typeinfo>
#include<iostream>
#include<WinSock2.h>
#include<vector>
#include<stdlib.h>
#include<pqxx/pqxx>

#pragma warning(disable:4996)

int main()
{
	pqxx::connection db("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
	WSADATA wsd;
	int check;
	long ok;
	check = WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET connectsock;
	SOCKET listensock;
	SOCKADDR_IN addr;
	connectsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(3000);
	if (::bind(listensock, (SOCKADDR*)&addr, sizeof(addr))==0)
	{
		std::cout << "\n SERVER STARTED\n\n";
	}
	if (listen(listensock, 1)==0)
	{
		std::cout << " Server started and ready for connection\n\n";
	}
	int sz = sizeof(addr);
	int bytesr, sendb;
	char msg[500];
	while (true)
	{
		if (connectsock = accept(listensock, (SOCKADDR*)&addr, &sz))
		{
			bytesr = recv(connectsock, msg, sizeof(msg), NULL);
			std::string q = msg;
			if (q[0] == '1')
			{
				pqxx::work w(db);
				q.erase(0, 1);
				w.exec(q);
				w.commit();
			}
			else if (q[0] == '6')
			{
				std::string reply;
				pqxx::nontransaction w(db);
				q.erase(0, 1);
				pqxx::result r(w.exec(q));
				if (r.empty()) {
					reply = "xxx";
					const char* s = reply.c_str();
					ok = send(connectsock, s, reply.size(), NULL);
				}
				else {
					pqxx::result::const_iterator c = r.begin();
					reply = c[0].as<std::string>();
					const char* s = reply.c_str();
					ok = send(connectsock, s, reply.size(), NULL);
				}
			}
			else if (q[0] == '0')
			{
				std::string reply="";
				pqxx::nontransaction w(db);
				q.erase(0, 1);
				pqxx::result r(w.exec(q));
				if (r.empty())
				{
					reply = "xxx";
					const char* s = reply.c_str();
					ok = send(connectsock, s, reply.size(), NULL);
				}
				else
				{
					for (pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
					{
						reply += c[0].as<std::string>() + ",";
					}
					const char* s = reply.c_str();
					ok = send(connectsock, s, reply.size(), NULL);
				}
			}
			else if(q[0]=='2')
			{
				std::string reply = "";
				pqxx::nontransaction w(db);
				q.erase(0, 1);
				pqxx::result r(w.exec(q));
				if (r.empty())
				{
					reply = "xxx";
					const char* s = reply.c_str();
					ok = send(connectsock, s, bytesr+1, NULL);
				}
				else
				{
					for (pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
					{
						reply += c[0].as<std::string>() + "|" + c[1].as<std::string>() + "|" + c[2].as<std::string>() + "|" + c[3].as<std::string>() + "|" + c[4].as<std::string>() + "|";
					}
					const char* s = reply.c_str();
					ok = send(connectsock, s, bytesr+1, NULL);
				}
			}
			else
			{
				std::string reply = "";
				pqxx::nontransaction w(db);
				pqxx::result r(w.exec(q));
				if (r.empty())
				{
					reply = "xxx";
					const char* s = reply.c_str();
					ok = send(connectsock, s, bytesr + 1, NULL);
				}
				else
				{
					for (pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
					{
						reply += c[0].as<std::string>() + "|" + c[1].as<std::string>() + "|" + c[2].as<std::string>() + "|" + c[3].as<std::string>() + "|" + c[4].as<std::string>() + "|" + c[7].as<std::string>() + "|";
					}
					const char* s = reply.c_str();
					ok = send(connectsock, s, bytesr + 1, NULL);
				}
			}
		}
	}
	closesocket(connectsock);
	WSACleanup();
	return 0;
}
