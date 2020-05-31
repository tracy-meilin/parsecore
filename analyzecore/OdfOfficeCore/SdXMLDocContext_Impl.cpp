#include "stdafx.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "sdxmlimp_impl.h"
#include "xmlictxt.h"
#include "xmlmetai.h"
#include "SdXMLBodyContext_Impl.h"
#include "SdXMLDocContext_Impl.h"


SdXMLDocContext_Impl::SdXMLDocContext_Impl(SvXMLImport& rImport, 
	const wstring& strPrfx,
	const wstring& rLName,
	const shared_ptr<AttributeList>& rAttributeList)
	: SvXMLImportContext(rImport, strPrfx, rLName)
{

}

SdXMLDocContext_Impl::~SdXMLDocContext_Impl()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLDocContext_Impl::CreateChildContext(const wstring& strPrefix,
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;

	if ((strPrefix == L"office")
		&& (rLocalName == L"body"))
	{
		spContext = make_shared<SdXMLBodyContext_Impl>(GetSdImport(), strPrefix, rLocalName, rAttributeList);
	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"meta"))
	{

	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"settings"))
	{

	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"scripts"))
	{

	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"font-face-decls"))
	{

	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"styles"))
	{

	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"automatic-styles"))
	{

	}
	else if ((strPrefix == L"office")
		&& (rLocalName == L"master-styles"))
	{

	}
	

	// call parent when no own context was created
	if (!spContext)
		spContext = SvXMLImportContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	//const SvXMLTokenMap& rTokenMap = GetSdImport().GetDocElemTokenMap();
	//switch (rTokenMap.Get(nPrefix, rLocalName))
	//{
	//	case XML_TOK_DOC_BODY:
	//	{
	//		int n = static_cast<int>(GetImport().getImportFlags());
	//		if (GetImport().getImportFlags() & SvXMLImportFlags::CONTENT)
	//		{
	//			// office:body inside office:document
	//			spContext = make_shared<SdXMLBodyContext_Impl>(GetSdImport(), nPrefix,
	//				rLocalName, rAttributeList);
	//		}
	//		break;
	//	}
	//}

	return spContext;
}

SdXMLFlatDocContext_Impl::SdXMLFlatDocContext_Impl(SvXMLImport& rImport, 
	const wstring& strPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttrList)
	: SvXMLImportContext(rImport, strPrfx, rLName)
	, SdXMLDocContext_Impl(rImport, strPrfx, rLName, rAttrList)
	, SvXMLMetaDocumentContext(rImport, strPrfx, rLName, rAttrList)
{

}

SdXMLFlatDocContext_Impl::~SdXMLFlatDocContext_Impl()
{

}

std::shared_ptr<SvXMLImportContext> SdXMLFlatDocContext_Impl::CreateChildContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	if ((strPrefix == L"office")
		&& (rLocalName == L"meta"))
	{
		return SvXMLMetaDocumentContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);
	}
	else
	{
		return SdXMLDocContext_Impl::CreateChildContext(strPrefix, rLocalName, rAttributeList);
	}
}
