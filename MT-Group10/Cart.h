#pragma once
#ifndef Cart_H

#define Cart_H
#include <string>
#include <iostream>
using std::string;

class Cart
{
	string book;
	int num;
public:
	void addItem(string book, int num);
	void removeItem(string book);
	string viewCartItems();
	void checkout();
};
#endif // !Cart_H

