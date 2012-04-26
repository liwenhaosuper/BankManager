
#include <iostream>
#include "BankManager.h"
#include <omniORB4\stringtypes.h>
using namespace std;
//Account,_objref_Account,_impl_Account,Account_Helper,_pof_Account

BankManager::Account_ptr pAccount;

bool Login(){
	cout<<"Please type your account id:\n";
	char name[20];
	memset(name,0,sizeof(name));
	cin>>name;
	char pwd[20];
	memset(pwd,0,sizeof(pwd));
	cin>>pwd;
	char* tid = new char[10];
	tid ="10";
	_CORBA_String_inout* id = new _CORBA_String_inout(tid);
	
	char* tbal = new char[10];
	tbal = "0.0";
	_CORBA_String_inout* bal = new _CORBA_String_inout(tbal);

	if(pAccount->open(*id,pwd,*bal,name)){
		cout<<"Open Successfully"<<endl;
	}
	return true;
}
bool Register(){
	cout<<"Please type a new user name:\n";
	char name[20];
	memset(name,0,sizeof(name));
	cin>>name;
	char pwd[20];
	memset(pwd,0,sizeof(pwd));
	cin>>pwd;
	char* tid = new char[10];
	tid ="10";
	_CORBA_String_inout* id = new _CORBA_String_inout(tid);

	char* tbal = new char[10];
	tbal = "0.0";
	_CORBA_String_inout* bal = new _CORBA_String_inout(tbal);
	try{
		if(pAccount->open(*id,pwd,*bal,name)){
			cout<<"Open Successfully"<<endl;
		}
	}catch(CORBA::TRANSIENT& e){
		cerr<<"Exception:"<<e.NP_minorString()<<endl;
	}catch(...){
		cerr<<"Unhandle exception."<<endl;
	}
	return true;
}
void MainMenu(){
	while(true){
		cout<<"\t\t\tATM Menu\nPlease select one option:\n"
			<<"1.查看余额;\n"
			<<"2.取款;\n"
			<<"3.存款;\n"
			<<"4.转账;\n"
			<<"5.注销账户;\n"
			<<"6.退出;\n";
		int choice;
		cin>>choice;
		if(choice==1){

		}else if(choice==2){

		}else if(choice==3){

		}else if(choice==4){

		}else if(choice==5){

		}else if(choice==6){
			cout<<"Byte...\n";
			exit(1);
		}else{
			cout<<"\n\n";
		}
	}
	
}

int main(int argc, char** argv){
	try{
// 		argc = 2;
// 		argv = new char *[2];
// 		argv[0] = "Client";
// 		argv[1] = "IOR:010000001c00000049444c3a42616e6b4d616e616765722f4163636f756e743a312e30000100\
// 			00000000000064000000010102000e0000003131312e3138362e372e31303200dec50e000000feaa\
// 			9c984f00001208000000000000000200000000000000080000000100000000545441010000001c00\
// 			000001000000010001000100000001000105090101000100000009010100";
		if(argc<2){
			cout<<"Invalid param...Program will exit"<<endl;
			exit(1);
		}
		CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
		CORBA::Object_var obj = orb->string_to_object(argv[1]);
		cout<<"CheckPoint\n";
		BankManager::Account_var accountRef = BankManager::Account::_narrow(obj);
		if(CORBA::is_nil(accountRef)){
			cerr<<"Unable to connect to server";
			return 1;
		}
		pAccount = accountRef; 
		while(true){
			cout<<"Please select one option:"<<endl
				<<"1.Login Account;"<<endl
				<<"2.Create new Account;"<<endl;
			int choice = -1;
			cin>>choice;
			if(choice==1){
				if(Login()){
					MainMenu();
				}
			}else if(choice==2){
				Register();
			}else{
				cout<<endl;
				continue;
			}
		}
	} catch(CORBA::TRANSIENT&) {
		cerr << "Caught system exception TRANSIENT -- unable to contact the "
			<< "server." << endl;
	}catch(CORBA::SystemException& ex) {
		cerr << "Caught a CORBA::" << ex._name() << endl<<ex.NP_minorString();
	}catch(CORBA::Exception& ex) {
		cerr << "Caught CORBA::Exception: " << ex._name() << endl;
	}catch(omniORB::fatalException& fe) {
		cerr << "Caught omniORB::fatalException:" << endl;
		cerr << "  file: " << fe.file() << endl;
		cerr << "  line: " << fe.line() << endl;
		cerr << "  mesg: " << fe.errmsg() << endl;
	}catch(...){
		cerr<<"Exception occurs..."<<endl;
	}
	return 0;
}