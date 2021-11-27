#include <iostream>

using namespace std;
void inventorySelection();
void cartSelection();
void accountSelection();

int main()
{
	bool login = false;
	int select;
	while (true)//loops until user exits
	{
		//checks boolean value to determine which menu to display
		if (login)
		{
			bool validSelection = false;
			while (!validSelection)
			{
				cout << "\nWhere would you like to go?\n\n";
				cout << "1. Inventory\n2. Shopping Cart\n3. Account\n4. Logout & Exit\n";
				cin >> select;

				if (select == 1)
				{
					//display available books in inventory.csv and allow user to add books to cart.csv
					validSelection = true;
					inventorySelection();
				}
				else if (select == 2)
				{
					//display books in cart.csv and allows user to remove items or checkout
					validSelection = true;
					cartSelection();
				}
				else if (select == 3)
				{
					//display new menu that makes changes to user's account
					validSelection = true;
					accountSelection();
				}
				else if (select == 4)
				{
					//logout and exit program
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

void inventorySelection() {
	int newSelection;
	cout << "What would you like to do?\n\n";
	cout << "1. Add book to cart\n2. Go back to main menu\n";
	cin >> newSelection;
	if (newSelection == 1)
	{
		string book;
		cout << "What is the title of the book you would like to add to the cart?\n";
		cin >> book;
		// call instance of cart to add the book to it
	}
	else if (newSelection == 2) {
		//find a way to do the go back option
	}
	else {
		cout << "Invalid selection";
	}
}

void cartSelection() {
	int newSelection;
	cout << "What would you like to do?\n\n";

}

void accountSelection() {

}
