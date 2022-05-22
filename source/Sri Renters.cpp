#include<iostream>
#include"Open_app.h"
#include"Postgresql.h"

int main()
{
	execute("select carid,current_holder from cars where return_time=current_date-1;", 5);
	char choice;
	std::cout << "\n             SRIRAM RENTERS LTD\n             ------ ------- ---\n";
	std::cout << "     Ph.no:9229935289, Mail:srirents@gmail.com\n";
	std::cout << " ________________________________________________________________________________________________________\n\n";
	do {
		Open_app app;
		std::cout << " Do you want to continue with app(y/n) : ";
		std::cin >> choice;
		std::cout << " ________________________________________________________________________________________________________\n\n";
	} while (choice == 'y');
}
