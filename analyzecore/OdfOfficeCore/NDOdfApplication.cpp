#include "stdafx.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "NDOdfPowerPointDoc.h"
#include "fastparser.h"
#include "NDOdfApplication.h"


CNDOdfApplication::CNDOdfApplication()
{
}


CNDOdfApplication::~CNDOdfApplication()
{
}

std::shared_ptr<CNDOdfPowerPointDoc> CNDOdfApplication::OpenDoc(const wstring& strDocPath)
{
	shared_ptr<FastSaxParser> spFastSaxParser = make_shared<FastSaxParser>();
	if (spFastSaxParser == nullptr)
		return nullptr;

	return spFastSaxParser->parseFodp(strDocPath);
}
