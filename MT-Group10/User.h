//Class for the User
#ifndef USER_H
#define USER_H
//#include "Cart.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class User {
private:
    string password;
    string payment;
public:
    string username;
    string address;
    
   
    void createUser(string uname, string pass, string addr, string paymentInfo);
    void removeUser(string uname);
    bool login(string uname, string pass);
    void logout();
    void editShippingInfo(string newAddress);
    void editPayInfo(string newPay);
    void addOrder(string order);
    vector<string> viewOrderHistory();
    ~User();
};


void User::createUser(string uname, string pass, string addr, string paymentInfo){
    //Set Variables
    username = uname;
    password = pass;
    address = addr;
    payment = paymentInfo;
    fstream usercsv;
    //Open csv File
    usercsv.open("users.csv", ios::out|ios::app);
    //Write the new user to the csv file
    usercsv << uname << "," << pass << "," << addr << "," << paymentInfo << "\n";
}

void User::removeUser(string uname){
    //create new file for update
    fstream newout, usercsv;
    //open both files
    usercsv.open("users.csv", ios::in);
    newout.open("newusers.csv", ios::out);

    string line,word;
    vector <string> input;

    while(!usercsv.eof()){
        //Clear the input
        input.clear();

        getline(usercsv,line);
        stringstream s(line);

        while(getline(s,word,',')){
            input.push_back(word);
        }

        if(input[0] != username){
           //Write everything except for the row to be deleted
            if(!usercsv.eof()){
                //Write to new file
                int test = input.size();
                for (int i = 0; i < test -1; i++)
                newout << input[i] << ',';
            }
            newout << input[input.size()-1] << "\n";
        }
    }

    //Close the files
    usercsv.close();
    newout.close();

    //Remove the old file 
    remove("users.csv");
    //Rename the new file
    rename("newusers.csv", "users.csv");

}

bool User::login(string uname, string pass){
    fstream usercsv;
    //Read the username and password from the csv file
    usercsv.open("users.csv", ios::in);
    string line, word;
    vector <string> input;
    while (!usercsv.eof()){
        //clear the input vector before reading
        input.clear();

        getline(usercsv, line);
        stringstream s(line);
        while(getline(s,word, ','))
        {
            input.push_back(word);
        }
     //Verify that the username and password match
    if(uname == input[0] && pass == input[1]){
        usercsv.close();
        username = input[0];
        password = input[1];
        address = input[2];
        payment = input[3];
        return true;
        }
    }
   
    usercsv.close();
    //Otherwise return false
    return false;
}

void User::logout(){
    fstream usercsv;
    usercsv.close();
    
}

//Update the address info
void User::editShippingInfo(string newAddress){
    //create new file for update
    fstream newout, usercsv;
    //open both files
    usercsv.open("users.csv", ios::in);
    newout.open("newusers.csv", ios::out);

    string line,word;
    vector <string> input;
    //New adress
    address = newAddress;

    while(!usercsv.eof()){
        //Clear the input
        input.clear();

        getline(usercsv,line);
        stringstream s(line);

        while(getline(s,word,',')){
            input.push_back(word);
        }

        if(input[0] == username){
            //insert new address
            input[2] = newAddress;
        }
        if(!usercsv.eof()){
            //Write to new file
            newout << input[0] << "," << input[1] << "," << input[2] << "," << input[3] << "\n";
        }
    }

    //Close the files
    usercsv.close();
    newout.close();

    //Remove the old file 
    remove("users.csv");
    //Rename the new file
    int test = rename("newusers.csv", "users.csv");
    if (test != 0) {cout << "Rename Failure\n"; perror("Reaname"); exit(EXIT_FAILURE);}
}

//Update the payment info
void User::editPayInfo(string newPay){
    //create new file for update
    fstream newout, usercsv;
    //open both files
    usercsv.open("users.csv", ios::in);
    newout.open("newusers.csv", ios::out);

    string line,word;
    vector <string> input;
    //New adress
    payment = newPay;

    while(!usercsv.eof()){
        //Clear the input
        input.clear();

        getline(usercsv,line);
        stringstream s(line);

        while(getline(s,word,',')){
            input.push_back(word);
        }
        
        //getline(s,word,'\n');
        //input.push_back(word);

        if(input[0] == username){
            //insert new address
            input[3] = newPay;
        }
        if(!usercsv.eof()){
            //Write to new file
            newout << input[0] << "," << input[1] << "," << input[2] << "," << input[3] << "\n";
        }
    }

    //Close the files
    usercsv.close();
    newout.close();

    //Remove the old file 
    remove("users.csv");
    //Rename the new file
    int test = rename("newusers.csv", "users.csv");
    if (test != 0) {cout << "Rename Failure\n"; perror("Reaname"); exit(EXIT_FAILURE);}
}

void User::addOrder(string order){
    //Open the orderHistory File
    fstream orderHistory;
    orderHistory.open("orderHistory.csv", ios::out | ios::app);
    //Add the username followed by the order to the list
    stringstream s(order);
    string word;
    orderHistory << username << "," << order;
    /*
    while(getline(s, word,','))
    {
        orderHistory << word;
        if(word[word.size()-1] != '\n')
            orderHistory << ",";
    }
    orderHistory << "\n";
    */
}


vector<string> User::viewOrderHistory(){
    fstream orderHistory;
    vector<string> returnVal;
    vector<string> input;
    string line, word;
    int count = 1;
    orderHistory.open("orderHistory.csv", ios::in);
    while(!orderHistory.eof())
    {
        input.clear();
        getline(orderHistory,line);
        stringstream s(line);
        while(getline(s,word,',')){
                input.push_back(word);
            }
        if(input[0] == username){
            string tmp = "Order #";
            tmp += to_string(count);
            tmp += ": \n";
            returnVal.push_back(tmp);
            tmp.clear();
            
            for(int i = 1; i < input.size(); i++)
                {
                    returnVal.push_back(input[i]);
                    if(i != (input.size() -1))
                        returnVal.push_back(",");
                }
            returnVal.push_back("\n");
            count++;
            }
    }
    return returnVal;
}


#endif