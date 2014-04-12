#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */



class MyString
{
private:
	char*	pData;	// pointer to C-style represenation of the MyString
	int		length;	// length of the MyString

public:
	/*
    Purpose: 		Default initializing constructor
    Parameters: 	N/A
	Main algorithm:	
		Sets the length to 0
		Creates a null-terminated character array of size 1
    Preconditions:
		N/A
    Postcondition:
		Creates empty MyString class
	*/
	MyString();

	/*
    Purpose: 		Creates a MyString which is a copy of cString
    Parameters: 	cString is a character array to be copied into the MyString
    Main algorithm: 
		Loop through cString, increment "length" until '\0' is hit
		Create character array of size length + 1
		Loop through cString, copy char from cString to corresponding array location
		End array with '\0'
    Preconditions:
		cString must be a character array, denoted by surrounding "quotations"
    Postcondition:
		Creates a MyString which contains data from cString
	*/
	MyString(const char* cString);	

	/*
    Purpose: 		Deallocates dynamically allocated memory made for MyString
    Parameters: 	N/A
    Main algorithm: 
		Delete character array
		Set pointer to NULL
		Set length to 0
    Preconditions:
		N/A -- Won't be called if class is never utilized.
    Postcondition:
		Memory freed back to the heap
	*/
	~MyString();

	/*
    Purpose: 		Overrided copy constructor
					Creates deep copy of original string
    Parameters: 	s is a MyString of any length
    Main algorithm: 
		(Using private copy function)
		Set length equal to original's length
		Create new character array of size length + 1
		Loop, copy original's character array to new character array
		Set last position to '\0'
    Preconditions:
		MyString must be a valid MyString
    Postcondition:
		New MyString is a deep copy of the original string
	*/
	MyString(const MyString& s);

	/*
    Purpose: 		Overrided default assignment operator
					Sets values of MyString from those in original MyString s
    Parameters: 	s is a MyString of any length
    Main algorithm: 
		(Using private copy function)
		Set length equal to original's length
		Create new character array of size length + 1
		Loop, copy original's character array to new character array
		Set last position to '\0'
    Preconditions:
		MyString must be a valid MyString
    Postcondition:
		New MyString is a deep copy of the original string
	*/
	MyString operator=(const MyString& s);

	/*
    Purpose: 		Assigns MyString to value set by the character array cString
    Parameters: 	cString is a character array to be copied into the MyString
    Main algorithm: 
		Create new MyString and initialize with the cString (using constructor)
		Return new MyString
    Preconditions:
		cString must be a character array, denoted by surrounding "quotations"
    Postcondition:
		Creates a MyString which contains data from cString
	*/
	MyString operator=(const char* cString);

	/*
    Purpose: 		Prints MyString to screen
    Parameters: 	N/A
    Main algorithm: 
		Loop through character array, print to screen
    Preconditions:
		MyString must be valid,  null-terminated and length recorded
    Postcondition:
		Prints MyString to screen
	*/
	void put();

	/*
    Purpose: 		Prints MyString to screen in reverse
    Parameters: 	N/A
    Main algorithm: 
		Loop through character array in reverse, print to screen
    Preconditions:
		MyString must be valid,  null-terminated and length recorded
    Postcondition:
		Prints MyString to screen
	*/
	void reverse();

	/*
    Purpose: 		Concatenation operator.  
					Adds another string to end of original MyString
    Parameters: 	s is a MyString of any length (referred to as additive)
    Main algorithm: 
		Creates a new MyString, cat
		Sets cat length to original length + additive MyString length
		Creates character array of new length + 1 for cat
		Copies original string to new character array
		Copies additive string to new character array
		Ends character array with '\0'
		Returns cat
    Preconditions:
		MyString must be valid, null-terminated and length recorded
    Postcondition:
		New MyString is result of string concatenation of original and additive
	*/
	MyString operator+(const MyString& s);

	/*
    Purpose: 		Concatenation operator
					Adds character array to end of original MyString
    Parameters: 	cString is a character array to be copied into the MyString
    Main algorithm: 
		Creates a temp MyString, initializes with cString
		Uses concatenation operator to add temp string with original string
		Puts concatenation to MyString cat
		Returns cat
    Preconditions:
		cString must be a character array, denoted by surrounding "quotations"
    Postcondition:
		New MyString is result of string concatenation of original and cString
	*/
	MyString operator+(const char* cString);

