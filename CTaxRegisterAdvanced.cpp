//
//  main.cpp
//  CTaxRegisterAdvanced
//
//  Created by Tomas Sykora, jr. on 15/03/14.
//  Copyright (c) 2014 Tomas Sykora, jr. All rights reserved.
//
#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */

int place;
int accPlace;
struct account;



struct person {
    string name;
    string address;

    account * accID;
};

struct account{
    string account;
    int income;
    int expense;

};

class CTaxRegister {
private:
    person **data;
    account **accountData;
    size_t counterSize;
    size_t counterRecord;
    
public:
    CTaxRegister(void);
    ~CTaxRegister(void);

    
    bool Birth        (const string &name, const string &addr, const string &account);
    bool Death        (const string &name, const string &addr);
    bool Income       (const string &account, int amount);
    bool Income       (const string &name, const string &addr, int amount);
    bool Expense      (const string &account, int amount);
    bool Expense      (const string &name, const string &addr, int amount);
    bool Audit        (const string &name, const string &addr, string &account, int &sumIncome, int &sumExpense) const;
    
    void makeBigger();
    int SearchIndex(string const &oName, string const &oAddr, int &place) const;
    int SearchAccount(string const & account, int & place);
    void TestPrint();
//    int SearchIndex(string const &oName, string const &oAddr,string const &account, int &place) const;
//    int SearchIndex(string const &acount, int & place);
//    int SearchAccount ( string const & account, int &place);
    
    
};

CTaxRegister::CTaxRegister(void) {
    this->counterSize = 20;
    this->counterRecord = 0;

    data = new person *[counterSize];
    accountData = new account*[counterSize];
    
    for (size_t i = 0; i < counterSize; i++) {
        accountData[i] = NULL;
        data[i] = NULL;

        
    }
}

CTaxRegister::~CTaxRegister(void) {
    for (size_t i = 0; i < counterRecord; i++) {
        if (data[i]) {
            delete data[i]->accID;
            delete data[i];
        }
    }
    delete[] data;
    delete [] accountData;
}

void CTaxRegister::makeBigger() {
    counterSize *= 2;
    person **temp = new person *[counterSize]; // create new bigger array.
    account **accTemp = new account*[counterSize];
    for (size_t i = 0; i < counterRecord; i++) {
        temp[i] = data[i]; // copy values to new array.
        accTemp[i] = accountData[i];
    }
    for (size_t i = counterRecord; i < counterSize; i++) {
        temp[i] = NULL; // nulls the rest
        accTemp[i] = NULL;
    }
    delete[] data; // free old array memory.
    delete[] accountData;
    data = temp;   // now data points to new array.
    accountData = accTemp;
    
    temp = NULL;
    accTemp = NULL;
}

int CTaxRegister::SearchIndex(string const &oName, string const &oAddr,int &place) const {
    int left = 0, right = (int)counterRecord - 1;
    int center = 0;
    place = 0;
    while (left <= right && counterRecord) {
        center = (left + right) / 2;
        if (oName < data[center]->name ||
            (oName == data[center]->name && oAddr < data[center]->address))
            right = center - 1;
        else if (oName > data[center]->name ||
                 (oName == data[center]->name && oAddr > data[center]->address))
            left = center + 1;
        else {
            place = center;
            return 1;
        }
    }
    place = left;
    return 0;
}


int CTaxRegister::SearchAccount(const string &account, int &place){
    int left = 0, right = (int)counterRecord - 1;
    int center = 0;
    place = 0;
    while (left <= right && counterRecord) {
        center = (left + right) / 2;
        if (account < accountData[center]->account)
            right = center - 1;
        else if (account > accountData[center]->account)
            left = center + 1;
        else {
            place = center;
            return 1;
        }
    }
    place = left;
    return 0;

}




bool CTaxRegister::Birth(const string &name, const string &addr, const string &account){
    if (SearchIndex(name, addr, place) || SearchAccount(account, accPlace)) {
        return false;
    } else {
        if (counterRecord == counterSize)
            makeBigger();
        
        
        for (size_t i = counterRecord; i > (size_t)place; i--)
            data[i] = data[i - 1];
        data[place] = NULL;
        data[place] = new person();
        data[place]->name = name;
        data[place]->address = addr;
       
        for (size_t i = counterRecord; i > (size_t)accPlace; i--)
            accountData[i] = accountData[i - 1];
        accountData[accPlace] = NULL;
        accountData[accPlace] = new struct account();
        accountData[accPlace]->account = account;
        


       data[place]->accID = accountData[accPlace] ;

        counterRecord++;
        return true;
    }
}

void CTaxRegister::TestPrint(){
    for (size_t i = 0; i < this->counterRecord; i++) {
        cout << this->data[i]->name << " -> " << this->data[i]->address <<" -> "<< this->data[i]->accID << " == " << this->data[i]->accID->account
        <<  " -> " << " income=" << this->data[i]->accID->income << " expense=" << this->data[i]->accID->expense << endl;
    }
    cout << endl;
    for (size_t i = 0; i < this->counterRecord; i++) {
        cout  << this->accountData[i] << " == " << this->accountData[i]->account << endl;
    }
    
    
}


