#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */
template <class Typ>


// ArrayForProgtest
class AFP {
public:
	AFP(){
		array = NULL;
		size = 0;
		last_index = -1;
	}
	AFP(int count){
		array = new Typ[count];
		size = count;
		last_index = -1;
	}
	AFP(const AFP<Typ>& RSmartArray){
		array = new Typ[RSmartArray.length()];
		size = RSmartArray.length();
		last_index = -1;

		for (int i = 0; i < RSmartArray.length(); i++) {
			array[i] = RSmartArray[i];
		}
	}
	~AFP(){
		delete [] array;
	}
	void newArray(int count){
		if (array != NULL) {
			delete [] array;
		}
		array = new Typ[count];
		size = count;
		last_index = -1;
	}
	void extend(){
		Typ * new_array = new Typ[size*2];
		for (int i = 0; i < size; i++) {
			new_array[i] = array[i];
		}
		size *= 2;

		delete [] array;

		array = new_array;
	}
	int length() const{
		return last_index+1;
	}
	void add(Typ new_element){
		if (++last_index >= size) {
			this->extend();
		}
		array[last_index] = new_element;
	}
	bool operator==(const AFP &array2) const{
		for (int i = 0; i < size; i++) {
			if (this->array[i] != array2.array[i]) {
				return false;
			}
		}
		return true;
	}
	Typ& operator[](int i){
		if ((i < 0)||(i>size-1)) {
			std::cout << "out of range : array[" << i << "]" <<  std::endl;
			return array[0];
		}

		if (last_index < i) {
			last_index = i;
		}

		return array[i];
	}
	bool set(int i,Typ val){
		if ((i < 0)||(i>size-1)) {
			return false;
		}

		if (last_index < i) {
			last_index = i;
		}

		array[i] = val;

		return true;
	}
	AFP& operator+=(const Typ& new_element){
		this->add(new_element);

		return *this;
	}
private:
	Typ * array;
	int size, last_index;
};


class CAccount
{
public:
    CAccount(const char * accID, int initialBalance);
    CAccount();
    
    ~CAccount();
private:
    const char *accID;
    int balance;
    int ** log;


};

CAccount::CAccount(const char * accID, int initialBalance){
    this->accID = accID;
    this->balance = initialBalance;
}

CAccount::CAccount(){

}

CAccount::~CAccount() {

}



class CBank
 {
   public:
    // default constructor
    // copy constructor
    // destructor
    // operator =
    CBank();
    bool NewAccount  (const char *accID, int initialBalance);
    bool Transaction (const char *debAccID, const char *credAccID, int amount, const char * signature);
    bool TrimAccount (const char *accID);
    bool addAccount (const CAccount account);
    // Account ( accID )
   private:
    AFP<CAccount> accounts;

 };


CBank::CBank(){
    // accounts = new AFP ;
}

bool CBank::addAccount(const CAccount account){
	this -> accounts.add (account);

	return true;
}

bool CBank::NewAccount(const char *accID, int initialBalance){
   
    
    CAccount temp = CAccount(accID, initialBalance);
    this->accounts.add(temp);
    return true;
}


bool CBank::Transaction (const char *debAccID, const char *credAccID, int amount, const char * signature){

	return true;
}

