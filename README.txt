Requirements:
1. VS-Code
2. Compiler

TO RUN THE PROGRAM: 
Open the source code in vs-code: ctrl + Alt + N


					****************************************************
					#The UI of the invoice system: (How does this work)#
					****************************************************

							Main Menu
							1. Customer
							2. Administrator
							3. Exit


						If you are a customer type: 1
						*****************************

							1. Customer
1. You will be asked to choose to enter the invoice or go back to the main menu.
1.1 It will ask for the number of items you want to add to the invoice.
1.2. It will display all the items with details in the store.
	1.2.1. click any key to start adding the items.
	1.2.2. Now, it will ask for the Item code i.e. the Product Number and the quantity of the item you want to add to the invoice.
1.3. The program will automatically exit if the number of items matches the user given.
1.4. The invoice will be displayed at last and you can click any key to continue (i.e. go back in the program)

	


						If you are an Admin or an Employee type: 2
						******************************************

							2. Administrator

##If you are a new user:
  Default Username: admin
  Default Password: 1234

##The Created product will be added to the products.txt:
  Following the pattern of:: Product Number' 'Product Name ' ' product rate

##All the History of invoices will be added to the file Invoices.txt.

##The new admin username and password will be added to the file admindatabase.txt.

						**********************************************
						#THE UI OF THE ADMINISTRATOR AND ITS FUNCTION#	
						**********************************************
		
1. Create Product == It helps to add a new product to the store.

2. Display All Products == It helps display all the store products.

3. Modify Product == It helps to set the new rate for the product.

4. Delete Product == As the name suggests, It deletes the product in the store saying the soap has been sold out so it deletes the entire data of the soap including rate and product number.

5. Display History of invoice == It will display all the invoices with their respective date and time. (All the invoices the customer has created will 	be added to the file Invoice.txt and displayed when this function is initialized.)

6. Add new admin == It creates a new username and new password and stores it in a file.

7.Back to Main menu == Will navigate to the main menu. (Start of the program.)

**If you have completed your activity with the program then to exit type: (3) in the main menu