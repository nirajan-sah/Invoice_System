#ifndef NAV_H
#define NAV_H

#include<iostream> 	
#include<iomanip>
#include<fstream>	


#include "Bill.h"
#include "Product.h"
#include "Bill-Items.h"
#include "Invoice.h"
#include "Admin.h"
using namespace std;
//This is where the real program begins
class NavPages : public Admin{
    public:
    //Its the main menu that navigates the customer and admin to respective Side of program
        static void user()
        {
            int ch;
            system("clear");
            cout << "\n\n\n\t\t\t\t\t\t\tNIRAJAN'S STORE"<<endl;
            cout << "\t\t\t\t================================================================\n";
            cout << "\n\n\t\t\t\t\t\t\t*************";
            cout << "\n\t\t\t\t\t\t\t# MAIN MENU #";
            cout << "\n\t\t\t\t\t\t\t*************";
            cout << "\n\n\t\t\t1. CUSTOMER";
            cout << "\n\n\t\t\t2. ADMINISTRATOR";
            cout << "\n\n\t\t\t3. EXIT";
            cout << "\n\n\n\n\t\t\tPlease Select Your Option (1-3) ";
            cin >> ch;
            switch (ch)
            {
            case 1: customer(); break; 	// goes to customer function
            case 2: admin(); break;	   	//goes to admin function
            case 3: exit(0);			//exits the program
            }
        }
        
        static void customer()
        {
            int n,c;
            string name;
            BillItems item[20];
            int code;
            int qty;
            Invoice fBill;	//calling variable for class Invoice
            system("clear");
            cout<<"\n\n\t1.Go Back to Main Menu.";
            cout<<"\n\n\t2.Continue to Invoice...\n";
            cout<<"\n\n\tChoose: ";
            cin>>c;
            switch(c)
            {
                case 1: return;	//It will return to main menu
                case 2: break;	//It will navigate to next phase
                default: cout<<"\n Invalid option. Please Try again.\n"; return;
            }
    
            cin.ignore();//clear newline character form input buffer
    
            cout<<"\n\n\tENTER YOUR NAME: ";
            getline(cin, name);
            cout << "\n\n\tENTER THE NUMBER OF ITEMS:";
            cin >> n;
    
            displayProduct();//display all products
            fBill.numOfItems = n;
            fBill.customerName = name;
            for (int i = 0; i < n; i++) 
            {
                cout << "\nAdding Item " << (i + 1) << ":";
                item[i].getItem();
                
                while(true)										//will only work when the Item number exists.
                {
                    cout<<"\n\tEnter the quantity: ";
                    cin>>qty;	
                    break;
                }
                item[i].setQuantity(qty);
                fBill.item[i] = item[i];
                fBill.totalAmount += item[i].getAmount();
            }
    
            //To print the Invoice of the customer
            system("clear");
            cout<<"\n\tCustomer Name: "<<fBill.customerName<<"\n";
            cout << "\n\n\tINVOICE \t\t\tDate/Time: " << fBill.date << endl;
            cout << "\t======================================================================================" << endl;
            cout << "\tProduct Number\tProduct Name\tProduct Rate\tQuantity\tAmount" << endl;
    
            for (int i = 0; i < n; i++) {
                item[i].printItemDet();
                cout << setw(6) << item[i].getAmount() << endl;
            }
    
            cout << "\n\n\t\t\t\tTOTAL AMOUNT: " << fBill.totalAmount;
            cout << "\n\tThank You for Shopping" << endl;
            cout << "\n\tPress any key to continue...";
            cin.ignore();
    
            fBill.storeInvoice();	//will store the data to Invoices.txt
        }
    
        //for admin purpose, enables to access program fully
        static void admin()
        {
            if(!authorizeAdmin())	//only valide username and password will let to enter the admin portal
            {
                cout<<"\n\n\tReturing to the main menu....\n";
                cin.ignore();
                return;
            }
            while (1)
            {
                system("clear");
                int ch;
                cout << "\n\n\n\tADMIN MENU";
                cout << "\n\n\t1.CREATE PRODUCT";
                cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
                cout << "\n\n\t3.MODIFY PRODUCT";
                cout << "\n\n\t4.DELETE PRODUCT";
                cout << "\n\n\t5.DISPLAY HISTORY OF INVOICE";
                cout << "\n\n\t6.REGISTER ADMIN USER";
                cout << "\n\n\t7.BACK TO MAIN MENU";
                cout << "\n\n\tPlease Enter Your Choice (1-7) ";
                cin >> ch;
                switch (ch)
                {
                case 1: createProduct(); break;
                case 2: displayProduct(); break;
                case 3: modifyProduct(); break;
                case 4: deleteProduct(); break;
                case 5: displayInvoices(); break;
                case 6: addAdminUser(); break;
                case 7: return;
                default: cout<<"\n\tInvalid choice. Try again. "; 
                cin.ignore();
                }
            }
        }
        