bool CBank::TrimAccount (const char *accID){

	return true;
}






 int main(){

    bool status;
    int  balance;
    char accCpy[100], debCpy[100], credCpy[100], signCpy[100];
    CBank a;
    status = a . NewAccount ( "123456", 1000 );
     // status = true
    status = a . NewAccount ( "987654", -500 );
     // status = true
    status = a . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
     // status = true
    status = a . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
     // status = true
    status = a . NewAccount ( "111111", 5000 );
     // status = true
    status = a . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" );
    printf("end\n");
     // status = true
//    balance = a . Account ( "123456" ). Balance ( );
//     // balance = -2190
//    balance = a . Account ( "987654" ). Balance ( );
//     // balance = 2980
//    balance = a . Account ( "111111" ). Balance ( );
//     // balance = 4710
//    cout << a . Account ( "123456" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    123456:
//       1000
//     - 300, to: 987654, sign: XAbG5uKz6E=
//     - 2890, to: 987654, sign: AbG5uKz6E=
//     = -2190
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << a . Account ( "987654" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    987654:
//       -500
//     + 300, from: 123456, sign: XAbG5uKz6E=
//     + 2890, from: 123456, sign: AbG5uKz6E=
//     + 290, from: 111111, sign: Okh6e+8rAiuT5=
//     = 2980
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << a . Account ( "111111" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    111111:
//       5000
//     - 290, to: 987654, sign: Okh6e+8rAiuT5=
//     = 4710
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    status = a . TrimAccount ( "987654" );
//     // status = true
//    status = a . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
//     // status = true
//    cout << a . Account ( "987654" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    987654:
//       2980
//     + 123, from: 111111, sign: asdf78wrnASDT3W
//     = 3103
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//
//    CBank c;
//    strncpy ( accCpy, "123456", sizeof ( accCpy ) );
//    status = c . NewAccount ( accCpy, 1000 );
//     // status = true
//    strncpy ( accCpy, "987654", sizeof ( accCpy ) );
//    status = c . NewAccount ( accCpy, -500 );
//     // status = true
//    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
//    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
//    strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
//    status = c . Transaction ( debCpy, credCpy, 300, signCpy );
//     // status = true
//    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
//    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
//    strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
//    status = c . Transaction ( debCpy, credCpy, 2890, signCpy );
//     // status = true
//    strncpy ( accCpy, "111111", sizeof ( accCpy ) );
//    status = c . NewAccount ( accCpy, 5000 );
//     // status = true
//    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
//    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
//    strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
//    status = c . Transaction ( debCpy, credCpy, 2890, signCpy );
//     // status = true
//    balance = c . Account ( "123456" ). Balance ( );
//     // balance = -2190
//    balance = c . Account ( "987654" ). Balance ( );
//     // balance = 5580
//    balance = c . Account ( "111111" ). Balance ( );
//     // balance = 2110
//    cout << c . Account ( "123456" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    123456:
//       1000
//     - 300, to: 987654, sign: XAbG5uKz6E=
//     - 2890, to: 987654, sign: AbG5uKz6E=
//     = -2190
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << c . Account ( "987654" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    987654:
//       -500
//     + 300, from: 123456, sign: XAbG5uKz6E=
//     + 2890, from: 123456, sign: AbG5uKz6E=
//     + 2890, from: 111111, sign: Okh6e+8rAiuT5=
//     = 5580
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << c . Account ( "111111" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    111111:
//       5000
//     - 2890, to: 987654, sign: Okh6e+8rAiuT5=
//     = 2110
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    status = c . TrimAccount ( "987654" );
//     // status = true
//    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
//    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
//    strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
//    status = c . Transaction ( debCpy, credCpy, 123, signCpy );
//     // status = true
//    cout << c . Account ( "987654" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    987654:
//       5580
//     + 123, from: 111111, sign: asdf78wrnASDT3W
//     = 5703
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//
//    CBank e;
//    status = e . NewAccount ( "123456", 1000 );
//     // status = true
//    status = e . NewAccount ( "987654", -500 );
//     // status = true
//    status = e . NewAccount ( "123456", 3000 );
//     // status = false
//    status = e . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" );
//     // status = false
//    status = e . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" );
//     // status = false
//    status = e . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" );
//     // status = false
//    balance = e . Account ( "666" ). Balance ( );
//     // exception thrown
//    cout << e . Account ( "666" );
//     // exception thrown
//    status = e . TrimAccount ( "666" );
//     // status = false
//
//    CBank g;
//    status = g . NewAccount ( "123456", 1000 );
//     // status = true
//    status = g . NewAccount ( "987654", -500 );
//     // status = true
//    status = g . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
//     // status = true
//    status = g . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
//     // status = true
//    status = g . NewAccount ( "111111", 5000 );
//     // status = true
//    status = g . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
//     // status = true
//    CBank h ( g );
//    status = g . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
//     // status = true
//    status = h . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
//     // status = true
//    status = g . NewAccount ( "99999999", 7000 );
//     // status = true
//    status = g . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
//     // status = true
//    status = g . TrimAccount ( "111111" );
//     // status = true
//    status = g . Transaction ( "123456", "111111", 221, "Q23wr234ER==" );
//     // status = true
//    cout << g . Account ( "111111" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    111111:
//       -1802
//     + 221, from: 123456, sign: Q23wr234ER==
//     = -1581
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << g . Account ( "99999999" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    99999999:
//       7000
//     + 3789, from: 111111, sign: aher5asdVsAD
//     = 10789
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << g . Account ( "987654" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    987654:
//       -500
//     + 300, from: 123456, sign: XAbG5uKz6E=
//     + 2890, from: 123456, sign: AbG5uKz6E=
//     + 2890, from: 111111, sign: Okh6e+8rAiuT5=
//     + 123, from: 111111, sign: asdf78wrnASDT3W
//     = 5703
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << h . Account ( "111111" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    111111:
//       5000
//     - 2890, to: 987654, sign: Okh6e+8rAiuT5=
//     - 789, to: 987654, sign: SGDFTYE3sdfsd3W
//     = 1321
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << h . Account ( "99999999" );
//     // exception thrown
//    cout << h . Account ( "987654" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    987654:
//       -500
//     + 300, from: 123456, sign: XAbG5uKz6E=
//     + 2890, from: 123456, sign: AbG5uKz6E=
//     + 2890, from: 111111, sign: Okh6e+8rAiuT5=
//     + 789, from: 111111, sign: SGDFTYE3sdfsd3W
//     = 6369
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//
//    CBank i;
//    CBank j;
//    status = i . NewAccount ( "123456", 1000 );
//     // status = true
//    status = i . NewAccount ( "987654", -500 );
//     // status = true
//    status = i . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
//     // status = true
//    status = i . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
//     // status = true
//    status = i . NewAccount ( "111111", 5000 );
//     // status = true
//    status = i . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
//     // status = true
//    j = i;
//    status = i . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
//     // status = true
//    status = j . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
//     // status = true
//    status = i . NewAccount ( "99999999", 7000 );
//     // status = true
//    status = i . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
//     // status = true
//    status = i . TrimAccount ( "111111" );
//     // status = true
//    cout << i . Account ( "111111" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    111111:
//       -1802
//     = -1802
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */
//    cout << j . Account ( "111111" );
//    /*
//    ---8<---8<---8<---8<---8<---8<---8<---
//    111111:
//       5000
//     - 2890, to: 987654, sign: Okh6e+8rAiuT5=
//     - 789, to: 987654, sign: SGDFTYE3sdfsd3W
//     = 1321
//    ---8<---8<---8<---8<---8<---8<---8<---
//    */


     return 0;
 }
















