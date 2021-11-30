#include "Book.h"
#include <string>

Book::Book(int isbn, string title, string author, float price)
{
	this->isbn = isbn;
	this->title = title;
	this->author = author;
	this->price = price;
}

int Book::getISBN()
{
	return this->isbn;
}

string Book::getTitle()
{
	return this->title;
}

string Book::getAuthor()
{
	return this->author;
}

float Book::getPrice()
{
	return this->price;
}
