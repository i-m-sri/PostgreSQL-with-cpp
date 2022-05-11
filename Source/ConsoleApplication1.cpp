#include <iostream>     //header file for input output streams
#include <pqxx/pqxx>    //API for postgreSQL cpp interface
#include <string>      //string headerfile
#include "VariadicTable.h"     //third party header file for priniting output in table format
#include<Windows.h>         //window header file used to change the color of the text

using namespace std;    
using namespace pqxx;    // using the namesapce pqxx

void setcolor(unsigned char color)          //function to handle the color of the text
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class Login               //LOGIN Class
{
private:
    string username,password;         //login attributes
public:
    static string query;  //variable to store query 
    string get_query()    //getter function to get query
    {
        return query;       
    }
    void set_username(string username)   //setter function to set username
    {
        this->username = username;
    }
    string get_username()     //getter funtion to get username
    {
        return username;
    }
    void set_password(string password)   //setter function to set password
    {
        this->password = password;
    }
    string get_password()      //getter function to get password
    {
        return password;
    }
};

string Login::query = "select * from users";   //initialising the static variable of Login class

class Search      //Search parent class
{ 
public :
    static string display_query;            //variable for display query
    string get_display_query()          //getter function to get query
    {
        return display_query;
    }
    string rest_of_query(int op)          //function to assign rest of the query statements
    {
        string sql;
        switch (op)
        {
        case 1:
            sql = "select * from cars where price between ";
            break;
        case 2:
            sql = "select * from cars where date>='";
            break;
        case 3:
            sql = "select * from cars where type='";
            break;
        default:
            break;
        }
        return sql;
    }
};

string Search::display_query = "select * from cars";    //initialising static variable for Search class

class Search_by_price : public Search        //derived class of Search class
{
private :
    string query;
public:
    Search_by_price(string min,string max)
    {
        query = min+" and "+max+";";     //initialising the query statement 
    }
    string query_statement()
    {
        return Search::rest_of_query(1).append(query);   /* return complete query statement after
                                                        inheriting the rest of the query fromm Search*/
    }
};

class Search_by_date : public Search         //derived class of Search class
{
private:
    string query;
public:
    Search_by_date(string min, string max)
    {
        query = min + "' and date<='" + max + "';";
    }
    string query_statement()
    {
        return Search::rest_of_query(2).append(query);
    }
};

class Search_by_type : public Search        //derived class of search class
{
private:
    string query;
public:
    Search_by_type(string type)
    {
        query = type+"';";
    }
    string query_statement()
    {
        return Search::rest_of_query(3).append(query);
    }
};
class Manage            //Manage class
{
public:
    string rest_of_query(int op)           //function to return rest of the query statement
    {
        string sql;
        switch (op)
        {
        case 1:
            sql = "insert into cars values('";
            break;
        case 2:
            sql = "update cars set ";
            break;
        case 3:
            sql = "delete from cars where ";
            break;
        default:
            break;
        }
        return sql;
    }
};

class Add :public Manage {          //derived class of Manage class
private:
    string query;                   // varibale to store query statement
public:
    string add_car(string name, string type, string price, string date)   //funtion to return query statement
    {
        query = name+"','"+type+"',"+price+",'"+date+"');";
        return Manage::rest_of_query(1).append(query);
    }
};

class Edit :public Manage {        //derived class of Manage class
private:
    string query;
public:
    string edit_car(string set_value, string car_details)
    {
        query =set_value + " where " + car_details + ";";;
        return Manage::rest_of_query(2).append(query);
    }
};

class Delete :public Manage {      //derived class of Manage class
private:
    string query;
public:
    string delete_car(string delete_condition)
    {
        query = delete_condition+";";
        return Manage::rest_of_query(3).append(query);
    }
};

