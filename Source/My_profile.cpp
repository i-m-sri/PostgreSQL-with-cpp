#include "My_profile.h"

My_profile::My_profile(std::string user)
{
    profile_name = user;
    std::cout << " MANAGE MY PROFILE\n -----------------\n";
    std::cout << " 1.Change Name\n 2.Change password\n 3.Change MailID\n 4.Change Address\n 5.Buy Membership\n 6.Go Back\n\n";
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
        std::cout << " CHANGE NAME\n -----------\n\n";
        std::cout << " Enter the new name : ";
        std::cin.ignore();
        getline(std::cin, name);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update customers set name='" + name + "' where name='" + profile_name + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Name changed successfully\n";
        setcolor(0x07);
        sql = "select * from customers where name='"+profile_name+"';";
        execute(sql, 0);
        My_profile obj(profile_name);
        break;
    }
    case 2:
    {
        std::string password;
        std::cout << " CHANGE PASSWORD\n ---------------\n\n";
        std::cout << " Enter the new password : ";
        std::cin.ignore();
        getline(std::cin, password);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update customers set password='" + password + "' where name='" + profile_name + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Password changed successfully\n";
        setcolor(0x07);
        sql = "select * from customers where name='" + profile_name + "';";
        execute(sql, 0);
        My_profile obj(profile_name);
        break;
    }
    case 3:
    {
        std::string mail;
        std::cout << " CHANGE MAILID\n -------------\n\n";
        std::cout << " Enter the new mail id : ";
        std::cin.ignore();
        getline(std::cin, mail);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update customers set mail='" + mail + "' where name='" + profile_name + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Mail ID changed successfully\n";
        setcolor(0x07);
        sql = "select * from customers where name='" + profile_name + "';";
        execute(sql, 0);;
        My_profile obj(profile_name);
        break;
    }
    case 4:
    {
        std::string address;
        std::cout << " CHANGE ADDRESS\n ---------------\n\n";
        std::cout << " Enter the new address : ";
        std::cin.ignore();
        getline(std::cin, address);
        std::cout << "_______________________________________________________________________________________\n\n";
        sql = "update customers set address='" + address + "' where name='" + profile_name + "';";
        execute(sql, 1);
        setcolor(0x0a);
        std::cout << " Address changed successfully\n";
        setcolor(0x07);
        sql = "select * from customers where name='" + profile_name + "';";
        execute(sql, 0);
        My_profile obj(profile_name);
        break;
    }
    case 5:
    {
        char membership_option;
        std::cout << " MEMBERSHIP PURCHASE\n -------------------\n\n";
        std::cout << "\n Membership account gives you privilege to extra discouts and offers...!!!\n";
        std::cout << "\n Buy membership(y/n) : ";
        std::cin >> membership_option;
        std::cout << "_______________________________________________________________________________________\n\n";
        if (membership_option == 'y')
        {
            execute("update customers set membership='Y' where name='"+profile_name+"';", 1);
            setcolor(0x0a);
            std::cout << " Purchased Successfuly\n";
            setcolor(0x07);
        }
        My_profile obj(profile_name);
        break;
    }
    case 6:
    {
        Customer_page2 obj(profile_name);
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