	/*
    Purpose: 		Creates a substring of MyString beginning at pos 
    Parameters: 	pos is an integer denoting position to begin substring
    Main algorithm: 
		Create temp MyString
		Set length to original string's length - pos
		Create character array of length + 1
		Copy elements beginning at pos to new array
		Set last element in character array to '\0'
		Return temp MyString
    Preconditions:
		pos must be less than the length
    Postcondition:
		Returned MyString will be a copy of original beginning from pos
		and be null-terminated
	*/
	MyString substr(const int pos);

	/*
    Purpose: 		Creates a substring of MyString beginning at pos and ending
					len characters later.
    Parameters: 	pos is an integer denoting position to begin
					len is an integer denoting how many characters to include
    Main algorithm: 
		Create temp MyString
		Set length to len
		Create character array of length + 1
		Copy elements to new array
		Set last element in array to '\0'
		Return temp MyString
    Preconditions:
		pos must be less than the length MyString
		pos + len must be less than or equal to the length of the original MyString
    Postcondition:
		Returned MyString will be a copy of original beginning from pos
		running for len characters, and be null-terminated
	*/
	MyString substr(const int pos, const int len);


	/*
    Purpose: 		Overloaded non-member insertion operator:
					allows MyString to be output in a given stream
    Parameters: 	os is the output stream to print to
					s is the MyString to be printed
    Main algorithm: 
		Loop, output character array to os.
    Preconditions:
		s must be a valid MyString, null-terminated and length recorded
    Postcondition:
		s will be output into the os stream
	*/
	friend ostream& operator<<(ostream& os, const MyString& s);

private:
	/*
    Purpose: 		Creates deep copy of original string
    Parameters: 	s is a MyString of any length
    Main algorithm: 
		Set length equal to original's length
		Create new character array of size length + 1
		Loop, copy original's character array to new character array
		Set last position to '\0'
    Preconditions:
		MyString s must be a valid MyString
    Postcondition:
		MyString is returned as a deep copy of MyString s
	*/
	void copy(const MyString& s);
};

MyString::MyString()
{
	length = 0;
	pData = NULL;
}

MyString::MyString(const char* cString)
{
	length = 0;
	while (cString[length] != '\0')
	{
		length++;
	}
	pData = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		pData[i] = cString[i];
	}
	pData[length] = '\0';
}

MyString::~MyString()
{
	delete [] pData;
	pData = NULL;
	length = 0;
}

MyString::MyString(const MyString& s)
{
	copy(s);
}

MyString MyString::operator=(const MyString& s)
{
	delete [] pData;
	copy(s);
	return *this;
}

MyString MyString::operator=(const char* cString)
{
	delete [] pData;
	MyString temp(cString);
	return temp;
}

void MyString::copy(const MyString& s)
{
	length = s.length;
	pData = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		pData[i] = s.pData[i];
	}
	pData[length] = '\0';
}

void MyString::put()
{
	for (int i = 0; i < length; i++)
	{
		cout << pData[i];
	}
}

void MyString::reverse()
{
	for (int i = length-1; i >= 0; i--)
	{
		cout << pData[i];
	}
}

MyString MyString::operator+(const MyString& s)
{
	MyString cat;
	cat.length = length + s.length;
	cat.pData = new char[cat.length + 1];
	for (int i = 0; i < length; i++)
	{
		cat.pData[i] = pData[i];
	}
	for (int i = 0; i < s.length; i++)
	{
		cat.pData[length + i] = s.pData[i];
	}
	cat.pData[cat.length] = '\0';
	return cat;
}

MyString MyString::operator+(const char* cString)
{
	MyString temp(cString);
	MyString cat;
	cat = operator+(temp);
	return cat;
}

MyString MyString::substr(const int pos)
{
	assert (pos < length);

	MyString temp;
	temp.length = length - pos;
	temp.pData = new char[temp.length + 1];
	for (int i = 0; i < temp.length; i++)
	{
		temp.pData[i] = pData[pos + i];
	}
	temp.pData[temp.length] = '\0';
	return temp;
}

MyString MyString::substr(const int pos, const int len)
{
	assert(pos < length);
	assert(pos + len <= length);

	MyString temp;
	temp.length = len;
	temp.pData = new char[temp.length + 1];
	for (int i = 0; i < temp.length; i++)
	{
		temp.pData[i] = pData[pos + i];
	}
	temp.pData[temp.length] = '\0';
	return temp;
}

ostream& operator<<(ostream& os, const MyString& s)
{
	for (int i = 0; i < s.length; i++)
	{
		os << s.pData[i];
	}
	return os;
}


class CAccount
{
public:
	CAccount();
	CAccount(const char *accID, int initialBalance);
	~CAccount();
	void pushToLog(int balanceChange);
	void resizeLog();
        const char getID();