        //If the product number already exists and new product with same number is being created with user it won't allow it
        static bool isUniqueNumber(int number) 
        {
        ifstream inProduct("Data/Products.txt");
            if (inProduct.is_open()) {
                string line;
                while (getline(inProduct, line)) 
                {
                    stringstream ss(line);
                    int num;
                    ss >> num;
                    if (num == number) {		//checks the given number to the number in Products.txt
                        inProduct.close();
                        return false;			//false if number is not unique
                    }
                }
                inProduct.close();
            }
            return true;
        }
    
        static void createProduct()
        {
            system("clear");
            int n;
            string p;
            float r;
            cout << "\n\n\tENTER THE DETAILS OF THE PRODUCT" << endl;
            cout << "\n\tENTER THE PRODUCT NUMBER" << endl;
            do{cin >> n;}while(n < 0);									//will only take positive number
    
            while (!isUniqueNumber(n)) 									//will check and if number already exist then !--inverts the fasle to true and the loops continue
            {
            cout << "\n\tError: Product number already exists.\n\tENTER A UNIQUE PRODUCT NUMBER: ";
            cin >> n;
            }
            cout << "\n\tENTER THE PRODUCT NAME" << endl;
            cin >> p;
            cout << "\n\tENTER THE PRODUCT RATE" << endl;
            do{cin >> r;}while(r < 0);									//will only take positve number
            Product prod(n,p,r);										//will save the data to Products.txt through the constructor Product
        }
        
        //simply displays all the product
        static void displayProduct()
        {
            system("clear");
            ifstream displayProducts;					
            displayProducts.open("Data/Products.txt", ios::in);
            int n;
            string p;
            float r;
            cout << "\n\n\tDISPLAY ALL PRODUCTS"<<"\n\t=================================================================";
            while (1)
            {
                displayProducts >> n;
                if (displayProducts.eof())
                    break;
                displayProducts >> p >> r;
                //displaying on screen
                cout << "\n\tPRODUCT NUMBER : " << n;
                cout << "\n\tPRODUCT NAME : " << p;
                cout << "\n\tRATE OF PRODUCT : " << r;
                cout << "\n\t=================================================================";
            }
            cout<<"\n\tPress any key";
            cin.ignore();
        }
        
        static void modifyProduct()
        {
            system("clear");
            displayProduct();		//first display all products for the users to select the product
            ifstream prodIn;
            ofstream prodTmp;
            cout << "\n\t*****************************************************************";
            cout << "\n\tEnter the Product Number to Modify: ";
            int modNum;
            cin >> modNum;
            prodIn.open("Data/Products.txt", ios::in);	//opens in read
            prodTmp.open("Data/temp.txt", ios::out);		//opens in write
            int n;
            string p;
            float r;
            while (1)
            {
                prodIn >> n;
                if (prodIn.eof())
                    break;
                prodIn >> p >> r;
                if (n == modNum)					//if matches them modify the rate else copy same
                {
                    cout << "\n\tEnter new rate:";
                    cin >> r;
                }	
                prodTmp
                    << n << ' ' << p << ' ' << r << endl;
            }
            prodIn.close();
            prodTmp.close();
            remove("Data/Products.txt");					//delets the file
            rename("Data/temp.txt", "Data/Products.txt");		//renames the file
            cout << "\n\n\n\tPRODUCT RATE UPDATED SUCCESSFULLY";
            cin.ignore();
        }
    
        //Function to delete products
        static void deleteProduct()
        {
            system("clear");
            displayProduct();//first display all products for the users to select the product
            ifstream prodIn;
            ofstream prodTmp;
            cout << "\n\t*****************************************************************";
            cout << "\n\tEnter the Product Number to Delete: ";
            int modNum;
            cin >> modNum;
            prodIn.open("Data/Products.txt", ios::in);	//open in read
            prodTmp.open("Data/temp.txt", ios::out);		//open in write
            int n;
            string p;
            float r;
            while (1)
            {
                prodIn >> n;
                if (prodIn.eof())
                    break;
                prodIn >> p >> r;
                if (n != modNum)					//If not equal them write same
                {
                    prodTmp
                        << n << ' ' << p << ' ' << r << endl;
                }
            }
            prodIn.close();
            prodTmp.close();
            remove("Data/Products.txt");					//removes the file
            rename("Data/temp.txt", "Data/Products.txt");		//renames the file
            cout << "\n\n\n\tPRODUCT DELETED SUCCESSFULLY";
            cin.ignore();
        }
    
        static void displayInvoices() {
            system("clear");
            ifstream inInvoice;
            inInvoice.open("Data/Invoices.txt", ios::in);	//open in read
            if (!inInvoice) {							//if file is not created or found
                cout << "\n\n\tNO INVOICES FOUND!";
                cout << "\n\tPress any key";
                cin.ignore();
                return;
            }
    
            string line;
            cout << "\n\n\tDISPLAY ALL INVOICES" << "\n\t=================================================================\n";
            while (getline(inInvoice, line)) //will read every line of invoice and print it
            {
                cout << line << endl;
            }
            inInvoice.close();
            cout << "\n\tPress any key";
            cin.ignore();
        }	
    };

#endif