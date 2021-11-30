#include <iostream>
#include "Cart.h"
#include <stdlib.h>
#include <fstream>
#include "Book.h"
#include "User.h"

using namespace std;
void createCSVFiles();
void inventorySelection(Cart cart);
void cartSelection(Cart cart, User* curUser);
void accountSelection(User* curUser);

int main()
{
	bool login = false;
	string input;
	int select;
	User* curUser = new User;
	createCSVFiles();
	while (true)//loops until user exits
	{
		//checks boolean value to determine which menu to display
		if (login)
		{
			bool validSelection = false;
			Cart cart;
			while (!validSelection)
			{
				cout << "\nWhere would you like to go?\n\n";
				cout << "1. Inventory\n2. Shopping Cart\n3. Account\n4. Logout & Exit\n";
				getline(cin, input);
				select = stoi(input);

				if (select == 1)
				{
					//display available books in inventory.csv and allow user to add books to cart.csv
					validSelection = true;
					inventorySelection(cart);
				}
				else if (select == 2)
				{
					//display books in cart.csv and allows user to remove items or checkout
					validSelection = true;
					cartSelection(cart, curUser);
				}
				else if (select == 3)
				{
					//display new menu that makes changes to user's account
					validSelection = true;
					accountSelection(curUser);
				}
				else if (select == 4)
				{
					//logout and exit program
					curUser->logout();
					validSelection = true;
					return 0;
				}
				else
				{
					validSelection = false;
					cout << "\nInvalid selection. Please try again.\n";
				}
			}
		}
		else
		{
			bool validSelection = false;
			while (!validSelection)
			{
				cout << "Welcome to the book store! Please login to continue.\n\n";
				cout << "1. Login\n2. Create Account\n3. Exit\n";
				string name;
				string password;
				string addr;
				string payInfo;
				getline(cin, input);
				select = stoi(input);
				switch(select){
					case 1: //Login
						//ask for username and password and checks user.csv for a match
						cout << "Enter Username: ";
						getline(cin, name);
						cout << "Enter Password: ";
						getline(cin, password);
						login = curUser->login(name, password);
						validSelection = true;
						if(login)
							cout << "\nLogin successful! ";
						else
							cout << "\nLogin Unsecessful Please try again\n";
						break;

					case 2: //Create Account
					{
						//asks for user information and adds to user.csv
						cout << "Enter a Username: ";
						getline(cin, name);
						cout << "Enter a password: ";
						getline(cin, password);
						cout << "Enter your address: ";
						getline(cin, addr);
						cout << "Enter your card number: ";
						getline(cin, payInfo);

						
						
						//Debugging nonsense
						cout << "Entered information: " << name << endl << password << endl << addr << endl << payInfo << endl;
						
						//create the account
						curUser->createUser(name,password,addr,payInfo); 
						login = true;
						validSelection = true;
						cout << "\nSuccessfully created account! ";
						break;
					}
					case 3: //Exit
						//exit program
						validSelection = true;
						return 0;
					default:
						validSelection = false;
						cout << "\nInvalid selection. Please try again.\n\n";
				}
			}
		}
	}
}

void createCSVFiles() {
	// Source: https://www.geeksforgeeks.org/csv-file-management-using-c/
	fstream foutCart;
	fstream foutInventory;
	fstream foutUsers;
	fstream orderHistory; //Used to track order histories format should be username,order
	foutCart.open("cart.csv", ios::out | ios::app);
	foutInventory.open("inventory.csv", ios::out | ios::app);
	foutUsers.open("users.csv", ios::out | ios::app);
	/*
	foutCart << "1, 9780060194994, To Kill a Mockingbird, 2,\n";
	foutCart << "2, 5000029999992, Bible, 3,\n";

	foutUsers << "mallory duke malloryd, paSSw0rd, 1000 something lane Starkville MS 39759, 1010101010101010-10/11-999\n";

	foutInventory << "1, 9780060194994, Harper Lee, To Kill a Mockingbird, 4, $9.16,\n";
	*/
	foutCart.close();
	foutInventory.close();
	foutUsers.close();
}

void inventorySelection(Cart cart) {
	string selctIn;
	int newSelection;
	cout << "What would you like to do?\n\n";
	cout << "1. Add book to cart\n2. Go back to main menu\n";
	getline(cin,selctIn);
	newSelection = stoi(selctIn);
	if (newSelection == 1)
	{
		string book;
		cout << "What is the title of the book you would like to add to the cart?\n";
		std::getline(std::cin >> std::ws, book);
		string numIn;
		int num;
		cout << "How many of " + book + " would you like to add to your cart?\n";
		getline(cin, numIn);
		num = stoi(numIn);
		string message = cart.addItem(book, num);
		cout << message;
		// call instance of cart to add the book to it
	}
	else if (newSelection == 2) {
		//find a way to do the go back option
	}
	else {
		cout << "Invalid selection";
	}
}

void cartSelection(Cart cart,User* curUser) {
	string input;
	int newSelection;
	bool validSel = false;
	cout << "What would you like to do?\n\n";
	cout << "1. View items currently in cart\n2. Remove an item currently in cart\n3. Checkout\n4. Go back to main menu\n";
	getline(cin, input);
	newSelection = stoi(input);
	while (!validSel)
	{
		if (newSelection == 1)
		{
			string items = cart.viewCartItems();
			cout << "Your current items are:\n" << items << "\n";
			validSel = true;
		}
		else if (newSelection == 2) {
			string items = cart.viewCartItems();
			cout << "Your current items are:\n" << items << "\n";
			string name;
			cout << "What is the title of the book you wish to remove? ";
			getline(cin, name);
			cart.removeItem(name); //need to make the book class
			validSel = true;
		}
		else if (newSelection == 3)
		{
			string order;
			order = cart.checkout();
			curUser->addOrder(order);
			cout << "Your items have been checked out!\n";
			validSel = true;
		}
		else if (newSelection == 4) {
			cout << "Headed back to main menu!\n";
			validSel = true;
		}
		else {
			validSel = false;
			cout << "Invalid Selection - Try again!\n";
		}
	}
}

void accountSelection(User* curUser) {
	string input;
	int select;
	//Run until User selcts Go Back
	while(true){
		cout << "Enter your section\n"
			<< "1: View Order History\n2: Edit Shipping Information\n3: Edit Payment Informtion\n4: Delete Account\n5: Go Back\n";
		getline(cin, input);
		select = stoi(input);
		vector<string>  orderHistory;
		string newAddr;
		string newPay;
		string deleteVerify;
		switch (select)
		{
			case 1: //View Order History
				orderHistory = curUser->viewOrderHistory();
				for(int i = 0; i < orderHistory.size(); i++){
					cout <<  orderHistory[i] << endl;
				}
				break;
			case 2: //Edit Shippping Info
				cout << "Enter new Shipping Address: ";
				getline(cin, newAddr);
				curUser->editShippingInfo(newAddr);
				break;
			case 3: //Edit Payment Info
				cout << "Enter new Payment Information: ";
				getline(cin, newPay);
				curUser->editPayInfo(newPay);
				break;
			case 4: //Delete Account
				cout << "Are you sure? (Y/n)";
				getline(cin,deleteVerify);
				if(deleteVerify == "Y" || deleteVerify == "y"){
					curUser->removeUser(curUser->username);
				}
				break;
			default:
				return;
		}
	}
	return;
}
