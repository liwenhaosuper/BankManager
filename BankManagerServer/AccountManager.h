
#ifndef _ACCOUNTMANAGER_H
#define _ACCOUNTMANAGER_H

#include "BankManager.h"

class AccountManager{

};

//Account,_objref_Account,_impl_Account,Account_Helper,_pof_Account

class AccountImpl:public POA_BankManager::Account{
public:
	AccountImpl(){}
	virtual ~AccountImpl(){}
	virtual ::CORBA::Boolean open(char*& id, const char* password, char*& balance, const char* customerName);
	virtual ::CORBA::Boolean close(const char* id);
	virtual ::CORBA::Boolean deposite(const char* id, const char* value);
	virtual char* getBalance(const char* id);
	virtual ::CORBA::Boolean transfer(const char* from, const char* to, const char* value);
	virtual ::CORBA::Boolean withdraw(const char* id, const char* value);
};


#endif