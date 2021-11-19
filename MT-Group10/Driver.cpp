#include <iostream>

using namespace std;

int main()
{
	bool login = false;
	int select;
	while (true)//loops until user exits
	{
		//checks boolean value to determine which menu to display
		if (login)
		{
			cout << "\nWhere would you like to go?\n\n";
			cout << "1. Inventory\n2. Shopping Cart\n3. Account\n4. Logout & Exit\n";
			cin >> select;

			if (select == 1)
			{
				//display available books and allow user to add books to cart
			}
			else if (select == 2)
			{
				//display books in user's cart and allows user to remove items or checkout
			}
			else if (select == 3)
			{
				//display new menu that makes changes to user's account
			}
			else if (select == 4)
			{
				//logout and exit program
				return 0;
			}
			else
			{
				cout << "\nInvalid selection. Please try again.\n";
			}
		}
		else
		{
			cout << "Welcome to the book store! Please login to continue.\n\n";
			cout << "1. Login\n2. Create Account\n3. Exit\n";
			cin >> select;

			if (select == 1)
			{
				//ask for username and password and checks user.csv for a match
				login = true;
				cout << "\nLogin successful! ";
			}

			else if (select == 2)
			{
				//asks for user information and adds to user.csv
				login = true;
				cout << "\nSuccessfully created account! ";
			}

			else if (select == 3)
			{
				//exit program
				return 0;
			}

			else
			{
				cout << "\nInvalid selection. Please try again.\n\n";
			}
		}
	}
}