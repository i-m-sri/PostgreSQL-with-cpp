#include "My_Account.h"

My_Account::My_Account()
{
    std::cout << " MANAGE MY ACCOUNT\n -----------------\n\n";
    std::cout << " 1.Change Name\n 2.Change password\n 3.Change MailID\n 4.Change Address\n 5.Go Back\n\n";
    std::cout << " Select your option : ";
    std::cin >> account_management_option;
    std::cout << "_______________________________________________________________________________________\n\n";
    account_management();
}

void My_Account::account_management()
{
    std::string sql;
    switch (get_account_management_option())
    {
    case 1:
    {
        std::string name;
        std::cout << "\n CHANGE NAME\n -----------\n\n";
        std::cout << " Enter the new name : ";
        std::cin.ignore();
        getline(std::cin,name);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update receptionist set name='" + name + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Name changed successfully\n";
        setcolor(0x07);
        sql = "select * from receptionist;";
        execute(sql, 3);
        My_Account obj;
        break;
    }
    case 2:
    {
        std::string password;
        std::cout << "\n CHANGE PASSWORD\n ---------------\n\n";
        std::cout << " Enter the new password : ";
        std::cin.ignore();
        getline(std::cin, password);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update receptionist set password='" + password + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Password changed successfully\n";
        setcolor(0x07);
        sql = "select * from receptionist;";
        execute(sql, 3);
        My_Account obj;
        break;
    }
    case 3:
    {
        std::string mail;
        std::cout << "\n CHANGE MAILID\n -------------\n\n";
        std::cout << " Enter the new mail id : ";
        std::cin.ignore();
        getline(std::cin, mail);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update receptionist set mail='" + mail + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Mail ID changed successfully\n";
        setcolor(0x07);
        sql = "select * from receptionist;";
        execute(sql, 3);
        My_Account obj;
        break;
    }
    case 4:
    {
        std::string address;
        std::cout << "\n CHANGE ADDRESS\n ---------------\n\n";
        std::cout << " Enter the new address : ";
        std::cin.ignore();
        getline(std::cin, address);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update receptionist set address='" + address + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Address changed successfully\n";
        setcolor(0x07);
        sql = "select * from receptionist;";
        execute(sql, 3);
        My_Account obj;
        break;
    }
    case 5:
    {
        Receptionist obj(0);
        break;
    }
    default:
        break;
    }
}
int My_Account::get_account_management_option()
{
    return account_management_option;
}