//
//  main.cpp
//  CTaxRegister
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
struct person  {
    string name;
    string address;
    int income;
    int expense;
};

class CTaxRegister
{
private:
    person ** data;
    size_t counterSize;
    size_t counterRecord;
public:
    CTaxRegister            (void);
    ~CTaxRegister           (void);
    bool Birth              (const string & name, const string & addr);
    bool Death              (const string & name, const string & addr);
    bool Income             (const string & name, const string & addr, int amount);
    bool Expense            (const string & name, const string & addr, int amount);
    bool Audit              (const string & name, const string & addr, int & sumIncome,int & sumExpense) const;
    void makeBigger         (    );
    int SearchIndex         (string const & oName, string const & oAddr, int &place) const;
    
};

CTaxRegister::CTaxRegister(void){
    this->counterSize = 20;
    this->counterRecord = 0;
    
    
    data = new person*[counterSize];
    for (size_t i = 0; i < counterSize; i++) {
        data[i] = NULL;
    }
    
}

CTaxRegister::~CTaxRegister(void){
    for (size_t i = 0; i < counterRecord; i++) {
        if (data[i]) {
            delete data[i];
        }
    }
    
    delete [] data;
    
}

void CTaxRegister::makeBigger(){
    counterSize *= 2;
    person ** temp = new person*[counterSize]; // create new bigger array.
    for (size_t i=0; i < counterRecord; i++) {
        temp[i] = data[i];       // copy values to new array.
    }
    for (size_t i=counterRecord; i<counterSize; i++) {
        temp[i] = NULL;       // nulls the rest
    }
    delete [] data;              // free old array memory.
    data = temp;                 // now data points to new array.
    temp = NULL;
    
}

int CTaxRegister::SearchIndex(string const & oName, string const & oAddr, int &place) const{
    int left = 0, right = (int)counterRecord - 1;
    int center = 0;
    place = 0;
    while (left <= right && counterRecord){
        center = (left + right) / 2;
        if (oName < data[center]->name || ( oName == data[center]->name && oAddr < data[center]->address) )
            right = center -1;
        else if (oName > data[center]->name || ( oName == data[center]->name && oAddr > data[center]->address) )
            left = center + 1;
        else {
            place = center;
            return 1;
        }
    }
    place = left;
    return 0;
}

bool CTaxRegister::Birth(const string &name, const string &addr){
    
    if (SearchIndex(name, addr, place)){
        return false;
    }else{
        if (counterRecord == counterSize) makeBigger();
        
        for (size_t i = counterRecord; i > (size_t)place; i--)
            data[i] = data[i-1];
        data[place] = NULL;
        data[place] = new person();
        data[place]->name = name;
        data[place]->address = addr;
        
        counterRecord++;
        return true;
    }
}


bool CTaxRegister::Death(const string &name, const string &addr){
    if (!SearchIndex(name, addr, place)){
        return false;
    }
    delete data[place];
    
    for (int i = place; i < (int)counterRecord; i++) {
        data[i] = data [i+1];
    }
    counterRecord--;
    data[counterRecord] = NULL;
    return true;
}

bool CTaxRegister::Income(const string &name, const string &addr, int amount){
    if (!SearchIndex(name, addr, place)){
        cout << "INCOME : Citizen not found" << endl;
        return false;
    }
    
    data[place]->income += amount;
    return true;
    
    
}

bool CTaxRegister::Expense(const string &name, const string &addr, int amount){
    if (!SearchIndex(name, addr, place)){
        cout << "EXPENSE : Citizen not found" << endl;
        return false;
    }
    
    data[place]->expense += amount;
    return true;
    
}

bool CTaxRegister::Audit(const string &name, const string &addr, int &sumIncome, int &sumExpense)const{
    if (!SearchIndex(name, addr, place)){
        cout << "AUDIT : Citizen not found" << endl;
        return false;
    }
    sumExpense = data[place]->expense;
    sumIncome = data[place]->income;
    return true;
}







