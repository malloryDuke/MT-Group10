#include "Cart.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
using std::fstream; using std::ios;

Cart::Cart() {
	book = "";
	num = 0;
}

void Cart::addItem(string book, int num) {

}

void Cart::removeItem(string book) {

}

string Cart::viewCartItems() {
	fstream fin;
	fin.open("cart.csv", ios::in);
	return "this";
}

void Cart::checkout() {

}