	const char id;
	int balance;
	int ** log;
	
        unsigned int sizeOfLog;
	unsigned int realSizeOfLog;
};



CAccount::CAccount(const char * accID, int initialBalance){
	this = CAccount();
	id = accID;
	pushToLog(initialBalance);


}
CAccount::CAccount(){
	sizeOfLog = 20;
	realSizeOfLog = 0;
	log = new int *[sizeOfLog];

	for(unsigned i = 0; i < sizeOfLog; i++) {
		log[i] = NULL:
	}
}

void CAccount::resizeLog(){
	sizeOfLog *=2;
    int **temp = new int *[sizeOfLog]; 
    
    for (size_t i = 0; i < realSizeOfLog; i++) {
        temp[i] = log[i]; 
    }
    
    for (size_t i = realSizeOfLog; i < sizeOfLog; i++) {
        temp[i] = NULL;
    }
    delete[] log;
    log = temp;
    temp = NULL;
    
}

void CAccount::pushToLog(int balanceChange){
	if (this->realSizeOfLog == this->sizeOfLog){
		this->resizeLog();
	}

	log[this->sizeOfLog] = new int;
	log[sizeOfLog] = balanceChange;
	sizeOfLog++;
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
    int SearchAccount(const char &id, int &place);
    void resizeBankAccounts();
    // Account ( accID )
   private:
    CAccount ** bankAccounts;
    unsigned int sizeOfBankAccounts;
    unsigned int realSizeOfBankAccounts;

 };

CBank::CBank(){
	sizeOfBankAccounts = 20;
	realSizeOfBankAccounts = 0;
        bankAccounts = new CAccount *[sizeOfBankAccounts];

	for(unsigned i = 0; i < sizeOfBankAccounts; i++) {
		bankAccounts[i] = NULL:
	}
}

void CBank::resizeBankAccounts(){
	sizeOfBankAccounts *=2;
    CAccount **temp = new CAccount *[sizeOfBankAccounts]; 
    
    for (size_t i = 0; i < realSizeOfBankAccounts; i++) {
        temp[i] = bankAccounts[i]; 
    }
    
    for (size_t i = realSizeOfBankAccounts; i < sizeOfBankAccounts; i++) {
        temp[i] = NULL;
    }
    delete[] bankAccounts;
    bankAccounts = temp;
    temp = NULL;
    
}


int CBank::SearchAccount(const char &id, int &place){
    int left = 0, right = (int)realSizeOfBankAccounts - 1;
    int center = 0;
    place = 0;
    while (left <= right && realSizeOfBankAccounts) {
        center = (left + right) / 2;
        if (id < bankAccounts[center]->id)
            right = center - 1;
        else if (id > bankAccounts[center]->id)
            left = center + 1;
        else {
            place = center;
            return 1;
        }
    }
    place = left;
    return 0;
}


bool CBank::NewAccount(const char *accID, int initialBalance){
	if (SearchAccount(accID, accPlace)) {
	        return false;
	} else {
	        if (realSizeOfBankAccounts == sizeOfBankAccounts)
	            resizeBankAccounts;();
	        
	        
	        for (size_t i = realSizeOfBankAccounts; i > (size_t)place; i--)
	            accounts[i] = accounts[i - 1];
	        accounts[place] = NULL;
	        accounts[place] = CAccount(accID, initialBalance);
	        
	        realSizeOfBankAccounts++;
	        return true;
	    }   
    
    return true;
}














CBank::CBank(){
    this->sizeOfBankAccounts = 50;
    this->realSizeOfBankAccounts = 0;

    this->bankAccounts = new account *[counterSize];
    
    for (size_t i = 0; i < counterSize; i++) {
        this->accounts[i] = NULL;
    }
}

bool CBank::addAccount(const CAccount account){
	this -> accounts.add (account);

	return true;
}



bool CBank::Transaction (const char *debAccID, const char *credAccID, int amount, const char * signature){

	int debAccPalce = -27;
	int credAccPlace = -27;

	if (!SearchAccount(debAccID, debAccPalce) || !SearchAccount(credAccID, credAccPlace)){
		return false;
	}else{
		accounts[debAccPalce]->pushToLog(amount * -1);
		accounts[credAccPlace]->pushToLog(amount);
	}

	return true;
}

bool CBank::TrimAccount (const char *accID){
	int accPlace;
	if (!SearchAccount(accID, accPlace)){
		return false;
	}else{
		int initialBalance = accounts[accPlace]->log[0];
		delete accounts[accPlace];
		accounts[place] = new CAccount()
	}


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















