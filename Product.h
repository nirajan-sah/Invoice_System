#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>	
#include<fstream>

using namespace std;

class Product {
    private:
        int productNumber;      // Unique ID for the product
        string productName;     // Name of the product
        float productRate;      // price of the product
    
    public:
        // Default constructor: Initializes the product attributes to default values
        Product() : productNumber(0), productName(""), productRate(0.0) {}
    
        // Parameterized constructor to write details to file 
        Product(int pNum, string pNam, float rate) : productNumber(pNum), productName(pNam), productRate(rate) {
            ofstream outProduct;
            outProduct.open("Data/Products.txt", ios::out | ios::app);
            outProduct << productNumber << ' ' << productName << ' ' << productRate << endl;
            cout << "\n\n\n\tPRODUCT CREATED SUCCESSFULLY";
            cin.get();
        }
    
        // Getter for product number, name, rate (access the value)
        int getNumber() { return productNumber; }
        string getName() { return productName; }
        float getRate() { return productRate; }
    
        // Setter for product number, name, rate (update or set the value)
        void setNumber(int x) { productNumber = x; }
        void setName(string x) { productName = x; }
        void setRate(float x) { productRate = x; }
    };

#endif