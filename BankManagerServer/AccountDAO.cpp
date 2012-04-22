/************************************************************************/
/* The XML File is stored as follows:
  <?xml version=1.0 encoding="utf-8"?>
   <accounts>
       <account id="1">
	       <customerName>hello</customerName>
		   <password>hello</password>
		   <balance>1000.0></balance>
	   </account>
	   <account id="2">
		   <customerName>hello1</customerName>
	       <password>hello1</password>
	       <balance>10001.0></balance>
	   </account>
   </accounts>                                                                   
																	 															 */
/************************************************************************/


#pragma  once
#include "AccountDAO.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
bool AccountDAO::Update( AccountEntity entity )
{
	DOMNodeList* pList = pDoc->getFirstChild()->getChildNodes();
	XMLCh tmp[129];
	for(int i=0;i<pList->getLength();i++){
		DOMNode* pNode = pList->item(i); //account
		char *attributeName = XMLString::transcode(pNode->getAttributes()->item(0)->getNodeName());
		if(strcmp(attributeName,"id")==0){
			if(strcmp(entity.Id().c_str(),XMLString::transcode(pNode->getAttributes()->item(0)->getNodeValue()))==0){
				DOMNodeList* pContentList = pNode->getChildNodes();
				for(int j=0;j<pContentList->getLength();j++){
					if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"customerName")==0){
						XMLString::transcode(entity.CustomerName().c_str(),tmp,128);
						pContentList->item(j)->setNodeValue(tmp);
					}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"password")==0){
						XMLString::transcode(entity.Password().c_str(),tmp,128);
						pContentList->item(j)->setNodeValue(tmp);
					}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"balance")==0){
						char bal[21];
						sprintf(bal,"%f",entity.Balance());
						XMLString::transcode(bal,tmp,128);
						pContentList->item(j)->setNodeValue(tmp);
					}
				}
				Save();
				return true;
			}
		}
	}
	return false;
}

bool AccountDAO::Save(){
	DOMLSSerializer* theSerializer = pDoc->getImplementation()->createLSSerializer();
	DOMLSOutput* theOutput = pDoc->getImplementation()->createLSOutput();
	XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(fileName.c_str());
	theOutput->setByteStream(myFormTarget);
	theSerializer->write(pDoc,theOutput);
	theSerializer->release();
	theOutput->release();
	delete myFormTarget;
	return true;
}

AccountEntity* AccountDAO::FindByName( string name )
{
	AccountEntity* entity = new AccountEntity();
	DOMNodeList* pList = pDoc->getFirstChild()->getChildNodes();
	for(int i=0;i<pList->getLength();i++){
		DOMNode* pNode = pList->item(i); //account
		char *attributeName = XMLString::transcode(pNode->getAttributes()->item(0)->getNodeName());
		if(strcmp(attributeName,"id")==0){
			entity->Id(XMLString::transcode(pNode->getAttributes()->item(0)->getNodeValue()));
			DOMNodeList* pContentList = pNode->getChildNodes();
			for(int j=0;j<pContentList->getLength();j++){
				if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"customerName")==0){
					entity->CustomerName(XMLString::transcode(pContentList->item(j)->getNodeValue()));
				}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"password")==0){
					entity->Password(XMLString::transcode(pContentList->item(j)->getNodeValue()));
				}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"balance")==0){
					entity->Balance(atof(XMLString::transcode(pContentList->item(j)->getNodeValue())));
				}
			}
			pNode->release();
			XMLString::release(&attributeName);
			if(strcmp(name.c_str(),entity->CustomerName().c_str())==0){
				return entity;
			}
		}
		pNode->release();
		XMLString::release(&attributeName);
	}
	return NULL;
}

