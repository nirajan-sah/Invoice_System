#ifndef BILLITEM_H
#define BILLITEM_H

#include<iostream>	
#include<fstream>
#include<iomanip>

#include "Product.h"
using namespace std;


class BillItems {
    private:
        //declaring the product and quantitly private so only funcions can use this
        Product product;
        int quantity;
    public:
        void getItem() {
            ifstream prod;
            int code;  // To store user input product code
            bool found = false;
    
            while (true) {
                cout << "\n\tEnter the Product Code: "; //code for the product simply product number
                cin >> code;
    
                prod.open("Data/Products.txt", ios::in);
    
                if (!prod)//if the file Products.txt has not been created
                {
                    cout << "\n\tError: Unable to open Products file!";
                    return;
                }
    
                int pn;
                string pp;
                float pr;
    
                while (prod >> pn >> pp >> pr) {  // Read product data line by line
                    if (pn == code) {             // Match the code with the given code
                        product.setNumber(pn);
                        product.setName(pp);
                        product.setRate(pr);
                        found = true;
                        break;
                    }
                }
    
                prod.close();
    
                if (found) {
                    break; // Exit loop if product is found
                } else {
                    cout << "\n\tError: Product with code " << code << " not found!\n\tPlease try again.\n"; //else it will run this part of code again
                }
            }
        }
        void setQuantity(int x)	//user inputing the quantity of product
        {
            quantity = x;
        }	
        float getAmount()	//getting total amount by multiplying with the rate
        {
            float r;
            r = product.getRate();
            return r*quantity;
        }
        void printItemDet() //will print the detail of the product that already exists
        {
            cout
                //setw is a function that specify the minimum width for output
                << "\t" << setw(14) << product.getNumber()
                << "\t" << setw(12) << product.getName()
                << "\t" << setw(12) << product.getRate()
                << "\t" << setw(8) << quantity << "\t";
        }
        int getQuantity() { return quantity; }
        string getProductName() { return product.getName(); }
        float getProductRate() { return product.getRate(); }
        int getProductNumber() { return product.getNumber(); }
    };

#endif