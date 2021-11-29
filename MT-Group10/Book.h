#pragma once
#define Book_h
#include <string>
#include <iostream>
using std::string;

class Book
{
private:
	int isbn;
	string title;
	string author;
	float price;
public:
	Book(int isbn, string title, string author, float price);
	int getISBN();
	string getTitle();
	string getAuthor();
	float getPrice();
};

