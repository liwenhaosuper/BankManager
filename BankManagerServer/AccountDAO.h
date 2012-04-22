
#ifndef _IACCOUNTDAO_
#define _IACCOUNTDAO_
#include "AccountEntity.h"
#include "XmlDb.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <vector>

class AccountDAO{
public:
	AccountDAO(string file):fileName(fileName){
		pDoc = db.Open(file);
	}
	~AccountDAO(){
		db.Close(pDoc);
		delete pDoc;
	}
	bool Add(AccountEntity entity);
	bool Delete(AccountEntity entity);
	bool Update(AccountEntity entity);
	AccountEntity* FindById(string id);
	AccountEntity* FindByName(string name);
	std::vector<AccountEntity> getAllAccounts();
private:
	bool Save();
	DOMDocument* pDoc;
	XMLDB db;
	string fileName;
};

#endif