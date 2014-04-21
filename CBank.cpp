#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <assert.h>
#include <limits.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#endif // __PROGTEST__

class BetterString {
private:
	char* data;
	int length;
public:
	BetterString();
	BetterString(const char* cString);
	~BetterString();
	BetterString(const BetterString& s);
	BetterString operator=(const BetterString& s);
	BetterString operator=(const char* cString);
	void put();
	friend ostream& operator<<(ostream& os, const BetterString& s);
private:
	void copy(const BetterString& s);
};

BetterString::BetterString() {
	length = 0;
	data = NULL;
}

BetterString::BetterString(const char* cString) {
	length = 0;
	while (cString[length] != '\0') {
		length++;
	}
	data = new char[length + 1];
	for (int i = 0; i < length; i++) {
		data[i] = cString[i];
	}
	data[length] = '\0';
}

BetterString::~BetterString() {
	if (data != NULL)
		delete[] data;
	data = NULL;
	length = 0;
}

BetterString::BetterString(const BetterString& s) {
	data = NULL;
	length = 0;
	copy(s);
}

BetterString BetterString::operator=(const BetterString& s) {
	delete[] data;
	copy(s);
	return *this;
}

BetterString BetterString::operator=(const char* cString) {
	delete[] data;
	BetterString temp(cString);
	return temp;
}

void BetterString::copy(const BetterString& s) {
	length = s.length;
	data = new char[length + 1];
	for (int i = 0; i < length; i++) {
		data[i] = s.data[i];
	}
	data[length] = '\0';
}

void BetterString::put() {
	for (int i = 0; i < length; i++) {
		cout << data[i];
	}
}

ostream& operator<<(ostream& os, const BetterString& s) {
	for (int i = 0; i < s.length; i++) {
		os << s.data[i];
	}
	return os;
}

struct transaction {
	int value;
	BetterString from;
	BetterString sign;

	transaction(int Xvalue, const char * Xfrom, const char * Xsign) {
		value = Xvalue;
		BetterString tmp(Xfrom);
		BetterString tmp2(Xsign);
		from = tmp;
		sign = tmp2;
	}

	transaction(int Xvalue, BetterString Xfrom, BetterString Xsign) {
		value = Xvalue;
		from = Xfrom;
		sign = Xsign;
	}

	transaction(transaction & trans) {
		this->value = trans.value;
		this->sign = trans.sign;
		this->from = trans.from;
	}

};

class CAccount {
public:
	CAccount();
	CAccount(CAccount & account);
	CAccount(const char *accID, int initialBalance);
	~CAccount();
	void pushToLog(int balanceChange, BetterString account,
			BetterString signature);
	void resizeLog();
	const char getID();
	int Balance();

	friend ostream& operator<<(ostream &out, const CAccount & account) {

		out << account.id << ":" << endl;
		if (account.transactions[0]->value < 0) {
			out << "" << account.transactions[0]->value << endl;
		} else {
			out << "" << account.transactions[0]->value << endl;
		}
		int finalBalance = account.transactions[0]->value;
		int actual;
		for (unsigned i = 1; i < account.realSizeOfLog; i++) {

			actual = account.transactions[i]->value;
			finalBalance += actual;
			if (actual < 0) {
				actual *= -1;
				out << "- " << actual << ", to: "
						<< account.transactions[i]->from << ", sign: "
						<< account.transactions[i]->sign << endl;
			} else {
				out << "+ " << actual << ", from: "
						<< account.transactions[i]->from << ", sign: "
						<< account.transactions[i]->sign << endl;
			}

		}
		out << "= " << finalBalance << endl;
		return out;
	}

	char * id;

	int balance;
	transaction ** transactions;

	unsigned int sizeOfLog;
	unsigned int realSizeOfLog;
};

CAccount::CAccount(CAccount & account) {
	id = NULL;
	size_t len = strlen(account.id);
	this->id = new char[len + 1];

	if (id) {
		strncpy(id, account.id, len);
		id[len] = '\0';
	}

	sizeOfLog = account.sizeOfLog;
	realSizeOfLog = account.realSizeOfLog;
	transactions = new transaction *[sizeOfLog];
	unsigned i(0);
	for (i = 0; i < realSizeOfLog; i++) {
		transactions[i] = new transaction(*account.transactions[i]);
	}
	for (; i < sizeOfLog; i++) {
		transactions[i] = NULL;
	}
}

