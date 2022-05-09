#include <iostream>     //header file for input output streams
#include <pqxx/pqxx>    //API for postgreSQL cpp interface
#include <string>      //string headerfile
#include <iomanip>     /*library for manipulating the output format in this 
                        project it is used to display the output in table format*/

using namespace std;    
using namespace pqxx;    // using the namesapce pqxx

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
            cout << "Opened database successfully: " << C.dbname() << endl;
        }       
        else {
            cout << "Can't open database" << endl;
            return 1;
        }
        string username, password, sql;         //string objects for login data's and query
        int flag=0;                             // flag variable for checking the existence of the user
        cout << "\n"<<" <-----.....WELCOME TO OUR CAR RENTAL APP.....----->\n\n";
        login_block:                            //login_block label containg login block of code
        {
            cout << " LOGIN\n -----\n";
            cout << " Enter the username : ";
            getline(cin, username);            //getting username 
            sql = "select * from users";       //query for selection with table name
            work w(C);                         //work class is used to make transactional operations in table
            result r(w.exec(sql));            /* result class is a container to store the executed result 
                                              of the query in tuples format */
            for (result::const_iterator c = r.begin(); c != r.end(); c++)  /* setting a constant iteratorand iterating 
                                                                           through the result container 
                                                                           until it reaches the end */
            {
                if (c[0].as<string>() == username) {        //check if the user given name matches with our username
                    flag = 1;                               //setting flag to 1 if user exist's
                    password_block:                         //password block to execute password entry operations
                    {
                        cout << " Enter the password : ";
                        cin >> password;                     //getting password from user
                        if (c[i].as<string>() == password) {     //check whether the password matches
                            cout << "\n" <<" Logged in Successfully WELCOME " << username << "\n\n";
                            goto menu_block;      
                            break;
                        }
                        else {
                            cout << "\n"<<" OOPS the password is wrong enter the correct password : \n\n";
                            goto password_block;
                        }
                    }
                }
            }
            if (flag == 0)            //if username mismatches login_block is repeated
            {
                cout << "\n"<<" Username " << username << " does not exit please enter the correct username...!!!\n\n";
                goto login_block;
            }
        }
        menu_block:                      //block of code for performing menu operations
        {
            int menu_option;             // menu_option for selecting the menu options and se
            string opinion;              // opinon variable for storing the opinion of the user
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
                        int search_by;             //variable to store search by option
                        cout << "\n_______________________________________________________________________________________\n";
                        nontransaction w(C);          //nontransaction class to perform nontransactionakl operations in table
                        sql = "select * from cars;"; 
                        result r(w.exec(sql));         
                        cout << "\n Cars available in our app are : \n";
                        cout << " -----------------------------------\n";
                        cout << ' ' << left << setw(6) << "S.no" << left << setw(20) << "Name" << left << setw(15) << "Type"
                            << left << setw(15) << "Price" << left << setw(15) << "Date" << "\n\n";
                             /*printing the column names in arranged manner using setw() method available
                             in iomanip library */
                        for (result::const_iterator c = r.begin(); c != r.end(); c++)
                        {
                            cout << ' ' << left << setw(6) << i << left << setw(20) << c[0].as<string>()
                                << left << setw(15) << c[1].as<string>() << left << setw(15) << c[2].as<string>()
                                << left << setw(15) << c[3].as<string>() << "\n";
                                                      // Display the output in column separted with unform spaces 
                            i++;           // increment the i in order to increment the s.no for next iter
                        }
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
                            sql = "select * from cars where price between " + minimum_price + " and " + maximum_price + ";"; 
                                      // query for displaying the cars with price range
                            cout << "\n Search result for your price range.....!!!\n\n";  // display block result
                            goto execute_search;        // jumping to execution block of query
                            break;
                        }
                        case 2:            //search by date block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            cout << " Search by Date\n --------------------\n";
                            sql = "select date from cars";
                            string date, staring_date, ending_date;   //variables for start and end date
                            cout << " Enter the staring date(yyyy-mm-dd) : ";
                            cin >> staring_date;
                            cout << " Enter the ending date(yyyy-mm-dd) : ";
                            cin >> ending_date;
                            sql = "select * from cars where date>='" + staring_date + "' and date<='" + ending_date + "';";
                            cout << "\n Search result for your date range.....!!!\n\n";
                            goto execute_search;
                            break;
                        }
                        case 3:               // search by type block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            cout << " Search by car type\n ----------------------\n";
                            string type;        // variable to store the type input given by user
                            cout << " Enter the type of car you are looking for : ";
                            cin >> type;
                            sql = "select * from cars where type='" + type + "';";
                            cout << "\n Search result for your car type......!!!\n\n";
                            goto execute_search;
                            break;
                        }
                        case 4:             
                            goto back;
                            break;
                        default:
                            break;
                        }

                    execute_search:                  //query execution block
                        {
                            result r(w.exec(sql));
                            if (r.empty()) {         //empty funtion checks is the result container is empty
                                cout << " SORRY No cars matching with your input details \n";
                            }
                            else {
                                cout << ' ' << left << setw(6) << "S.no" << left << setw(20) << "Name" << left << setw(15) << "Type"
                                    << left << setw(15) << "Price" << left << setw(15) << "Date" << "\n\n";
                                for (result::const_iterator c = r.begin(); c != r.end(); c++)
                                {
                                    cout << ' ' << left << setw(6) << i << left << setw(20) << c[0].as<string>()
                                        << left << setw(15) << c[1].as<string>() << left << setw(15) << c[2].as<string>()
                                        << left << setw(15) << c[3].as<string>() << "\n";
                                    i++;
                                }
                                i = 1;
                            }
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
                            cout << " Enter the price of the car : ";
                            getline(cin, price);
                            cout << " Enter the launch date : ";
                            getline(cin, date);
                            sql = "insert into cars values('" + name + "','" + type + "'," + price + ",'" + date + "');";
                            cout << "\n New car Added successfully\n";
                            goto execute_manage;;
                            break;
                        }
                        case 2:             // edit block
                        {
                            cout << "_______________________________________________________________________________________\n\n";
                            string car_detail, set_value;    //variables for storing set and where conditions in query
                            cout << " Edit a car :\n\n";
                            cout << " Type the car details which you want to edit\n";
                            cout << " (For example: name='car_name')\n\n Enter details : ";
                            cin.ignore();
                            getline(cin, car_detail);
                            cout << "\n Type the parameters and values you want to change in the car\n";
                            cout << " (For example: name='car_name',type='new_type',etc..)\n\n Enter details :";
                            getline(cin, set_value);
                            sql = "update cars set " + set_value + " where " + car_detail + ";";
                            cout << "\n Car details updated successfully\n";
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
                            sql = "delete from cars where " + delete_condition + ";";
                            cout << "\n Car details deleted successfully\n";
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
                        }
                    }
                    cout << "\n_______________________________________________________________________________________\n";
                    cout << "\n Do you want to continue or logout\n\n Enter your opinion(continue/logout) : ";
                    cin >> opinion;                 //get user opinion
                }
            }while (opinion == "continue");
        }
        cout << "\n Logged out successfully\n\n---...THANK YOU FOR USING OUR APP...---\n";
    }
    catch (const exception& e) {        //any errors or failure throws will be catched and displayed
            cerr << e.what() << std::endl;
    }
}
