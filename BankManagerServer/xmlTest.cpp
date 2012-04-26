
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <iostream>
#include "BankManager.h"
#include "AccountManager.h"
#include "XmlDb.h"
using namespace std;
using namespace xercesc;

int main(){
	XMLDB::Initialize();
	XMLDB::Terminate();
	return 0;
}