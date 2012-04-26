
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <iostream>
#include "BankManager.h"
#include "AccountManager.h"
#include "XmlDb.h"
using namespace std;
using namespace xercesc;

int main(int argc,char* argv[]){
	try
	{
		XMLDB::Initialize();
		CORBA::ORB_var orb = CORBA::ORB_init(argc,argv);
		CORBA::Object_var obj= orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa=PortableServer::POA::_narrow(obj);
	    PortableServer::POAManager_var mgr = poa->the_POAManager();
		AccountImpl* account = new AccountImpl();
		PortableServer::ObjectId_var accountId = poa->activate_object(account);
		obj = account->_this();
		CORBA::String_var sior(orb->object_to_string(obj));
		cout << (char*)sior << endl;
		account->_remove_ref();
		
		mgr->activate();
		orb->run();
	}
	catch (const CORBA::Exception&)
	{
		cerr<<"exception"<<endl;
		return 1;
	}catch(...){
		cout<<"exception";
	}
	XMLDB::Terminate();
	return 0;
}