bool CTaxRegister::Death(const string &name, const string &addr) {
    if (!SearchIndex(name, addr, place)) {
        return false;
    }
    SearchAccount(this->data[place]->accID->account, accPlace);
    
    delete data[place];
    delete accountData[accPlace];
    
    for (int i = place; i < (int)counterRecord; i++) {
        data[i] = data[i + 1];
    }
    
    for (int i = accPlace; i < (int)counterRecord; i++) {
        accountData[i] = accountData[i + 1];
    }
    
    counterRecord--;
    data[counterRecord] = NULL;
    accountData[counterRecord] = NULL;
    return true;
}

bool CTaxRegister::Income(const string &name, const string &addr, int amount) {
    if (!SearchIndex(name, addr, place)) {
        cout << "INCOME : Citizen not found" << endl;
        return false;
    }
    
    data[place]->accID->income += amount;
    return true;
}

bool CTaxRegister::Income(const string &account, int amount){
    if (!SearchAccount(account, accPlace)) {
        cout << "INCOME -> ACCOUNT: NOT FOUND"<< endl;
        return false;
    }
    accountData[accPlace]->income += amount;
    return true;
    
}

bool CTaxRegister::Expense(const string &name, const string &addr, int amount) {
    if (!SearchIndex(name, addr, place)) {
        cout << "EXPENSE : Citizen not found" << endl;
        return false;
    }
    
    data[place]->accID->expense += amount;
    return true;
}

bool CTaxRegister::Expense(const string &account, int amount){
    if (!SearchAccount(account, accPlace)) {
        cout << "EXPENSE -> ACCOUNT: NOT FOUND"<< endl;
        return false;
    }
    accountData[accPlace]->expense += amount;
    return true;
}

bool CTaxRegister::Audit(const string &name, const string &addr, string &account, int &sumIncome, int &sumExpense) const{
    if (!SearchIndex(name, addr, place)) {
        cout << "AUDIT : Citizen not found" << endl;
        return false;
    }
    sumExpense = data[place]->accID->expense;
    sumIncome = data[place]->accID->income;
    account = data[place]->accID->account;
    return true;
}

#ifndef __PROGTEST__
int main() {
    bool   status;
    string acct;
    int    sumIncome, sumExpense;
    
    CTaxRegister b1;
    status = b1 . Birth ( "John Smith", "Oak Road 23", "123/456/789" );
    // status = true
    status = b1 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" );
    // status = true
    status = b1 . Birth ( "Peter Hacker", "Main Street 17", "634oddT" );
    // status = true
    status = b1 . Birth ( "John Smith", "Main Street 17", "Z343rwZ" );
    // status = true
    
   
    
    status = b1 . Income ( "Xuj5#94", 1000 );
    // status = true
    status = b1 . Income ( "634oddT", 2000 );
    // status = true
    status = b1 . Income ( "123/456/789", 3000 );
    // status = true
    status = b1 . Income ( "634oddT", 4000 );
    // status = true
    status = b1 . Income ( "Peter Hacker", "Main Street 17", 2000 );
    // status = true
    
    
    status = b1 . Expense ( "Jane Hacker", "Main Street 17", 2000 );
    // status = true
    status = b1 . Expense ( "John Smith", "Main Street 17", 500 );
    // status = true
    status = b1 . Expense ( "Jane Hacker", "Main Street 17", 1000 );
    // status = true
    status = b1 . Expense ( "Xuj5#94", 1300 );
    // status = true
    

    
    
    status = b1 . Audit ( "John Smith", "Oak Road 23", acct, sumIncome, sumExpense );
    // status = true, acct = "123/456/789", sumIncome=3000, sumExpense=0
    status = b1 . Audit ( "Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense );
    // status = true, acct = "Xuj5#94", sumIncome=1000, sumExpense=4300
    status = b1 . Audit ( "Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense );
    // status = true, acct = "634oddT", sumIncome=8000, sumExpense=0
    status = b1 . Audit ( "John Smith", "Main Street 17", acct, sumIncome, sumExpense );
    // status = true, acct = "Z343rwZ", sumIncome=0, sumExpense=500
       b1.TestPrint();
    status = b1 . Death ( "John Smith", "Main Street 17" );
    // status = true
    b1.TestPrint();

    CTaxRegister b2;
    status = b2 . Birth ( "John Smith", "Oak Road 23", "123/456/789" );
    // status = true
    status = b2 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" );
    // status = true
    status = b2 . Income ( "634oddT", 4000 );
    // status = false
    status = b2 . Expense ( "John Smith", "Main Street 18", 500 );
    // status = false
    status = b2 . Audit ( "John Nowak", "Second Street 23", acct, sumIncome, sumExpense );
    // status = false
    status = b2 . Death ( "Peter Nowak", "5-th Avenue" );
    // status = false
    status = b2 . Birth ( "Jane Hacker", "Main Street 17", "4et689A" );
    // status = false
    status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" );
    // status = false
    status = b2 . Death ( "Jane Hacker", "Main Street 17" );
    // status = true
    status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" );
    // status = true
    status = b2 . Audit ( "Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense );
    // status = true, acct = "Xuj5#94", sumIncome=0, sumExpense=0
    status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "AAj5#94" );
    // status = false
    return true;
}

#endif /* __PROGTEST__ */