#ifndef __PROGTEST__
int main(){
    
    
    bool   status;
    int    sumIncome, sumExpense;
    
    CTaxRegister b1;
    status = b1 . Birth ( "John Smith", "Oak Road 23" );
    // status = true
    status = b1 . Birth ( "John Smith", "Oak Road 23" );
    // status fail
    status = b1 . Birth ( "Jane Hacker", "Main Street 17" );
    // status = true
    status = b1 . Birth ( "Peter Hacker", "Main Street 17" );
    // status = true
    status = b1 . Birth ( "John Smith", "Main Street 17" );
    // status = true
    status = b1 . Income ( "Peter Hacker", "Main Street 17", 2000 );
    // status = true
    status = b1 . Income ( "Jane Hacker", "Main Street 17", 3000 );
    // status = true
    status = b1 . Income ( "Peter Hacker", "Main Street 17", 4000 );
    // status = true
    status = b1 . Expense ( "Jane Hacker", "Main Street 17", 2000 );
    // status = true
    status = b1 . Expense ( "John Smith", "Main Street 17", 500 );
    // status = true
    status = b1 . Expense ( "Jane Hacker", "Main Street 17", 100 );
    // status = true
    status = b1 . Audit ( "John Smith", "Oak Road 23", sumIncome, sumExpense );
    // status = true, sumIncome=0, sumExpense=0
    status = b1 . Audit ( "Jane Hacker", "Main Street 17", sumIncome, sumExpense );
    // status = true, sumIncome=3000, sumExpense=2100
    status = b1 . Audit ( "Peter Hacker", "Main Street 17", sumIncome, sumExpense );
    // status = true, sumIncome=6000, sumExpense=0
    status = b1 . Audit ( "John Smith", "Main Street 17", sumIncome, sumExpense );
    // status = true, sumIncome=0, sumExpense=500
    status = b1 . Death ( "John Smith", "Main Street 17" );
    // status = true
    
    CTaxRegister b2;
    status = b2 . Birth ( "John Smith", "Oak Road 23" );
    // status = true
    status = b2 . Birth ( "Jane Hacker", "Main Street 17" );
    // status = true
    status = b2 . Income ( "Jane Hacker", "Oak Road 10", 4000 );
    // status = false
    status = b2 . Expense ( "John Smith", "Main Street 18", 500 );
    // status = false
    status = b2 . Audit ( "John Nowak", "Second Street 23", sumIncome, sumExpense );
    // status = false
    status = b2 . Death ( "Peter Nowak", "5-th Avenue" );
    // status = false
    status = b2 . Birth ( "Jane Hacker", "Main Street 17" );
    // status = false
    status = b2 . Birth ( "Joe Hacker", "Elm Street 23" );
    // status = true
    status = b2 . Birth ( "Joe Hacker", "Elm Street 23" );
    // status = false
    status = b2 . Death ( "Jane Hacker", "Main Street 17" );
    // status = true
    status = b2 . Audit ( "Jane Hacker", "Main Street 17", sumIncome, sumExpense );
    // status = false
    status = b2 . Birth ( "Jane Hacker", "Main Street 17" );
    // status = true
    
    
    
    // MemoryManagent test
    CTaxRegister b3;
    b3.Birth("a","a");
    b3.Birth("b", "b");
    b3.Birth("c", "c");
    b3.Birth("d", "b");
    b3.Birth("e", "e");
    b3.Birth("f", "f");
    b3.Birth("g", "g");
    b3.Birth("h", "h");
    b3.Birth("i", "i");
    b3.Birth("j", "j");
    b3.Birth("k", "k");
    b3.Birth("l", "l");

    b3.Death("a","a");
    b3.Death("b", "b");
    b3.Death("c", "c");
    b3.Death("d", "b");
    b3.Death("e", "e");
    b3.Death("f", "f");
    b3.Death("g", "g");
    b3.Death("h", "h");
    b3.Death("i", "i");
    b3.Death("j", "j");
    b3.Death("k", "k");
    b3.Death("l", "l");
    
    
    
    
    
    
}

#endif /* __PROGTEST__ */