//Class for the User


#ifndef USER_H
#define USER_H
//#include <cart.h>
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
    
    //User(string uname, string pass, string addr, string paymentInfo);
    void createUser(string uname, string pass, string addr, string paymentInfo);
    void removeUser(string uname);
    bool login(string uname, string pass);
    void logout();
    void editShippingInfo(string newAddress);
    void editPayInfo(string newPay);
    //void addOrder(Cart cartInfo);
    vector<string> viewOrderHistory();
    ~User();
};

/*Class Constructor
User::User(string uname, string pass, string addr, string paymentInfo){
    //Set Variables
    username = uname;
    password = pass;
    address = addr;
    payment = paymentInfo;
}
*/
void User::createUser(string uname, string pass, string addr, string paymentInfo){
    //Set Variables
    username = uname;
    password = pass;
    address = addr;
    payment = paymentInfo;
    fstream usercsv;
    //Open csv File
    usercsv.open("accountInfo.csv", ios::out|ios::app);
    //Write the new user to the csv file
    usercsv << uname << "," << pass << "," << addr << "," << paymentInfo << "\n";
}

void User::removeUser(string uname){
    //create new file for update
    fstream newout, usercsv;
    //open both files
    usercsv.open("accountInfo.csv", ios::in);
    newout.open("newaccountInfo.csv", ios::out);

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
                newout << input[i] << ", ";
            }
            newout << input[input.size()-1] << "\n";
        }
    }

    //Close the files
    usercsv.close();
    newout.close();

    //Remove the old file 
    remove("accountInfo.csv");
    //Rename the new file
    rename("newaccountInfo.csv", "accountInfo.csv");

}

bool User::login(string uname, string pass){
    fstream usercsv;
    //Read the username and password from the csv file
    usercsv.open("accountInfo.csv", ios::in);
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
    usercsv.open("accountInfo.csv", ios::in);
    newout.open("newaccountInfo.csv", ios::out);

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
    remove("accountInfo.csv");
    //Rename the new file
    int test = rename("newaccountInfo.csv", "accountInfo.csv");
    if (test != 0) {cout << "Rename Failure\n"; perror("Reaname"); exit(EXIT_FAILURE);}
}

//Update the payment info
void User::editPayInfo(string newPay){
    //create new file for update
    fstream newout, usercsv;
    //open both files
    usercsv.open("accountInfo.csv", ios::in);
    newout.open("newaccountInfo.csv", ios::out);

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
    remove("accountInfo.csv");
    //Rename the new file
    int test = rename("newaccountInfo.csv", "accountInfo.csv");
    if (test != 0) {cout << "Rename Failure\n"; perror("Reaname"); exit(EXIT_FAILURE);}
}

//void User::addOrder(){

//}

vector<string> User::viewOrderHistory(){
    vector<string> returnVal;
    return returnVal;
}


#endif