CAccount::CAccount() {
	id = NULL;
	sizeOfLog = 20;
	realSizeOfLog = 0;

	transactions = new transaction *[sizeOfLog];

	for (unsigned i = 0; i < sizeOfLog; i++) {
		transactions[i] = NULL;
	}
}

CAccount::CAccount(const char * accID, int initialBalance) {
	id = NULL;
	size_t len = strlen(accID);
	this->id = new char[len + 1];
	strncpy(this->id, accID, len);
	this->id[len] = '\0';

	sizeOfLog = 20;
	realSizeOfLog = 0;
	transactions = new transaction *[sizeOfLog];
	for (unsigned i = 0; i < sizeOfLog; i++) {
		transactions[i] = NULL;
	}

	pushToLog(initialBalance, "x", "x");
}

CAccount::~CAccount() {
	if (id)
		delete[] id;
	for (unsigned i = 0; i < sizeOfLog; i++) {
		if (transactions[i]) {
			transaction *p(transactions[i]);
			delete p;
		}
	}
	delete[] transactions;
	id = NULL;
}

int CAccount::Balance() {
	int initialBalance = 0;
	for (unsigned i = 0; i < this->realSizeOfLog; i++) {
		initialBalance += this->transactions[i]->value;
	}

	return initialBalance;

}

void CAccount::resizeLog() {
	sizeOfLog *= 2;
	// int **temp = new int *[sizeOfLog];
	transaction **temp = new transaction *[sizeOfLog];

	for (size_t i = 0; i < realSizeOfLog; i++) {
		temp[i] = transactions[i];
	}

	for (size_t i = realSizeOfLog; i < sizeOfLog; i++) {
		temp[i] = NULL;
	}
	delete[] transactions;
	transactions = temp;
	temp = NULL;

}

void CAccount::pushToLog(int balanceChange, BetterString account,
		BetterString signature) {
	if (this->realSizeOfLog == this->sizeOfLog) {
		this->resizeLog();
	}

	transactions[this->realSizeOfLog] = new transaction(balanceChange, account,
			signature);

	realSizeOfLog++;
}

class CBank {
public:
	CBank();
	CBank(  CBank &bank);
	~CBank();
	bool NewAccount(const char *accID, int initialBalance);
	bool Transaction(const char *debAccID, const char *credAccID, int amount, const char * signature);
	bool TrimAccount(const char *accID);
	bool addAccount(CAccount * account);
	int SearchAccount(const char *id, int &place);
	void resizeBankAccounts();
	CAccount & Account(const char * account);
	CBank& operator=(const CBank & bank) {
		for (unsigned i = 0; i < this->sizeOfBankAccounts; i++)
			delete bankAccounts[i];
		delete[] bankAccounts;

		if (referencedBanks[0])
		{
			passTheCrown();

		}if (isReferenced)
		{
			bool flag = false;
			for (unsigned i = 0; i < origin->sizeOfRef; i++)
			{
				if (flag)
				{
					origin->referencedBanks[i-1] = origin->referencedBanks[i];
				}
				if (this == origin->referencedBanks[i])
				{
					origin->referencedBanks[i] = NULL;
					flag = true;
				}
		
			}

			if (!flag)
			{
				cout << "ERROR" << endl;
			}
		}



		realSizeOfBankAccounts = bank.realSizeOfBankAccounts;
		sizeOfBankAccounts = bank.sizeOfBankAccounts;
		bankAccounts = new CAccount *[sizeOfBankAccounts];
		unsigned i(0);
		for (i = 0; i < realSizeOfBankAccounts; i++)
			bankAccounts[i] = new CAccount(*bank.bankAccounts[i]);
		for (; i < sizeOfBankAccounts; i++)
			bankAccounts[i] = NULL;
		return *this;
	}

	void createDeepCopy();
	void allocateReferencedBanks();
	void resizeReferencedBanks();
	void pushToReferencedBanks(CBank * bankToPush);
	void changeOriginTo(CBank * newOrigin);
	void passTheCrown(void);

private:
	CAccount ** bankAccounts;
	unsigned int sizeOfBankAccounts;
	unsigned int realSizeOfBankAccounts;
	bool isReferenced;
	CBank * origin;
	CBank ** referencedBanks;
	unsigned int sizeOfRef;
	unsigned int realSizeOfRef;
};