bool AccountDAO::Add( AccountEntity entity )
{
	if(FindByName(entity.CustomerName())==NULL){
		return false;
	}
	DOMElement* pNewEle = pDoc->createElement(L"account");
	XMLCh tmp[129];
	XMLString::transcode(entity.Id().c_str(),tmp,128);
	pNewEle->setAttribute(L"id",tmp);

	DOMElement* pName = pDoc->createElement(L"customerName");
	XMLString::transcode(entity.CustomerName().c_str(),tmp,128);
	DOMText* pNameV = pDoc->createTextNode(tmp);
	pName->appendChild(pNameV);

	DOMElement* pPwd = pDoc->createElement(L"password");
	XMLString::transcode(entity.Password().c_str(),tmp,128);
	DOMText* pPwdV = pDoc->createTextNode(tmp);
	pName->appendChild(pPwdV);

	DOMElement* pBalance = pDoc->createElement(L"balance");
	char balance[20];
	sprintf(balance,"%f",entity.Balance());
	XMLString::transcode(balance,tmp,19);
	DOMText* pBalanceV= pDoc->createTextNode(tmp);
	pName->appendChild(pBalanceV);
	pDoc->getFirstChild()->appendChild(pNewEle);
	Save();
	return true;
}

AccountEntity* AccountDAO::FindById( string id )
{
	AccountEntity* entity = new AccountEntity();
	entity->Id(id);
	DOMNodeList* pList = pDoc->getFirstChild()->getChildNodes();
	for(int i=0;i<pList->getLength();i++){
		DOMNode* pNode = pList->item(i); //account
		char *attributeName = XMLString::transcode(pNode->getAttributes()->item(0)->getNodeName());
		if(strcmp(attributeName,"id")==0){
			if(strcmp(id.c_str(),XMLString::transcode(pNode->getAttributes()->item(0)->getNodeValue()))==0){
				DOMNodeList* pContentList = pNode->getChildNodes();
				for(int j=0;j<pContentList->getLength();j++){
					if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"customerName")==0){
						entity->CustomerName(XMLString::transcode(pContentList->item(j)->getNodeValue()));
					}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"password")==0){
						entity->Password(XMLString::transcode(pContentList->item(j)->getNodeValue()));
					}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"balance")==0){
						entity->Balance(atof(XMLString::transcode(pContentList->item(j)->getNodeValue())));
					}
				}
				pNode->release();
				XMLString::release(&attributeName);
				return entity;
			}
		}
		pNode->release();
		XMLString::release(&attributeName);
	}
	return NULL;
}

bool AccountDAO::Delete( AccountEntity entity )
{
	DOMNodeList* pList = pDoc->getFirstChild()->getChildNodes();
	for(int i=0;i<pList->getLength();i++){
		DOMNode* pNode = pList->item(i); //account
		char *attributeName = XMLString::transcode(pNode->getAttributes()->item(0)->getNodeName());
		if(strcmp(attributeName,"id")==0){
			if(strcmp(entity.Id().c_str(),XMLString::transcode(pNode->getAttributes()->item(0)->getNodeValue()))==0){
				pNode->getParentNode()->removeChild(pNode);
				Save();
				return true;
			}
		}
	}
	return false;
}
std::vector<AccountEntity> AccountDAO::getAllAccounts(){
	std::vector<AccountEntity> result;
	DOMNodeList* pList = pDoc->getFirstChild()->getChildNodes();
	for(int i=0;i<pList->getLength();i++){
		DOMNode* pNode = pList->item(i); //account
		char *attributeName = XMLString::transcode(pNode->getAttributes()->item(0)->getNodeName());
		if(strcmp(attributeName,"id")==0){
			AccountEntity entity;
			entity.Id(XMLString::transcode(pNode->getAttributes()->item(0)->getNodeValue()));
			DOMNodeList* pContentList = pNode->getChildNodes();
			for(int j=0;j<pContentList->getLength();j++){
				if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"customerName")==0){
					entity.CustomerName(XMLString::transcode(pContentList->item(j)->getNodeValue()));
				}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"password")==0){
					entity.Password(XMLString::transcode(pContentList->item(j)->getNodeValue()));
				}else if(strcmp(XMLString::transcode(pContentList->item(j)->getNodeName()),"balance")==0){
					entity.Balance(atof(XMLString::transcode(pContentList->item(j)->getNodeValue())));
				}
			}
			result.push_back(entity);
			//Should I delete pContentList?
		}
		pNode->release();
		XMLString::release(&attributeName);
	}
	return result;
}