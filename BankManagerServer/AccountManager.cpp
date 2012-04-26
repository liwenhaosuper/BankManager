
#pragma once

#include "AccountManager.h"
#include "AccountDAO.h"
#include "AccountEntity.h"

#include <iostream>

::CORBA::Boolean AccountImpl::open( char*& id, const char* password, char*& balance, const char* customerName )
{
	std::cout<<"AccountManager:Open"<<endl;
	AccountDAO* ADao = new AccountDAO("data.xml");
	AccountEntity entity;
	entity.Balance(atof(balance));
	entity.CustomerName(customerName);
	entity.Password(password);
	return ADao->Add(entity);
}

::CORBA::Boolean AccountImpl::close( const char* id )
{
	std::cout<<"AccountManager:Close"<<endl;
	AccountDAO* ADao = new AccountDAO("data.xml");
	AccountEntity* entity = ADao->FindById(id);
	if(entity==NULL){
		return false;
	}
	return ADao->Delete(*entity);
}

::CORBA::Boolean AccountImpl::deposite( const char* id, const char* value )
{
	std::cout<<"AccountManager:Deposite"<<endl;
	AccountDAO* ADao = new AccountDAO("data.xml");
	AccountEntity* entity = ADao->FindById(id);
	if(entity==NULL){
		return false;
	}
	entity->Balance(entity->Balance()+atof(value));
	return ADao->Update(*entity);
}

char* AccountImpl::getBalance( const char* id )
{
	std::cout<<"AccountManager:GetBalance"<<endl;
	AccountDAO* ADao = new AccountDAO("data.xml");
	AccountEntity* entity = ADao->FindById(id);
	if(entity==NULL){
		return "0";
	}
	char* res = new char[20];
	memset(res,0,sizeof(res));
	sprintf(res,"%f",(float)entity->Balance());
	return res;
}

::CORBA::Boolean AccountImpl::transfer( const char* from, const char* to, const char* value )
{
	std::cout<<"AccountManager:Transfer"<<endl;
	AccountDAO* ADao = new AccountDAO("data.xml");
	AccountEntity* fromEntity = ADao->FindById(from);
	if(fromEntity==NULL||fromEntity->Balance()<=0||atof(value)<=0){
		return false;
	}
	AccountEntity* toEntity = ADao->FindById(to);
	if(toEntity==NULL){
		return false;
	}
	fromEntity->Balance(fromEntity->Balance()-atof(value));
	toEntity->Balance(toEntity->Balance()+atof(value));
	if(ADao->Update(*fromEntity)){
		if(ADao->Update(*toEntity)){
			return true;
		}else{
			//rollback
			fromEntity->Balance(fromEntity->Balance()+atof(value));
			ADao->Update(*fromEntity);
			return false;
		}
	}
	return false;
}


::CORBA::Boolean AccountImpl::withdraw( const char* id, const char* value )
{
	std::cout<<"AccountManager:WithDraw"<<endl;
	return false;
}
