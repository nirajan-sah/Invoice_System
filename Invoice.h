#ifndef INVOICE_H
#define INVOICE_H

#include<iostream>	
#include<fstream>
#include<iomanip>

using namespace std;

//Invoice is a derived class of Bill
class Invoice : public Bill{
    public:
        int numOfItems;
        string customerName;
        BillItems item[50];
    
        void storeInvoice() override
        {
            //This will store the generated Invoice to the file Invoices.txt
            ofstream outInvoice;
            outInvoice.open("Data/Invoices.txt", ios::out | ios::app); 		//writes to the file
            outInvoice <<"\n\n\tCustomer Name: "<<customerName<<"\n";
            outInvoice << "\n\n\tINVOICE \t\t\tDate/Time: " << date << endl;
            outInvoice << "\t======================================================================================" << endl;
            outInvoice << "\tProduct Number\tProduct Name\tProduct Rate\tQuantity\tAmount" << endl;
    
            for (int i = 0; i < numOfItems; i++) {
                outInvoice << "\t" << setw(14) << item[i].getProductNumber()
                           << "\t" << setw(12) << item[i].getProductName()
                           << "\t" << setw(12) << item[i].getProductRate()
                           << "\t" << setw(8) << item[i].getQuantity()
                           << "\t" << setw(6) << item[i].getAmount() << endl;
            }
    
            outInvoice << "\n\n\t\t\t\tTOTAL AMOUNT: " << totalAmount << endl;
            outInvoice.close();		//will close the file when done
        }
    };
    

#endif