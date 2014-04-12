#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

class CAccount
{
public:
	CAccount();
	CAccount(const char *accID, int initialBalance);
	~CAccount();
	void pushToLog(int balanceChange);
	void resizeLog();
private:
	const char id;
	int balance;
	int ** log;
	usigned int sizeOfLog;
	usigned int realSizeOfLog;
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

void pushToLog(int balanceChange){
	if (realSizeOfLog == sizeOfLog){
		this->resizeLog;
	}

	log[sizeOfLog] = new int;
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

    void resizeBankAccounts();
    // Account ( accID )
   private:
    account ** bankAccounts;
    unsigned int sizeOfBankAccounts;
    unsigned int realSizeOfBankAccounts;

 };

CBank::CBank(){
	sizeOfBankAccounts = 20;
	realSizeOfBankAccounts = 0;
	accounts = new CAccount *[sizeOfBankAccounts];

	for(unsigned i = 0; i < sizeOfBankAccounts; i++) {
		accounts[i] = NULL:
	}
}

void CBank::resizeBankAccounts(){
	sizeOfBankAccounts *=2;
    int **temp = new CAccount *[sizeOfBankAccounts]; 
    
    for (size_t i = 0; i < realSizeOfBankAccounts; i++) {
        temp[i] = accounts[i]; 
    }
    
    for (size_t i = realSizeOfBankAccounts; i < sizeOfBankAccounts; i++) {
        temp[i] = NULL;
    }
    delete[] accounts;
    accounts = temp;
    temp = NULL;
    
}


int CBank::SearchAccount(const char &id, int &place){
    int left = 0, right = (int)realSizeOfLog - 1;
    int center = 0;
    place = 0;
    while (left <= right && realSizeOfLog) {
        center = (left + right) / 2;
        if (id < accounts[center]->id)
            right = center - 1;
        else if (id > accounts[center]->id)
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







int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}