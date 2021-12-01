#include "Cart.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

Cart::Cart() {
	book = "";
	num = 0;
}

string Cart::addItem(string book, int num) {
	fstream fInventory;
	fInventory.open("inventory.csv", ios::in);
	fstream finCart, foutCart;
	finCart.open("cart.csv", ios::in);
	foutCart.open("cart.csv", ios::out | ios::app);
	string line;
	vector<string> row;
	string items = "";
	string temp;
	int count = 1;
	string message = "Book added to cart!";
	string isbn;
	bool add = false;
	while (fInventory >> temp) {
		row.clear();
		getline(fInventory, line);
		stringstream ss(line);
		string word;
		char split = ',';
		while (getline(ss, word, split))
		{
			row.push_back(word);
		}
		// source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
		string whitespace = " \t";
		const auto strBegin = row[2].find_first_not_of(whitespace);

		const auto strEnd = row[2].find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;
		string title = row[2].substr(strBegin, strRange);

		if (book == title)
		{
			isbn = row[0];
			string inStock = row[3];
			bool canAdd = num <= std::stoi(inStock);
			if (!canAdd)
			{
				message = "We do not have " + std::to_string(num) + " of the book " + book + " in stock, but we added " + std::to_string(num - 1) + " to your cart.";
				num = num - 1;
			}
			add = true;
		}
		else {
			add = false;
			message = "We do not offer this book. If you believe we do, check your spelling and casing and try again";
		}
	}
	string temp2;
	vector<string> row2;
	string line2;
	while (finCart >> temp2)
	{
		row2.clear();
		getline(finCart, line2);
		count += 1;
	}
	foutCart << std::to_string(count) + ", " + isbn + ", " + book + ", " + std::to_string(num) + "\n";
	fInventory.close();
	foutCart.close();
	return message;
}

string Cart::removeItem(string book) {
	return "bluh";
}

string Cart::viewCartItems() {
	fstream fin;
	fin.open("cart.csv", ios::in);
	string line;
	vector<string> row;
	string items = "";
	string temp;
	int count = 0;
	while (fin >> temp) {
		row.clear();
		getline(fin, line);
		stringstream ss(line);
		string word;
		char split = ',';
		while (getline(ss, word, split))
		{
			row.push_back(word + " ");
		}
		items.append(row[1] + "\n");
	}
	fin.close();
	return items;
}

string Cart::checkout() {
	string message;
	fstream finCart;
	finCart.open("cart.csv", ios::in);
	string temp;
	vector<string> row;
	string line;
	int count = 0;
	string items = "";
	while (finCart >> temp) {
		row.clear();
		getline(finCart, line);
		count += 1;
	}
	finCart.close();
	fstream fin;
	fin.open("cart.csv", ios::in);
	int count2 = 0;
	string temp2;
	string line2;
	vector<string> row2;
	while (fin >> temp2)
	{
		row2.clear();
		getline(fin, line2);
		count2 += 1;
		stringstream ss(line2);
		string word2;
		char split2 = ',';
		while (getline(ss, word2, split2))
		{
			row2.push_back(word2);
		}
		if (count == count2)
		{
			items.append(row2[1]);
		}
		else {
			items.append(row2[1] + ",");
		}
	}
	items.append("\n");
	fin.close();
	message = std::to_string(count) + " items purchased: " + items;
	return message;
}

