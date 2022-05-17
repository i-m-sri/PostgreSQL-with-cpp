#include <iostream>     
#include"Opening_page.h"  
#include"textcolor.h"
#include"Postgresql.h"

using namespace std;    

int main()
{
    char choice;
        setcolor(0x0e);
        cout << "\n                 SRIRAM RENTERS LTD\n                 ------------------\n";
        cout << "     3WHR+3R9, MTP Road, Thudiyalur, Coimbatore-641034\n";
        cout << "      Ph.no: 063800 38432, Mail:Srirenters@gmail.com\n";
        setcolor(0x07);
        cout << "_______________________________________________________________________________________\n\n";
        setcolor(0x0a);
        cout << " -----> WELCOME TO RENTO GARAGE <-----\n";
        setcolor(0x07);
        cout << "_______________________________________________________________________________________\n\n";
        execute("select carid,name from cars where return_time=current_date-1;", 4);
    do
    {
        Open_app app;
        cout << " Do you want to continue with our app(y/n)?: ";
        cin >> choice;
        cout << "_______________________________________________________________________________________\n\n";
        cout << "\n";
    } while (choice == 'y');
    setcolor(0x0a);
    cout << "\n ---> THANKS FOR USING OUR APP HAVE A NICE DAY <---\n";
    setcolor(0x07);
}