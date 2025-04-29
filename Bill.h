#ifndef BILL_H
#define BILL_H

#include<iostream>	
#include<ctime>

using namespace std;

class Bill {
    public:
        string date;		//To store the date and time of the invoice
        float totalAmount;	
        string customerName;
    public:
        virtual void storeInvoice()
        {
            cout<<"No Inovice";
        }
        //Default constructor : Initialized the date with current time and amount
        Bill()
        {
            // current date/time on current system
            time_t now = time(0);
    
            // convert now to string form
            char* dt = ctime(&now);
    
            //assign date to 'date' attribute
            date = dt;
            //by default total amount is 0
            totalAmount = 0;
    
        }
    };

#endif