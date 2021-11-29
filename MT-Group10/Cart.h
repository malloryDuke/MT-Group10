#pragma once
#define Cart_h
#include <string>
#include <iostream>
using std::string;

class Cart
{
private:
	string book;
	int num;
public:
	Cart();
	string addItem(string book, int num);
	void removeItem(string book);
	string viewCartItems();
	void checkout();
};

