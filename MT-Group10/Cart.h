#pragma once
#define Cart_H
#include <string>
#include <iostream>
using std::string;

class Cart
{
public:
	Cart();
	void addItem(Book book, int num);
	void removeItem(Book book);
	string viewCartItems();
	void checkout();

private:
	Book book;
	int num;
};

Cart::Cart()
{
}

