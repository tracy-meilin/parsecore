#include "stdafx.h"
#include "NDSlide.h"

#include "NDPowerpointDoc.h"

CNDPowerpointDoc::CNDPowerpointDoc()
{
}


CNDPowerpointDoc::~CNDPowerpointDoc()
{
}

bool CNDPowerpointDoc::OpenDoc(const wstring& strDocPath)
{
	shared_ptr<StructuredStorageReader> st = make_shared<StructuredStorageReader>(strDocPath);
	shared_ptr<PowerPointDocument> spPPT = make_shared<PowerPointDocument>(st);
	return true;
}
