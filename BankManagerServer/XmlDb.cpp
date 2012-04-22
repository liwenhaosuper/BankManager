
#pragma  once

#include "XmlDb.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <string>
#include <iostream>


bool XMLDB::isInit = false;

DOMDocument* XMLDB::Open( string filename )
{
	parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);   
	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);
	parser->parse(filename.c_str());
	return parser->getDocument();
}

bool XMLDB::Close( DOMDocument* doc )
{	
	DOMLSSerializer* theSerializer = doc->getImplementation()->createLSSerializer();
	DOMLSOutput* theOutput = doc->getImplementation()->createLSOutput();
	XMLFormatTarget *myFormTarget = new StdOutFormatTarget();
	theOutput->setByteStream(myFormTarget);
	theSerializer->write(doc,theOutput);
	theSerializer->release();
	theOutput->release();
	delete myFormTarget;
	return true;
}

bool XMLDB::Terminate()
{
	if(XMLDB::isInit){
		XMLPlatformUtils::Terminate();
	}
	return true;
}

bool XMLDB::Initialize()
{
	if(XMLDB::isInit==false)
	{
		XMLDB::isInit = true;
		try {
			XMLPlatformUtils::Initialize();
		}
		catch (const XMLException& e) {
			cerr<<"Failed to initialize XML Parser.";
			return false;
		}
	}
	return true;
}