CBank::CBank()
{
	isReferenced = false;
	sizeOfRef = sizeOfBankAccounts = 20;
	realSizeOfBankAccounts = 0;
	bankAccounts = new CAccount *[sizeOfBankAccounts];
	referencedBanks = new CBank *[sizeOfRef];
	for (unsigned i = 0; i < sizeOfBankAccounts; i++)
	{
		bankAccounts[i] = NULL;
	}
	for (unsigned i = 0; i < sizeOfRef; i++)
	{
		referencedBanks[i] = NULL;
	}
}

CBank::CBank(  CBank & bank) 
{
	isReferenced = true;
	origin =  &bank;
	bank.allocateReferencedBanks();
	bank.pushToReferencedBanks(this);

	sizeOfRef = 20;
	referencedBanks = new CBank *[sizeOfRef];
	for (unsigned i = 0; i < sizeOfRef; i++)
	{
		referencedBanks[i] = NULL;
	}
}

CBank::~CBank()
{

	if (referencedBanks[0])
	{
		passTheCrown();
	}


	/*if (referencedBanks[0])
	{
		referencedBanks[0]->createDeepCopy();

		for(unsigned i = 0; i < realSizeOfRef; i++ ){
			referencedBanks[i]->changeOriginTo(referencedBanks[0]);
		}
		for (unsigned i = 0;  i < sizeOfRef; i++) {
			referencedBanks[i] = NULL;
		}

	}
	*/
	
	if (isReferenced) {
		bankAccounts = NULL;
		origin = NULL;
	}else{
		for (unsigned i = 0; i < realSizeOfBankAccounts; i++) {
			if (bankAccounts[i])
				delete bankAccounts[i];
		}

		delete[] bankAccounts;
		//if (referencedBanks)
		//{
		//	for (unsigned i = 0; i < realSizeOfRef; i++) {
		//	if (referencedBanks[i])
		//		delete referencedBanks[i];
		//}

		//delete[] referencedBanks;
		//}
		


	}

		





}



void CBank::allocateReferencedBanks()
{
	realSizeOfRef = 0;
	sizeOfRef = 20;
	if (referencedBanks) delete [] referencedBanks;
	referencedBanks = new CBank * [sizeOfRef];
		for (unsigned i = 0; i < sizeOfRef; i++) 
		{
			referencedBanks[i] = NULL;
		}

}

//Called when not copied bank has changed values;
void CBank::createDeepCopy()
{
	bool flag = false;
	for (unsigned i = 0; i < origin->sizeOfRef; i++)
	{
		if (flag)
		{
			origin->referencedBanks[i-1] = origin->referencedBanks[i];
		}
		if (this == origin->referencedBanks[i])
		{
			origin->referencedBanks[i] = NULL;
			flag = true;
		}
		
	}

	if (!flag)
	{
		cout << "ERROR" << endl;
	}

	realSizeOfBankAccounts = origin->realSizeOfBankAccounts;
	sizeOfBankAccounts = origin->sizeOfBankAccounts;
	bankAccounts = new CAccount *[sizeOfBankAccounts];
	unsigned i(0);
	for (i = 0; i < realSizeOfBankAccounts; i++)
	{
		bankAccounts[i] = new CAccount(*origin->bankAccounts[i]);
	}
	for (; i < sizeOfBankAccounts; i++) 
	{
		bankAccounts[i] = NULL;
	}

	origin = NULL;
	isReferenced = false;

}

void CBank::changeOriginTo(CBank * newOrigin){
	origin = newOrigin;
	newOrigin->pushToReferencedBanks(this);
}


void CBank::resizeReferencedBanks(){
	sizeOfRef *= 2;
	CBank **temp = new CBank *[sizeOfRef];

	for (size_t i = 0; i < realSizeOfRef; i++) {
		temp[i] = referencedBanks[i];
	}

	for (size_t i = realSizeOfRef; i < sizeOfRef; i++) {
		temp[i] = NULL;
	}
	delete[] referencedBanks;
	referencedBanks = temp;
	temp = NULL;
}

