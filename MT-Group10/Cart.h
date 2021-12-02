#pragma once
#define Cart_h
#include <string>
#include <iostream>
#include <vector>
using std::string;

class Cart
{
private:
	string book;
	int num;
public:
	Cart();
	string addItem(string book, int num);
	string removeItem(string book);
	string viewCartItems();
	string checkout();
	string getISBN(string book);
};

