//AccountEntity.h
#ifndef _ACCOUNTENTITY_
#define _ACCOUNTENTITY_

#include <string>
using namespace std;

class AccountEntity{
private:
	string id;
	string customerName;
	string password;
	double balance;
public:
	AccountEntity(string ids,string name,string pwd,double num):id(ids),customerName(name),password(pwd),balance(num){};
	AccountEntity(){};
	std::string Id() const { return id; }
	void Id(std::string val) { id = val; }
	double Balance() const { return balance; }
	void Balance(double val) { balance = val; }
	std::string CustomerName() const { return customerName; }
	void CustomerName(std::string val) { customerName = val; }
	std::string Password() const { return password; }
	void Password(std::string val) { password = val; }



	

};

#endif