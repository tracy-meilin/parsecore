#include "stdafx.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "sdxmlimp_impl.h"
#include "xmlictxt.h"
#include "SdXMLBodyContext_Impl.h"
#include "SdXMLDocContext_Impl.h"


SdXMLDocContext_Impl::SdXMLDocContext_Impl(SvXMLImport& rImport, 
	sal_uInt16 nPrfx,
	const wstring& rLName,
	const AttributeList& rAttrList)
	: SvXMLImportContext(rImport, nPrfx, rLName)
{

}

SdXMLDocContext_Impl::~SdXMLDocContext_Impl()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLDocContext_Impl::CreateChildContext(sal_uInt16 nPrefix, 
	const wstring& rLocalName, 
	const AttributeList& rAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;

	const SvXMLTokenMap& rTokenMap = GetSdImport().GetDocElemTokenMap();
	switch (rTokenMap.Get(nPrefix, rLocalName))
	{
		case XML_TOK_DOC_BODY:
		{
			int n = static_cast<int>(GetImport().getImportFlags());
			if (GetImport().getImportFlags() & SvXMLImportFlags::CONTENT)
			{
				// office:body inside office:document
				spContext = make_shared<SdXMLBodyContext_Impl>(GetSdImport(), nPrefix,
					rLocalName, rAttributeList);
			}
			break;
		}
	}

	return nullptr;
}
