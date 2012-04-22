
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <iostream>
//#include "F:\projects\middleware\BankManager\BankManagerServer\XmlDb.h"
#include "BankManager.h"
#include "../BankManagerServer/XmlDb.h"
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
	}
	catch (const CORBA::Exception&)
	{
		cerr<<"exception"<<endl;
		return 1;
	}
	XMLDB::Terminate();
	return 0;
}