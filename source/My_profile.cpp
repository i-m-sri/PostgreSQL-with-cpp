#include "My_profile.h"

My_profile::My_profile(int s)
{
    this->userid = s;
    std::cout << " MANAGE MY ACCOUNT\n -----------------\n\n";
    std::cout << " 1.Change Name\n 2.Change password\n 3.Change Mobile number\n 4.Change MailID\n 5.Change Address\n 6.Go Back\n\n";
    std::cout << " Select your option : ";
    std::cin >> profile_management_option;
    std::cout << "_______________________________________________________________________________________\n\n";
    profile_management();
}

void My_profile::profile_management()
{
    std::string sql;
    switch (get_profile_management_option())
    {
    case 1:
    {
        std::string name;
        std::cout << "\n CHANGE NAME\n -----------\n\n";
        std::cout << " Enter the new name : ";
        std::cin.ignore();
        getline(std::cin, name);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update users set name='" + name + "' where id=" + to_string(this->userid) + ";";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Name changed successfully\n";
        setcolor(0x07);
        sql = "select * from users where id=" + to_string(this->userid) + ";";
        execute(sql, 4);
        My_profile obj(this->userid);
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
        sql = "update users set password='" + password + "' where id=" + to_string(this->userid) + ";";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Password changed successfully\n";
        setcolor(0x07);
        sql = "select * from users where id=" + to_string(this->userid) + ";";
        execute(sql, 4);
        My_profile obj(this->userid);
        break;
    }
    case 3:
    {
        std::string mobile;
        std::cout << "\n CHANGE MOBILE NUMBER\n --------------------\n\n";
        std::cout << " Enter the new mobile number : ";
        std::cin.ignore();
        getline(std::cin, mobile);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update users set mobile_number=" + mobile + " where id=" + to_string(this->userid) + ";";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Password changed successfully\n";
        setcolor(0x07);
        sql = "select * from users where id=" + to_string(this->userid) + ";";
        execute(sql, 4);
        My_profile obj(this->userid);
        break;
    }
    case 4:
    {
        std::string mail;
        std::cout << "\n CHANGE MAILID\n -------------\n\n";
        std::cout << " Enter the new mail id : ";
        std::cin.ignore();
        getline(std::cin, mail);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update users set mail='" + mail + "' where id=" + to_string(this->userid) + ";";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Mail ID changed successfully\n";
        setcolor(0x07);
        sql = "select * from users where id=" + to_string(this->userid) + ";";
        execute(sql, 4);
        My_profile obj(this->userid);
        break;
    }
    case 5:
    {
        std::string address;
        std::cout << "\n CHANGE ADDRESS\n ---------------\n\n";
        std::cout << " Enter the new address : ";
        std::cin.ignore();
        getline(std::cin, address);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update users set address='" + address + "' where id=" + to_string(this->userid) + ";";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Address changed successfully\n";
        setcolor(0x07);
        sql = "select * from users where id=" + to_string(this->userid) + ";";
        execute(sql, 4);
        My_profile obj(this->userid);
        break;
    }
    case 6:
    {
        Customer obj(this->userid);
        break;
    }
    default:
        break;
    }
}
int My_profile::get_profile_management_option()
{
    return profile_management_option;
}
