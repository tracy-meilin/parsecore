#include "stdafx.h"
#include "OdfOfficeCore.h"
#include "NDOdfPowerPointDoc.h"
#include "NDOdfApplication.h"


CNDOdfApplication::CNDOdfApplication()
{
}


CNDOdfApplication::~CNDOdfApplication()
{
}

std::shared_ptr<CNDOdfPowerPointDoc> CNDOdfApplication::OpenDoc(const wstring& strDocPath)
{
	return nullptr;
}
