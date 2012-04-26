#ifndef _XMLDB_H__
#define _XMLDB_H__

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <string>
using namespace xercesc;
using namespace std;

class XMLDB{
private:
	XercesDOMParser* parser;
public:
	XMLDB(){};
	static bool isInit;
	DOMDocument* Open(string filename);
	bool Close(DOMDocument* doc);
	static bool Initialize();
	static bool Terminate();
};

#endif