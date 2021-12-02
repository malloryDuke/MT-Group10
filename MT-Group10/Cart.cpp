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
	int purchased = num;
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
				purchased = std::stoi(inStock);
				message = "We do not have " + std::to_string(num) + " of the book " + book + " in stock, but we added " + std::to_string(purchased) + " to your cart.";
			}
			else {
				message = "Book added to cart!";
			}
			add = true;
			break;
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
	if (add)
	{
		foutCart << std::to_string(count) + ", " + isbn + ", " + book + ", " + std::to_string(purchased) + "\n";
	}
	fInventory.close();
	foutCart.close();
	return message;
}

string Cart::removeItem(string book) {
	fstream fin, fout;
	fin.open("cart.csv", ios::in);
	fout.open("cartnew.csv", ios::out);
	int index;
	string line, word;
	vector<string> row;
	int count = 0;
	string message;
	string temp;
	int lineCount = 0;
	while (fin >> temp)
	{
		row.clear();
		getline(fin, line);
		lineCount += 1;
		stringstream s(line);
		char split = ',';
		while (getline(s, word, split))
		{
			row.push_back(word);
		}
		int rowSize = row.size();

		string whitespace = " \t";
		const auto strBegin = row[1].find_first_not_of(whitespace);

		const auto strEnd = row[1].find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;
		string title = row[1].substr(strBegin, strRange);

		if (title == book)
		{
			lineCount = lineCount - 1;
		}
		if (title != book)
		{
			if (rowSize!=0 && (!fin.eof())) {
				fout << lineCount << ",";
				for (int i = 0; i < rowSize; ++i)
				{
					fout << row[i] << ",";
				}
				fout << "\n";
			}
		}
		else {
			count = 1;
		}
		if (fin.eof())
		{
			break;
		}
	}
	if (count == 1)
	{
		message = "Book was removed from your cart!\n";
	}
	else
	{
		message = "Book was not found in your cart!\n";
	}
	fin.close();
	fout.close();

	remove("cart.csv");
	rename("cartnew.csv", "cart.csv");
	return message;
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
			row.push_back(word);
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
	message = "Items purchased: " + items;
	return message;
}

string Cart::getISBN(string book) {
	fstream fInventory;
	fInventory.open("inventory.csv", ios::in);
	string line;
	vector<string> row;
	string temp;
	string isbn;
	while (fInventory >> temp) {
		row.clear();
		getline(fInventory, line);
		cout << line + "\n";
		stringstream ss(line);
		string word;
		char split = ',';
		while (getline(ss, word, split))
		{
			row.push_back(word);
			cout << word + "\n";
		}
		string whitespace = " \t";
		const auto strBegin = row[2].find_first_not_of(whitespace);

		const auto strEnd = row[2].find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;
		string title = row[2].substr(strBegin, strRange);

		if (book == title)
		{
			isbn = row[0];
		}
		else {
			isbn = "";
		}
	}
	fInventory.close();
	return isbn;
}

