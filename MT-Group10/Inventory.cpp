#include "Inventory.h"

void Inventory::addInventory(Book book, int stock)
{

   fstream fin, fout;
   fin.open("Inventory.csv", ios::in);
   fout.open("Inventorynew.csv", ios::out);
   
   vector <string> row;
   int count;
   int num = 1;
   string line, word, temp, temp1;
   while(fin >> temp)
   {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      char split = ',';
		while (getline(s, word, split))
		{
			row.push_back(word);
		}      

      int row_size = row.size();
      long int isbn = stoi(row[0]);
     
      if(isbn == book.getISBN())
      {
         count = 1;
         stringstream convert;
         int current = stoi(row[3]);
         int total = stock + current; //current + stock;
          
         // sending a number as a stream into output string
         convert << total;
  
         // the str() converts number into string
         row[3] = convert.str();
  
         if (!fin.eof()) 
         {  
            fout << num << ",";
            num++;
            for (int i = 0; i < row_size - 1; i++) 
            {
  
               // write the updated data
               // into a new file 'reportcardnew.csv'
               // using fout
               fout << row[i] << ",";
            }
  
            fout << row[row_size - 1] << "\n";
         }
       }
       else
       {
         fout << num << ",";
         num++;
         for (int i = 0; i < row_size - 1; i++) 
         {
  
            // write the updated data
            // into a new file 'reportcardnew.csv'
            // using fout
            fout << row[i] << ",";
         }
  
         fout << row[row_size - 1] << "\n";
       }
       if(fin.eof())
          break;
   }
   if(count == 0)
   {  
      cout << "Record Not Found" << endl;
   }
   fin.close();
   fout.close();
   remove("Inventory.csv");
   rename("Inventorynew.csv", "Inventory.csv"); 
}

bool Inventory::removeInventory(Book book, int stock)
{
   fstream fin, fout;
   fin.open("Inventory.csv", ios::in);
   fout.open("Inventorynew.csv", ios::out);
   
   vector <string> row;
   int count;
   int num = 1;
   string line, word, temp, temp1;
   while(fin >> temp)
   {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      char split = ',';
		while (getline(s, word, split))
		{
			row.push_back(word);
		}      

      int row_size = row.size();
      long int isbn = stoi(row[0]);
     
      if(isbn == book.getISBN())
      {
         count = 1;
         stringstream convert;
         int current = stoi(row[3]);
         int total = current - stock; //current + stock;
         if(total <= 0)
            return false;
          
         // sending a number as a stream into output string
         convert << total;
  
         // the str() converts number into string
         row[3] = convert.str();
  
         if (!fin.eof()) 
         {  
            fout << num << ",";
            num++;
            for (int i = 0; i < row_size - 1; i++) 
            {
  
               // write the updated data
               // into a new file 'reportcardnew.csv'
               // using fout
               fout << row[i] << ",";
            }
  
            fout << row[row_size - 1] << "\n";
         }
       }
       else
       {
         fout << num << ",";
         num++;
         for (int i = 0; i < row_size - 1; i++) 
         {
  
            // write the updated data
            // into a new file 'reportcardnew.csv'
            // using fout
            fout << row[i] << ",";
         }
  
         fout << row[row_size - 1] << "\n";
       }
       if(fin.eof())
          break;
   }
   if(count == 0)
   {
      cout << "Record Not Found" << endl;
   }
   fin.close();
   fout.close();
   remove("Inventory.csv");
   rename("Inventorynew.csv", "Inventory.csv"); 
   return true;
}

void Inventory::updateStock(int ISBN, int stock)
{
  Book tmp(ISBN, "tmp", "tmp", 69.99); 
  if (stock < 0) {
    removeInventory(tmp, -stock);
  }
  else {
    addInventory(tmp, stock);
  }
}

void Inventory::viewInventory()
{
   fstream fin;
   fin.open("Inventory.csv", ios::in);
   
   int num = 1;
   vector <string> row;
   string line, word, temp, temp1;
   while(fin >> temp)
   {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      char split = ',';
		while (getline(s, word, split))
		{
			row.push_back(word);
		}      

      int row_size = row.size();
      long int isbn = stoi(row[0]);
      
      cout << num << ".";
      num++;
      cout << "Title: " << row[2] << endl;
      cout << "Author: " << row[1] << endl;
      cout << "ISBN: " << row[0] << endl;
      cout << "Price: " << row[4] << endl;
      cout << "Stock: " << row[3] << endl;
      cout << endl;
    
      if(fin.eof())
        break;
   }
    fin.close(); 
}

int Inventory::getStock(int ISBN)
{
   fstream fin;
   fin.open("Inventory.csv", ios::in);
   
   vector <string> row;
   int count;
   string line, word, temp, temp1;
   while(fin >> temp)
   {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      char split = ',';
		while (getline(s, word, split))
		{
			row.push_back(word);
		}      

      int row_size = row.size();
      long int isbn = stoi(row[0]);
     
      if(isbn == ISBN)
         return stoi(row[3]);
   }
   fin.close();
   return false;
}

