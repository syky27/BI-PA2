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
    ~CAccount();
private:
    const char *accID;
    
};

CAccount::CAccount()


class CBank
 {
   public:
    // default constructor
    // copy constructor
    // destructor
    // operator =

    bool NewAccount  (const char *accID, int initialBalance);
    bool Transaction (const char *debAccID, const char *credAccID, int amount, const char * signature);
    bool TrimAccount (const char *accID);
    // Account ( accID )
   private:
    // todo
 };