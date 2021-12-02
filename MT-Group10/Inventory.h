#pragma once
#ifndef Inventory_H

#define Inventory_H
#include "Book.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Inventory
{
     public:
      bool addInventory(Book book, int stock);
      bool removeInventory(Book book, int stock);
      void updateStock(int ISBN, int stock);
      void viewInventory(ostream& os);
      int getStock(int ISBN);
};
#endif // Inventory_H
