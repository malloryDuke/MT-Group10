#include <iostream>
#include "User.h"

using namespace std;
void inventorySelection();
void cartSelection();
void accountSelection(User* curUser);

int main()
{
	bool login = false;
	string input;
	int select;
	User* curUser = new User;
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
				cin >> input;
				select = stoi(input);

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
				cin >> select;
				switch(select){
					case 1: //Login
						//ask for username and password and checks user.csv for a match
						cout << "Enter Username: ";
						cin >> name;
						cout << "Enter Password: ";
						cin >> password;
						login = curUser->login(name, password);
						validSelection = true;
						if(login)
							cout << "\nLogin successful! ";
						else
							cout << "\nLogin Unsecessful Please try again\n";
						break;

					case 2: //Create Account
						//asks for user information and adds to user.csv
						cout << "Enter a Username: ";
						cin >> name;
						cout << "Enter a password: ";
						cin >> password;
						cout << "Enter your address: ";
						cin >> addr;
						cout << "Enter your payment information: ";
						cin >> payInfo;

						//Debugging nonsense
						cout << "Entered information: " << name << endl << password << endl << addr << endl << payInfo << endl;
						
						//create the account
						curUser->createUser(name,password,addr,payInfo); 
						login = true;
						validSelection = true;
						cout << "\nSuccessfully created account! ";
						break;
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

}

void accountSelection(User* curUser) {
	string input;
	int select;
	//Run until User selcts Go Back
	while(true){
		cout << "Enter your section\n"
			<< "1: View Order History\n2: Edit Shipping Information\n3: Edit Payment Informtion\n4: Delete Account\n5: Go Back\n";
		cin >>  input;
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
					cout << "Order #" << i <<": " << orderHistory[i] << endl;
				}
				break;
			case 2: //Edit Shippping Info
				cout << "Enter new Shipping Address: ";
				cin >> newAddr;
				curUser->editShippingInfo(newAddr);
				break;
			case 3: //Edit Payment Info
				cout << "Enter new Payment Information: ";
				cin >> newPay;
				curUser->editPayInfo(newPay);
				break;
			case 4: //Delete Account
				cout << "Are you sure? (Y/n)";
				cin >> deleteVerify;
				if(deleteVerify == "Y" || deleteVerify == "y"){
					cout << "Seg Fault \n";
					curUser->removeUser(curUser->username);
				}
				break;
			default:
				return;
		}
	}
	return;
}
