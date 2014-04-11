#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
#endif /* __PROGTEST__ */

int place;


struct comp{
    string name;
    string address;
};

struct owner{
    string name;
    string address;
    comp * company;

    owner(){
        this->company = new comp();

    }
    virtual ~owner(){
        if (this->company == NULL)
            delete this->company;
    }

};

class CCompanyIndex
{
public:
    owner ** data;
    size_t counterSize;
    size_t counterRecord;
    int freeMem [1000];
    size_t counterFreeMem;

public:
    CCompanyIndex ( void );
    ~CCompanyIndex ( void );
    void makeBigger( void );
    bool Add    ( const string & oName, const string & oAddr, const string & cName, const string & cAddr );
    bool Del    ( const string & oName, const string & oAddr );
    bool Search ( const string & oName, const string & oAddr,  string & cName,  string & cAddr )const;
    int  SearchIndex ( const string & oName, const string & oAddr, int &place)const;
    bool NullIndex (int);
    void quicksort(int, int);


};

CCompanyIndex::CCompanyIndex() {
    counterSize = 20;
    counterRecord = 0;

    data = new owner*[counterSize];

    for (size_t i = 0; i < counterSize; i++) {
        data[i] = NULL;
    }


}

CCompanyIndex::~CCompanyIndex() {
    for (size_t i = 0; i < counterRecord; i++) {
        if (data[i]) {
            delete data[i]->company;
            delete data[i];
        }
    }

    delete [] data;
}

void CCompanyIndex::makeBigger() {
    counterSize *= 2;
    owner ** temp = new owner*[counterSize]; // create new bigger array.
    for (size_t i=0; i<counterRecord; i++) {
        temp[i] = data[i];       // copy values to new array.
    }
    for (size_t i=counterRecord; i<counterSize; i++) {
        temp[i] = NULL;       // nulls the rest
    }
    delete [] data;              // free old array memory.
    data = temp;                 // now data points to new array.
    temp = NULL;
}

bool CCompanyIndex::NullIndex(int i ) {
    data[i]->name = "";
    data[i]->address = "";
    data[i]->company->name = "";
    data[i]->company->address = "";

    return true;

}


bool CCompanyIndex::Del(string const & oName, string const & oAddr) {


    if (!SearchIndex(oName, oAddr, place)){
        return false;
    }

    delete data[place]->company;
    delete data[place];

    for (int i = place; i < (int)counterRecord; i++) {
        data[i] = data [i+1];


    }

    counterRecord--;
    data[counterRecord] = NULL;



    return true;

}



bool CCompanyIndex::Add(string const & oName, string const & oAddr, string const & cName, string const & cAddr) {



    if (SearchIndex(oName, oAddr, place)){
        return false;
    }else{
        if (counterRecord == counterSize) makeBigger();
        //data[counterRecord+1] = new owner();
        for (size_t i = counterRecord; i > (size_t)place; i--)
            data[i] = data[i-1];
        data[place] = NULL;
        data[place] = new owner();
        data[place]->name = oName;
        data[place]->address = oAddr;
        data[place]->company->name = cName;
        data[place]->company->address = cAddr;

        counterRecord++;
        return true;
    }

}


int CCompanyIndex::SearchIndex(string const & oName, string const & oAddr, int &place) const{
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

bool CCompanyIndex::Search(string const & oName, string const & oAddr, string & cName, string & cAddr) const{
    if(!SearchIndex(oName, oAddr, place)){
        return false;
    }
    cName = data[place]->company->name;
    cAddr = data[place]->company->address;

    return true;
}

void CCompanyIndex::quicksort( int left, int right ) {
    int i = left , j = right;
    if (counterRecord < 2)
        return;
    string pivot = data[(right - left)/2 + left]->name;
    owner* tmp;

    while (i <= j){
        while (data[i]->name < pivot )
            i++;
        while (data[j]->name > pivot)
            j--;
        if (i <= j){
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            tmp = NULL;
            i++;
            j--;
        }
    };

    if (left < j)
        quicksort(left , j);
    if (i < right)
        quicksort( i, right);

}


//#ifndef __PROGTEST__
//int main(void){
//    bool   status;
//    string cName, cAddress;
//    CCompanyIndex  b1;
//    status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "One ACME road" );
//
//// status = true
//    status = b1 . Add ( "Brown", "Second street", "MakroHard, Inc.", "Soft street" );
//// status = true
//    status = b1 . Add ( "Hacker", "5-th avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
//// status = true
//    status = b1 . Add ( "Hacker", "7-th avenue", "Child toys, Inc.", "Red light district" );
//// status = true
//    status = b1 . Search ( "Brown", "Second street", cName, cAddress );
//// status = true, cName = "MakroHard, Inc.", cAddress="Soft street"
//    status = b1 . Search ( "Hacker", "Oak road", cName, cAddress );
//// status = false
//    status = b1 . Search ( "Smith", "Oak road", cName, cAddress );
//// status = true, cName = "ACME, Ltd.", cAddress="One ACME road"
//    status = b1 . Del ( "Smith", "Oak road" );
//// status = true
//    status = b1 . Search ( "Smith", "Oak road", cName, cAddress );
//// status = false
//
//    CCompanyIndex  b2;
//    status = b2 . Add ( "Smith", "Michigan avenue", "ACME, Ltd.", "One ACME road" );
//// status = true
//    status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
//// status = true, cName = "ACME, Ltd.", cAddress="One ACME road"
//    status = b2 . Del ( "Smith", "Michigan avenue" );
//// status = true
//    status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
//// status = false
//    status = b2 . Del ( "Smith", "Michigan avenue" );
//// status = false
//    status = b2 . Add ( "Smith", "Michigan avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
//// status = true
//    status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
//// status = true, cName = "Forks and Knives, Ltd.", cAddress="Cutlery avenue"
//    status = b2 . Add ( "Smith", "Michigan avenue", "Child toys, Inc.", "Red light district" );
//// status = false
//    status = b2 . Add ( "Smith", "Michigan avenue", "MakroHard, Inc.", "Soft street" );
//// status = false
//    status = b2 . Del ( "Smith", "Michigan avenue" );
//// status = true
//    status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
//// status = false
//    return 27;
//}
//#endif /* __PROGTEST__ */
//
