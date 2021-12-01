#include <iostream>
#include "Cart.h"
#include <stdlib.h>
#include <fstream>
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
				cin >> select;

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
				cin >> select;
				string name;
				string password;
				string addr;
				string payInfo;
				if (select == 1)
				{
					//ask for username and password and checks user.csv for a match
					login = true;
					validSelection = true;
					cout << "\nLogin successful! ";
				}

				else if (select == 2)
				{
					//asks for user information and adds to user.csv
					login = true;
					validSelection = true;
					cout << "\nSuccessfully created account! ";
				}

				else if (select == 3)
				{
					//exit program
					validSelection = true;
					return 0;
				}
				else
				{
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
	foutCart.open("cart.csv", ios::out | ios::app);
	foutInventory.open("inventory.csv", ios::out | ios::app);
	foutUsers.open("users.csv", ios::out | ios::app);

	//foutCart << "1, 9780060194994, To Kill a Mockingbird, 2,\n";
	//foutCart << "2, 5000029999992, Bible, 3,\n";

	foutUsers << "1, mallory, duke, malloryd, paSSw0rd, 1010101010101010-10/11-999, 1000 something lane Starkville MS 39759, no orders,\n";

	foutInventory << "1, 9780060194994, Harper Lee, To Kill a Mockingbird, 4, $9.16,\n";

	foutCart.close();
	foutInventory.close();
	foutUsers.close();
}

void inventorySelection(Cart cart) {
	int newSelection;
	cout << "What would you like to do?\n\n";
	cout << "1. Add book to cart\n2. Go back to main menu\n";
	cin >> newSelection;
	if (newSelection == 1)
	{
		// Display contents of inventory.csv
		string book;
		cout << "What is the title of the book you would like to add to the cart?\n";
		std::getline(std::cin >> std::ws, book);
		int num;
		cout << "How many of " + book + " would you like to add to your cart?\n";
		cin >> num;
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

void cartSelection(Cart cart, User* curUser) {
	int newSelection;
	bool validSel = false;
	cout << "What would you like to do?\n\n";
	cout << "1. View items currently in cart\n2. Remove an item currently in cart\n3. Checkout\n4. Go back to main menu\n";
	cin >> newSelection;
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
			cout << "What is the title of the book you wish to remove?\n";
			std::getline(std::cin >> std::ws, name);
			string message = cart.removeItem(name); 
			cout << message;
			validSel = true;
		}
		else if (newSelection == 3)
		{
			string message = cart.checkout();
			//curUser->addOrder(message);
			cout << message;
			validSel = true;
			fstream fin;
			fin.open("cart.csv", std::ofstream::out | std::ofstream::trunc);
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

void accountSelection(User *curUser) {

}