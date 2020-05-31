#include "stdafx.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "fastparser.h"
#include "NDOdfPowerPointDoc.h"


CNDOdfPowerPointDoc::CNDOdfPowerPointDoc()
{
}


CNDOdfPowerPointDoc::~CNDOdfPowerPointDoc()
{
}

bool CNDOdfPowerPointDoc::OpenDoc(const wstring& strDocPath)
{
	shared_ptr<FastSaxParser> spFastSaxParser = make_shared<FastSaxParser>();
	if (spFastSaxParser == nullptr)
		return false;

	spFastSaxParser->parseFodp(strDocPath);

	return true;
}
