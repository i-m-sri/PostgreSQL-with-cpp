#include "Login.h"
#include"Postgresql.h"

Login::Login()
{
	std::cout << " LOGIN\n -----\n";
	std::cout << " Enter the username(mobile or mailid) : ";
	std::cin >> username;
	username_check(username);
}

void Login::username_check(std::string username)
{
	if (get_value("select password from users where mobile_number='" + username + "' or mail='" + username + "';")!="")
	{
		std::cout << " Enter the password : ";
		std::cin >> password;
		std::cout << " ________________________________________________________________________________________________________\n\n";
		if (password == get_value("select password from users where mobile_number='" + username + "' or mail='" + username + "';"))
		{
			setcolor(0x0a);
			std::cout << " Logged in \n";
			setcolor(0x07);
			std::cout << " ________________________________________________________________________________________________________\n\n";
			role_selection();
		}
		else {
			char choice;
			setcolor(0x0c);
			std::cout << " OPPS the password is in correct\n\n";
			setcolor(0x07);
			std::cout<<" Do you want to retry it(y / n) : ";
			std::cin >> choice;
			std::cout << " ________________________________________________________________________________________________________\n\n";
			if(choice=='y'){ username_check(this->username); }
			else { Login a; }
		}
	}
	else { 
		std::cout << " ________________________________________________________________________________________________________\n\n";
		setcolor(0x0c);
		std::cout << " No such user\n"; 
		setcolor(0x07);
		std::cout << " ________________________________________________________________________________________________________\n\n";
		Login a;
	}
}

void Login::role_selection()
{
	if (get_value("select type from users where mobile_number='" + username + "' or mail='" + username + "';")=="receptionist")
	{
		Receptionist r(stoi(get_value("select id from users where mobile_number = '" + username + "' or mail = '" + username + "'; ")));
	}
	else
	{
		
		execute("select history from messages where userid=" + get_value("select id from users where mobile_number = '" + username + "' or mail = '" + username + "'; "), 3);
		check_inbox(get_value("select id from users where mobile_number = '" + username + "' or mail = '" + username + "'; "),1);
		Customer c(stoi(get_value("select id from users where mobile_number = '" + username + "' or mail = '" + username + "'; ")));
		return;
	}
}