void CBank::pushToReferencedBanks(CBank *bankToPush)
{
	if(realSizeOfRef == sizeOfRef) resizeReferencedBanks();

	referencedBanks[realSizeOfRef] = bankToPush;
	realSizeOfRef++;
}



CAccount & CBank::Account(const char *account) {
	int place;
	if (!SearchAccount(account, place)) {
		cout << "SHIT ! " << endl;
		throw exception();

	}

	return *bankAccounts[place];

}



void CBank::resizeBankAccounts() {
	sizeOfBankAccounts *= 2;
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

int CBank::SearchAccount(const char *id, int &place) {
	int left = 0, right = (int) realSizeOfBankAccounts - 1;
	int center = 0;
	place = 0;
	while (left <= right && realSizeOfBankAccounts) {
		center = (left + right) / 2;
		if (strcmp(id,
				bankAccounts[center]->id) < 0)
			right = center - 1;
		else if (strcmp(id,
				bankAccounts[center]->id) > 0)
			left = center + 1;
		else {
			place = center;
			return 1;
		}
	}
	place = left;
	//    cout << "DEBUG PLACE: " << place << endl;
	return 0;
}


void CBank::passTheCrown(){
// kdyz meninim banku na ktere ostatni zavisi
	//predavam vsechny reference na tu dalsi banku co je v poradi
	referencedBanks[0]->createDeepCopy();

	for (unsigned i = 1; i < sizeOfRef; i++)
	{//pokud neni null
		if (referencedBanks[i])
		{//prekopiruju pole, nastavim novej origin u zkopirovanyho a dam na NULL;
			referencedBanks[0]->pushToReferencedBanks(referencedBanks[i]);
			referencedBanks[i]->origin = referencedBanks[0];
			referencedBanks[i] = NULL;
		}
	}

	referencedBanks[0] = NULL;

	// delete [] referencedBanks;

}


bool CBank::NewAccount(const char *accID, int initialBalance) {
	if (isReferenced)
	{
		createDeepCopy();
	}
	else if (referencedBanks[0])
	{
		passTheCrown();
	}


	int accPlace;
	if (SearchAccount(accID, accPlace)) {

		if (strcmp(accID, bankAccounts[accPlace]->id) == 0) {
			return false;
		}

	} 
	if (realSizeOfBankAccounts == sizeOfBankAccounts)
		resizeBankAccounts();

	for (size_t i = realSizeOfBankAccounts; i > (size_t) accPlace; i--)
		bankAccounts[i] = bankAccounts[i - 1];
	bankAccounts[accPlace] = NULL;
	bankAccounts[accPlace] = new CAccount(accID, initialBalance);
	realSizeOfBankAccounts++;
	return true;

}

bool CBank::Transaction(const char *debAccID, const char *credAccID, int amount,const char * signature) {
	//Zkopiruju pokud nevlastni hodny tak ji zkopiruju a odmazu ji
	if (isReferenced) 
	{
		createDeepCopy();
	}else if (referencedBanks[0])
	{
		passTheCrown();
	}


	if (strcmp(debAccID, credAccID) == 0) {
		//cout << "Transaction on one account" << endl;
		return false;
	}

	int debAccPalce = -27;
	int credAccPlace = -27;

	if (!SearchAccount(debAccID, debAccPalce)
			|| !SearchAccount(credAccID, credAccPlace)) {
		return false;
	} else {

		BetterString crediAcc(credAccID);
		BetterString debitAcc(debAccID);
		BetterString sign(signature);

		bankAccounts[debAccPalce]->pushToLog(amount * -1, crediAcc, sign);
		bankAccounts[credAccPlace]->pushToLog(amount, debAccID, sign);
	}

	return true;
}

bool CBank::TrimAccount(const char *accID) {
	if (isReferenced) 
	{
		createDeepCopy();
	}else if (referencedBanks[0])
	{
		passTheCrown();
	}


	int accPlace;
	if (!SearchAccount(accID, accPlace)) {
		return false;
	} else {

		int initialBalance = 0;
		for (unsigned i = 0; i < bankAccounts[accPlace]->realSizeOfLog; i++) {
			initialBalance += bankAccounts[accPlace]->transactions[i]->value;
		}

		char * my_id;
		size_t len = strlen(bankAccounts[accPlace]->id);
		my_id = new char[len + 1];
		strncpy(my_id, bankAccounts[accPlace]->id, len);
		my_id[len] = '\0';

		// char * id = bankAccounts[accPlace]->id;

		delete bankAccounts[accPlace];
		bankAccounts[accPlace] = new CAccount(my_id, initialBalance);

		delete[] my_id;

	}

	return true;
}

#ifndef __PROGTEST__

int main() {



	/*CBank a;
	a.NewAccount("123456", 1000);
	a.NewAccount("987654", -500);
	a.Transaction("123456", "987654", 300, "XAbG5uKz6E=");
	a.Transaction("123456", "987654", 2890, "AbG5uKz6E=");
	a.NewAccount("111111", 5000);
	a.Transaction("111111", "987654", 290, "Okh6e+8rAiuT5=");

	CBank b(a);


	b.Transaction("123456", "987654", 6666, "sykyRocks");




	cout << b.Account("123456") << endl;*/




		bool status;
	int balance;
	char accCpy[100], debCpy[100], credCpy[100], signCpy[100];

	CBank a;
	status = a.NewAccount("123456", 1000);
	// status = true
	assert(status == true);
	status = a.NewAccount("987654", -500);
	// status = true
	assert(status == true);
	status = a.Transaction("123456", "987654", 300, "XAbG5uKz6E=");
	// status = true
	assert(status == true);
	status = a.Transaction("123456", "987654", 2890, "AbG5uKz6E=");
	// status = true
	assert(status == true);
	status = a.NewAccount("111111", 5000);
	// status = true
	assert(status == true);
	status = a.Transaction("111111", "987654", 290, "Okh6e+8rAiuT5=");
	// status = true
	assert(status == true);
	balance = a.Account("123456").Balance();
	// balance = -2190
	assert(balance == -2190);
	balance = a.Account("987654").Balance();
	// balance = 2980
	assert(balance == 2980);
	balance = a.Account("111111").Balance();
	// balance = 4710
	assert(balance == 4710);
	cout << a.Account("123456");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 123456:
	 1000
	 - 300, to: 987654, sign: XAbG5uKz6E=
	 - 2890, to: 987654, sign: AbG5uKz6E=
	 = -2190
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << a.Account("987654");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 987654:
	 -500
	 + 300, from: 123456, sign: XAbG5uKz6E=
	 + 2890, from: 123456, sign: AbG5uKz6E=
	 + 290, from: 111111, sign: Okh6e+8rAiuT5=
	 = 2980
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << a.Account("111111");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 111111:
	 5000
	 - 290, to: 987654, sign: Okh6e+8rAiuT5=
	 = 4710
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	status = a.TrimAccount("987654");
	// status = true
	assert(status == true);
	status = a.Transaction("111111", "987654", 123, "asdf78wrnASDT3W");
	// status = true
	assert(status == true);
	cout << a.Account("987654");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 987654:
	 2980
	 + 123, from: 111111, sign: asdf78wrnASDT3W
	 = 3103
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */

	CBank c;
	strncpy(accCpy, "123456", sizeof(accCpy));
	status = c.NewAccount(accCpy, 1000);
	// status = true
	assert(status == true);
	strncpy(accCpy, "987654", sizeof(accCpy));
	status = c.NewAccount(accCpy, -500);
	// status = true
	assert(status == true);
	strncpy(debCpy, "123456", sizeof(debCpy));
	strncpy(credCpy, "987654", sizeof(credCpy));
	strncpy(signCpy, "XAbG5uKz6E=", sizeof(signCpy));
	status = c.Transaction(debCpy, credCpy, 300, signCpy);
	// status = true
	assert(status == true);
	strncpy(debCpy, "123456", sizeof(debCpy));
	strncpy(credCpy, "987654", sizeof(credCpy));
	strncpy(signCpy, "AbG5uKz6E=", sizeof(signCpy));
	status = c.Transaction(debCpy, credCpy, 2890, signCpy);
	// status = true
	assert(status == true);
	strncpy(accCpy, "111111", sizeof(accCpy));
	status = c.NewAccount(accCpy, 5000);
	// status = true
	assert(status == true);
	strncpy(debCpy, "111111", sizeof(debCpy));
	strncpy(credCpy, "987654", sizeof(credCpy));
	strncpy(signCpy, "Okh6e+8rAiuT5=", sizeof(signCpy));
	status = c.Transaction(debCpy, credCpy, 2890, signCpy);
	// status = true
	assert(status == true);
	balance = c.Account("123456").Balance();
	// balance = -2190
	assert(balance == -2190);
	balance = c.Account("987654").Balance();
	// balance = 5580
	assert(balance == 5580);
	balance = c.Account("111111").Balance();
	// balance = 2110
	assert(balance == 2110);
	cout << c.Account("123456");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 123456:
	 1000
	 - 300, to: 987654, sign: XAbG5uKz6E=
	 - 2890, to: 987654, sign: AbG5uKz6E=
	 = -2190
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << c.Account("987654");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 987654:
	 -500
	 + 300, from: 123456, sign: XAbG5uKz6E=
	 + 2890, from: 123456, sign: AbG5uKz6E=
	 + 2890, from: 111111, sign: Okh6e+8rAiuT5=
	 = 5580
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << c.Account("111111");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 111111:
	 5000
	 - 2890, to: 987654, sign: Okh6e+8rAiuT5=
	 = 2110
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	status = c.TrimAccount("987654");
	// status = true
	assert(status == true);
	strncpy(debCpy, "111111", sizeof(debCpy));
	strncpy(credCpy, "987654", sizeof(credCpy));
	strncpy(signCpy, "asdf78wrnASDT3W", sizeof(signCpy));
	status = c.Transaction(debCpy, credCpy, 123, signCpy);
	// status = true
	assert(status == true);
	cout << c.Account("987654");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 987654:
	 5580
	 + 123, from: 111111, sign: asdf78wrnASDT3W
	 = 5703
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	CBank e;
	status = e.NewAccount("123456", 1000);
	// status = true
	assert(status == true);
	status = e.NewAccount("987654", -500);
	// status = true
	assert(status == true);
	status = e.NewAccount("123456", 3000);
	// status = false
	assert(status == false);
	status = e.Transaction("123456", "666", 100, "123nr6dfqkwbv5");
	// status = false
	assert(status == false);
	status = e.Transaction("666", "123456", 100, "34dGD74JsdfKGH");
	// status = false
	assert(status == false);
	status = e.Transaction("123456", "123456", 100, "Juaw7Jasdkjb5");
	// status = false
	assert(status == false);

	//  balance = e . Account ( "666" ). Balance ( );
	// exception thrown

	//cout << e . Account ( "666" );
	// exception thrown

	status = e.TrimAccount("666");
	// status = false
	assert(status == false);

	CBank g;
	status = g.NewAccount("123456", 1000);
	// status = true
	assert(status == true);
	status = g.NewAccount("987654", -500);
	// status = true
	assert(status == true);
	status = g.Transaction("123456", "987654", 300, "XAbG5uKz6E=");
	// status = true
	assert(status == true);
	status = g.Transaction("123456", "987654", 2890, "AbG5uKz6E=");
	// status = true
	assert(status == true);
	status = g.NewAccount("111111", 5000);
	// status = true
	assert(status == true);
	status = g.Transaction("111111", "987654", 2890, "Okh6e+8rAiuT5=");
	// status = true
	assert(status == true);

	CBank h(g);

	status = g.Transaction("111111", "987654", 123, "asdf78wrnASDT3W");
	// status = true
	assert(status == true);
	status = h.Transaction("111111", "987654", 789, "SGDFTYE3sdfsd3W");
	// status = true
	assert(status == true);
	status = g.NewAccount("99999999", 7000);
	// status = true
	assert(status == true);
	status = g.Transaction("111111", "99999999", 3789, "aher5asdVsAD");
	// status = true
	assert(status == true);
	status = g.TrimAccount("111111");
	// status = true
	assert(status == true);
	status = g.Transaction("123456", "111111", 221, "Q23wr234ER==");
	// status = true
	assert(status == true);
	cout << g.Account("111111");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 111111:
	 -1802
	 + 221, from: 123456, sign: Q23wr234ER==
	 = -1581
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << g.Account("99999999");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 99999999:
	 7000
	 + 3789, from: 111111, sign: aher5asdVsAD
	 = 10789
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << g.Account("987654");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 987654:
	 -500
	 + 300, from: 123456, sign: XAbG5uKz6E=
	 + 2890, from: 123456, sign: AbG5uKz6E=
	 + 2890, from: 111111, sign: Okh6e+8rAiuT5=
	 + 123, from: 111111, sign: asdf78wrnASDT3W
	 = 5703
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << h.Account("111111");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 111111:
	 5000
	 - 2890, to: 987654, sign: Okh6e+8rAiuT5=
	 - 789, to: 987654, sign: SGDFTYE3sdfsd3W
	 = 1321
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
//    cout << h . Account ( "99999999" );
	// exception thrown
	cout << h.Account("987654");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 987654:
	 -500
	 + 300, from: 123456, sign: XAbG5uKz6E=
	 + 2890, from: 123456, sign: AbG5uKz6E=
	 + 2890, from: 111111, sign: Okh6e+8rAiuT5=
	 + 789, from: 111111, sign: SGDFTYE3sdfsd3W
	 = 6369
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */

	CBank i;
	CBank j;
	status = i.NewAccount("123456", 1000);
	// status = true
	assert(status == true);
	status = i.NewAccount("987654", -500);
	// status = true
	assert(status == true);
	status = i.Transaction("123456", "987654", 300, "XAbG5uKz6E=");
	// status = true
	assert(status == true);
	status = i.Transaction("123456", "987654", 2890, "AbG5uKz6E=");
	// status = true
	assert(status == true);
	status = i.NewAccount("111111", 5000);
	// status = true
	assert(status == true);
	status = i.Transaction("111111", "987654", 2890, "Okh6e+8rAiuT5=");
	// status = true
	assert(status == true);

	j = i;
	status = i.Transaction("111111", "987654", 123, "asdf78wrnASDT3W");
	// status = true
	assert(status == true);
	status = j.Transaction("111111", "987654", 789, "SGDFTYE3sdfsd3W");
	// status = true
	assert(status == true);
	status = i.NewAccount("99999999", 7000);
	// status = true
	assert(status == true);
	status = i.Transaction("111111", "99999999", 3789, "aher5asdVsAD");
	// status = true
	assert(status == true);
	status = i.TrimAccount("111111");
	// status = true
	assert(status == true);
	cout << i.Account("111111");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 111111:
	 -1802
	 = -1802
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */
	cout << j.Account("111111");
	/*
	 ---8<---8<---8<---8<---8<---8<---8<---
	 111111:
	 5000
	 - 2890, to: 987654, sign: Okh6e+8rAiuT5=
	 - 789, to: 987654, sign: SGDFTYE3sdfsd3W
	 = 1321
	 ---8<---8<---8<---8<---8<---8<---8<---
	 */

	//tester
	/*
	 CBank x;



	 vector<string> accounts;

	 for(int i = 0; i < 10000; i++){
	 string account_name = random_string(20);
	 int random_number;
	 accounts.push_back(account_name);

	 x.NewAccount(account_name.c_str(), random_number);
	 cout << i << " 1. " << endl;

	 }



	 int z;
	 for(unsigned long long  i = 0; i < 10000 - 1; i++){
	 z = rand()%10000;
	 string account_name = accounts.at(z);
	 z = rand()%10000;
	 string account_name2 = accounts.at(z);
	 string signature = random_string(16);

	 x.Transaction(account_name.c_str(), account_name2.c_str(), (int)z, signature.c_str());

	 cout << i << endl;

	 }

	 for(unsigned long long  i = 0; i < 10000 - 1; i++){
	 z = rand()%10000;
	 string account_name = accounts.at(z);



	 cout << x.Account(account_name.c_str()) << endl;

	 }






	 for(unsigned long long  i = 0; i < 10000 - 1; i++){
	 z = rand()%10000;
	 string account_name = accounts.at(z);
	 x.TrimAccount(account_name.c_str());
	 cout << "trimm" << endl;

	 }



	 */

	return 0;
}

#endif //__PROGTEST__

