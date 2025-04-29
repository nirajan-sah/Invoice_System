#include<iostream> 	//input and output
#include<string>	//string input
#include<iomanip>	//for setw function
#include<fstream>	//file handling
#include<ctime>		//for time and date


#include "Bill.h"

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
        outProduct.open("Products.txt", ios::out | ios::app);
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

            prod.open("Products.txt", ios::in);

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
        outInvoice.open("Invoices.txt", ios::out | ios::app); 		//writes to the file
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

//This class is for authorization of admin_authorization
class Admin {
protected:
	//reason to use static is so that it not not accessible by other source rather that static in this case it is static void admin()
    static void addAdminUser() {
        string newUsername, newPassword, confirmPassword;

        cout << "\n\n\tEnter New Admin Username: "; 			//new username to register
        cin >> newUsername;

        cout << "\n\n\tEnter New Admin Password: ";				//password of that username
        char ch;
        while ((ch = cin.get()) != '\r') 							//will continue to read the char until the enter key is pressed
		{ 
            if (ch == '\b' && !newPassword.empty()) {			//if backspace is pressed then this loop will check if there is char in the newpassword
                newPassword.pop_back();							//pop_back will delete the last character
                cout << "\b \b";								//will delete the last char replace with space and again delete
            } else if (ch != '\b') {							
                newPassword += ch;								//if no backspace it will continue to write password to newPassword
                cout << '*';									//if a character is enter I will output * rather than actual password
            }
        }

		//using same algorithm as before
        cout << "\n\n\tConfirm Password: ";			
        while ((ch = cin.get()) != '\r') {
            if (ch == '\b' && !confirmPassword.empty()) {
                confirmPassword.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                confirmPassword += ch;
                cout << '*';
            }
        }

		//confirm if the password matches the enteres password else returns to wirte again
        if (newPassword != confirmPassword) {
            cout << "\n\n\tError: Passwords do not match. Admin user not added.";
            cout << "\n\tPress any key to continue...";
            cin.get();
            return;
        }

		//store the password in the file admindatabase.txt
        ofstream adminData("admindatabase.txt", ios::app);
        if (!adminData) {
            cerr << "\n\n\tError: Unable to access admindatabase file.";	//if file doesn't exist or unable to create it
            cout << "\n\tPress any key to continue...";
            cin.get();
            return;
        }

        adminData << newUsername << ' ' << newPassword << '\n';					//write it to the file
        adminData.close();

        cout << "\n\n\tNew Admin User Added Successfully!";
        cout << "\n\tPress any key to continue...";
        cin.get();
    }

	//static bool is entered because we only expect output of true or false from this.
    static bool authorizeAdmin() {
        const string defaultAdminUsername = "admin"; // Default admin username
        const string defaultAdminPassword = "1234"; // Default admin password

        string enteredUsername, enteredPassword;
        char ch;

        cout << "\n\n\tEnter Admin Username: ";
        cin >> enteredUsername;
        cout << "\n\tEnter Admin Password: ";
        enteredPassword = "";

        // Hide password input
        while ((ch = cin.get()) != '\r') { // Enter key ends input
            if (ch == '\b' && !enteredPassword.empty()) {
                enteredPassword.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                enteredPassword += ch;
                cout << '*';
            }
        }

        // Check default login first
        if (enteredUsername == defaultAdminUsername && enteredPassword == defaultAdminPassword) {
            cout << "\n\tDefault Admin Login Successful!";
            return true;
        }

        // Check stored login detail in admindatabase.txt
        ifstream adminFile("admindatabase.txt");
        string fileUsername, filePassword;
        while (adminFile >> fileUsername >> filePassword) {
            if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                cout << "\n\tAdmin Login Successful!";
                adminFile.close();
                return true;
            }
        }

        adminFile.close();
        cout << "\n\tLogin Failed! Invalid Username or Password.";
        return false;
    }
};

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
        cin.get();

        fBill.storeInvoice();	//will store the data to Invoices.txt
    }

	//for admin purpose, enables to access program fully
	static void admin()
	{
		if(!authorizeAdmin())	//only valide username and password will let to enter the admin portal
		{
			cout<<"\n\n\tReturing to the main menu....\n";
			cin.get();
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
			cin.get();
			}
		}
	}
	
	//If the product number already exists and new product with same number is being created with user it won't allow it
	static bool isUniqueNumber(int number) 
	{
    ifstream inProduct("Products.txt");
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
		ifstream displayProducts;						//open the file in read
		displayProducts.open("Products.txt", ios::in);
		int n;
		string p;
		float r;
		cout << "\n\n\tDISPLAY ALL PRODUCTS"<<"\n\t=================================================================";
		while (1)
		{
			displayProducts >> n;
			if (displayProducts.eof())				//check end of the file is reached or not
				break;
			displayProducts >> p >> r;
			//displaying on screen
			cout << "\n\tPRODUCT NUMBER : " << n;
			cout << "\n\tPRODUCT NAME : " << p;
			cout << "\n\tRATE OF PRODUCT : " << r;
			cout << "\n\t=================================================================";
		}
		cout<<"\n\tPress any key";
		cin.get();
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
		prodIn.open("Products.txt", ios::in);	//opens in read
		prodTmp.open("temp.txt", ios::out);		//opens in write
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
		remove("Products.txt");					//delets the file
		rename("temp.txt", "Products.txt");		//renames the file
		cout << "\n\n\n\tPRODUCT RATE UPDATED SUCCESSFULLY";
		cin.get();
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
		prodIn.open("Products.txt", ios::in);	//open in read
		prodTmp.open("temp.txt", ios::out);		//open in write
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
		remove("Products.txt");					//removes the file
		rename("temp.txt", "Products.txt");		//renames the file
		cout << "\n\n\n\tPRODUCT DELETED SUCCESSFULLY";
		cin.get();
	}

	static void displayInvoices() {
        system("clear");
        ifstream inInvoice;
        inInvoice.open("Invoices.txt", ios::in);	//open in read
        if (!inInvoice) {							//if file is not created or found
            cout << "\n\n\tNO INVOICES FOUND!";
            cout << "\n\tPress any key";
            cin.get();
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
        cin.get();
    }	
};

int main()
{
	system("clear");//function for clearing the screen in visual studio
	while (1)
	{
		NavPages::user();
	}
    return 0;
}