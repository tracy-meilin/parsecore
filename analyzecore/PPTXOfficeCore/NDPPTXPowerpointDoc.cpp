#include "stdafx.h"

#include "NDPPTXSlide.h"
#include "NDPPTXPowerpointDoc.h"


CNDPPTXPowerpointDoc::CNDPPTXPowerpointDoc()
{
}


CNDPPTXPowerpointDoc::~CNDPPTXPowerpointDoc()
{
}

bool CNDPPTXPowerpointDoc::OpenDoc(const wstring& strDocPath)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	m_spZipArchive = make_shared<ZipArchive>(converterX.to_bytes(strDocPath));
	if (m_spZipArchive)
	{
		return m_spZipArchive->open(ZipArchive::READ_ONLY);
	}

	return false;
}

std::vector<std::shared_ptr<CNDPPTXSlide>>& CNDPPTXPowerpointDoc::GetSlides()
{
	std::vector<std::shared_ptr<CNDPPTXSlide>> vec;

	return vec;
}
