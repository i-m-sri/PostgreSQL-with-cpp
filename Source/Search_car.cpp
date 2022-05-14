#include"Search_car.h"

void search_a_car()
{
	char continue_option;
	do {
		int search_option;
		std::string sql = "select * from cars";
		execute(sql, 2);
		std::cout << " SEARCH CARS\n -----------\n";
		std::cout << " 1.Search car by price\n 2.Search car by type\n 3.Search car by date\n 4.Go Back\n\n";
		std::cout << " Select your search option : ";
		std::cin >> search_option;
		std::cout << "_______________________________________________________________________________________\n\n";
		switch (search_option)
		{
		case 1:
		{
			int minimum_price, maximum_price;
			std::cout << " Search by price\n\n";
			std::cout << " Enter the minimum range of price : ";
			std::cin >> minimum_price;
			std::cout << " Enter the maximum range of price : ";
			std::cin >> maximum_price;
			std::cout << "\n The cars at the price range " + std::to_string(minimum_price) + " to " + std::to_string(maximum_price) + " are:-\n";
			sql += " where price between " + std::to_string(minimum_price) + " and " + std::to_string(maximum_price) + " order by price;";
			execute(sql, 2);
			break;
		}
		case 2:
		{
			std::string type;
			std::cout << " Search by Type\n\n";
			std::cout << " Enter the type of Car you are lookin for : ";
			std::cin >> type;
			std::cout << "\n The cars with type " + type + " are :-\n";
			sql += " where type='" + type + "';";
			execute(sql, 2);
			break;
		}
		case 3:
		{
			std::string minimum_date, maximum_date;
			std::cout << " Search by Date\n\n";
			std::cout << " Enter the minimum date(yyyy-mm-dd) : ";
			std::cin >> minimum_date;
			std::cout << " Enter the maximum date(yyyy-mm-dd) : ";
			std::cin >> maximum_date;
			std::cout << "\n The cars at the date between " + minimum_date + " to " + maximum_date + " are:-\n";
			sql += " where date>='" + minimum_date + "' and date<='" + maximum_date + "' order by date;";
			execute(sql, 2);
			break;
		}
		default:
			break;
		}
		std::cout << " Do you want to continue your search(y/n) : ";
		std::cin >> continue_option;
		std::cout << "_______________________________________________________________________________________\n\n";
	} while (continue_option == 'y');
}