int main()
{
    int i = 1;      //variable used as s.no while displaying output
    try {           //try statememt to check the connectivity and flow of work
        connection C("dbname = car_rental_management user = postgres password = sri@post hostaddr = 127.0.0.1 port = 5432");
              
        /* connection class is used to connect with our data base its arguments are
              dbname = your datase name,
              user = username of your server,
              password = password of your server,
              hostaddr = hosting id of your psql and
              port = port number of your psql */

        if (C.is_open()) {         //is_open method checks wether the database is connnected and open successfully
            setcolor(0x0e);        //setcolor funtion from windows is used to assign the colour of the text
            cout << "\n                 SRIRAM RENTERS LTD\n                 ------------------\n";
            cout << "     3WHR+3R9, MTP Road, Thudiyalur, Coimbatore-641034\n";
            cout << "      Ph.no: 063800 38432, Mail:Srirenters@gmail.com\n";
            setcolor(0x07);
            cout << "_______________________________________________________________________________________\n";
        }       
        else {
            cout << "Can't open database" << endl;
            return 1;
        }
        string username, password,sql;         //string objects for login data's and query
        int flag=0;                             // flag variable for checking the existence of the user
        setcolor(0x0A);
        cout << "\n"<<" <-----.....WELCOME TO OUR CAR RENTAL APP.....----->\n";
        setcolor(0x07);
        login_block:                            //login_block label containg login block of code
        {
            Login sql,user;
            cout << "_______________________________________________________________________________________\n\n";
            cout << " LOGIN\n -----\n";
            cout << " Enter the username : ";
            setcolor(0xa);
            getline(cin, username);            //getting username 
            setcolor(0x07);
            user.set_username(username);
            work w(C);                         //work class is used to make transactional operations in table
            result r(w.exec(sql.get_query()));            /* result class is a container to store the executed result 
                                              of the query in tuples format */
            for (result::const_iterator c = r.begin(); c != r.end(); c++)  /* setting a constant iteratorand iterating 
                                                                           through the result container 
                                                                           until it reaches the end */
            {
                if (c[0].as<string>() == user.get_username()) {        //check if the user given name matches with our username
                    flag = 1;                               //setting flag to 1 if user exist's
                    password_block:                         //password block to execute password entry operations
                    {
                        cout << " Enter the password : ";
                        setcolor(0x0a);
                        cin >> password;     //getting password from user
                        setcolor(0x07);
                        if (c[i].as<string>() == password) {     //check whether the password matches
                            cout << "\n_______________________________________________________________________________________\n";
                            setcolor(0x0A);
                            cout << "\n" <<" Logged in Successfully WELCOME " << username << "\n";     //login statement
                            setcolor(0x07);
                            user.set_password(password);
                            goto menu_block;      
                            break;
                        }
                        else {
                            int c;     
                            setcolor(0x0C); 
                            cout << "\n" << " OOPS the password is wrong...!!!\n\n";     //password failure statement
                            setcolor(0x07);
                            cout<<" 1)Retry the correct password (or)\n 2)Go Back \n\n";
                            cout << " Enter your choice : ";
                            cin >> c;
                            if (c == 1) {
                                cout << "\n";
                                goto password_block;
                            }
                            else {
                                cin.ignore();
                                cout << "\n\n";
                                goto login_block;
                            }
                        }
                    }
                }
            }
            if (flag == 0)            //if username mismatches login_block is repeated
            {
                setcolor(0x0c);
                cout << "\n"<<" Username " << username << " does not exit please enter the correct username...!!!\n\n";
                setcolor(0x07);
                goto login_block;
            }
        }
        menu_block:                      //block of code for performing menu operations
        {
            int menu_option;             // menu_option for selecting the menu options and se
            char opinion;              // opinon variable for storing the opinion of the user
            do
            {
            back:                         // block of code to perform back operation
                {
                    cout << "_______________________________________________________________________________________\n\n";
                    cout << " Search and Manage Cars\n\n";
                    cout << " MENU :-\n ----\n 1)Search\n 2)Manage\n 3)Exit Menu\n\n Select your choice : ";
                    cin >> menu_option;           //getting user's choice from menu list
                    if (menu_option == 1)         // search block
                    {
                        Search s;             //object of Search class
                        int search_by;        //variable to store the search by option
                        cout << "\n_______________________________________________________________________________________\n";
                        nontransaction w(C);          //nontransaction class to perform nontransactionakl operations in table
                        result r(w.exec(s.get_display_query()));   //getting the query from Search class      
                        cout << "\n Cars available in our app are : \n";
                        cout << " -----------------------------------\n";
                        VariadicTable<int,string,string,string,string > vt({ "S.no", "Name", "Type", "Price(Lakhs)" ,"Date"}, 10); /* object of 
                                                                                                                                   VariadicTable with 
                                                                                                                                   column name and types*/
                        for (result::const_iterator c = r.begin(); c != r.end(); c++)       //loop to add rows to table
                        {
                            vt.addRow(i,c[0].as<string>(),c[1].as<string>(),c[2].as<string>(),c[3].as<string>());
                                                      // add the output in table format separted with unform spaces
                            i++;           // increment the i in order to increment the s.no for next iter
                        }
                        setcolor(0x0e);
                        vt.print(cout);     //printing the output table
                        setcolor(0x07);
                        i = 1;             // set i=1 for strating with  1 in future operations
                        cout << "\n_______________________________________________________________________________________\n";
                        cout << "\n Search a Car as per your needs :-\n ---------------------------------\n"
                            << " 1)Price Range\n 2)Date\n 3)Type\n 4)Go Back\n\n Select your search criteria : ";
                        cin >> search_by;    // get user given search option
                        cout << "\n\n";
                        switch (search_by)    
                        {
                        case 1:              //search by price block
                        {
                           
                            cout << "_______________________________________________________________________________________\n\n";
                            cout << " Search by price range\n ----------------------\n";
                            string minimum_price, maximum_price;     // variables for price interval
                            int i = 1;
                            cout << " Enter the minimum price your are looking for : ";
                            cin >> minimum_price;                      // get minimum price
                            cout << " Enter the maximum price your are looking for : ";
                            cin >> maximum_price;                      // get maximum price
                            Search_by_price s(minimum_price,maximum_price); //object of Search_by_price class 
                            sql = s.query_statement();         //getting query
                            cout << "\n Search result for your price(in Lakhs) range.....!!!\n\n";  // display block result
                            goto Display;        // jumping to Display block 
                            break;
                        }
                        case 2:            //search by date block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            cout << " Search by Date\n --------------------\n";
                            string date, staring_date, ending_date;   //variables for start and end date
                            cout << " Enter the staring date(yyyy-mm-dd) : ";
                            cin >> staring_date;
                            cout << " Enter the ending date(yyyy-mm-dd) : ";
                            cin >> ending_date;
                            Search_by_date s(staring_date, ending_date);     //object of Search_by_date class
                            sql = s.query_statement();        //getting query
                            cout << "\n Search result for your date range.....!!!\n\n";
                            goto Display;
                            break;
                        }
                        case 3:               // search by type block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            cout << " Search by car type\n ----------------------\n";
                            string type;        // variable to store the type input given by user
                            cout << " Enter the type of car you are looking for : ";
                            cin >> type;
                            Search_by_type s(type);         //object of Search_by_type class
                            sql = s.query_statement();      //getting query;
                            cout << "\n Search result for your car type......!!!\n\n";
                            goto Display;
                            break;
                        }
                        case 4:             
                            goto back;
                            break;
                        default:
                            break;
                        }
                    }
                    else if (menu_option == 2)      //manage block
                    {
                        cout << "\n_______________________________________________________________________________________\n";
                        cout << "\n Manage cars list : \n -----------------------\n 1)Add a car\n 2)Edit a car\n 3)Remove a car\n 4)Go Back\n\n Select your option : ";
                        int manage;
                        cin >> manage;
                        cout << "\n\n";
                        switch (manage)
                        {
                        case 1:                 // add block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            string name, type, price, date;         //variables for storing car details
                            cout << " Enter the name of the car : ";
                            cin.ignore();
                            getline(cin, name);
                            cout << " Enter the type of the car : ";
                            getline(cin, type);
                            cout << " Enter the price of the car in lakh : ";
                            getline(cin, price);
                            cout << " Enter the launch date : ";
                            getline(cin, date);
                            Add a;      //oblect of Add class
                            sql = a.add_car(name,type,price,date);   //getting query
                            setcolor(0x0a);
                            cout << "\n New car Added successfully\n\n";
                            setcolor(0x07);
                            cout<<" Cars list after addition are...\n";
                            goto execute_manage;;          //jumping to execute_manage block
                            break;
                        }
                        case 2:             // edit block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            string car_details, set_value;    //variables for storing set and where conditions in query
                            cout << " Edit a car :\n\n";
                            cout << " Type the car details which you want to edit\n";
                            cout << " (For example: name='car_name')\n\n Enter details : ";
                            cin.ignore();
                            getline(cin, car_details);
                            cout << "\n Type the parameters and values you want to change in the car\n";
                            cout << " (For example: name='car_name',type='new_type',etc..)\n\n Enter details : ";
                            getline(cin, set_value);
                            Edit e;       //object of Edit class
                            sql = e.edit_car(set_value,car_details);        //getting query
                            setcolor(0x0a);
                            cout << "\n Car details updated successfully\n\n";
                            setcolor(0x07);
                            cout<<" Cars list after update are...\n";
                            goto execute_manage;
                            break;
                        }
                        case 3:                        // delete block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            string delete_condition;    // variable to store where condition in query
                            cout << " Enter the details of the car you want to delete\n";
                            cout << " (For example: name='car_name')\n\n Enter details : ";
                            cin.ignore();
                            getline(cin, delete_condition);
                            Delete d;     //object of Delete class
                            sql = d.delete_car(delete_condition);
                            setcolor(0x0a);
                            cout << "\n Car details deleted successfully\n\n";
                            setcolor(0x07);
                            cout<<" Cars list after deletion are...\n";
                            goto execute_manage;
                            break;
                        }
                        case 4:
                            goto back;      
                            break;
                        default:
                            break;
                        }
                    execute_manage:          // query execution block
                        {
                            work w(C);       
                            w.exec(sql);
                            w.commit();        // make chnages permanent in table
                            Search s;
                            sql = s.get_display_query();  //getting query
                            goto Display;
                        }
                    }
                    else { goto opinion_block; };
                Display:                  //query execution block
                        {
                        work w(C);
                        result r(w.exec(sql));
                        if (r.empty()) {         //empty funtion checks is the result container is empty
                            setcolor(0x0c);
                            cout << " SORRY No cars matching with your input details \n";   //statement if result is empty
                            setcolor(0x07);
                        }
                        else {
                            setcolor(0x0e);
                            VariadicTable<int, string, string, string, string > st({ "S.no", "Name", "Type", "Price(Lakhs)" ,"Date" }, 10);
                            for (result::const_iterator c = r.begin(); c != r.end(); c++)
                            {
                                st.addRow(i, c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>());
                                i++;
                            }
                            st.print(cout);
                            setcolor(0x07);
                            i = 1;
                            goto menu_block;
                        }
                        }
                    opinion_block: {     //opinion_block 
                        cout << "\n_______________________________________________________________________________________\n";
                        cout << "\n Do you want to continue(c) or logout(l)\n\n Enter your opinion(c/l) : ";
                        cin >> opinion; }                //get user opinion
                }
            }while (opinion == 'c');
        }
        setcolor(0x0a);
        cout << "\n_______________________________________________________________________________________\n";
        cout << "\n Logged out successfully\n";
        setcolor(0x07);
        cout << "_______________________________________________________________________________________\n";
        cout << "\n Do you want to login to other account(y/n) : ";
        char last_c;
        cin >> last_c;
        if (last_c == 'y') { cin.ignore(); goto login_block; }
        else{
            cout << "\n_______________________________________________________________________________________\n";
            setcolor(0x0a);
            cout<<"\n --- ...THANK YOU FOR USING OUR APP...--- \n";
            setcolor(0x07);
            cout << "_______________________________________________________________________________________\n";
        }
    }
    catch (const exception& e) {        //any errors or failure throws will be catched and displayed
            cerr << e.what() << std::endl;
    }
}