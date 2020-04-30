#include "stdafx.h"
#include "attributelist.h"
#include "xmlictxt.h"
#include "xmlimp.h"


SvXMLImport::SvXMLImport()
{
}


SvXMLImport::~SvXMLImport()
{
}

std::shared_ptr<SvXMLImportContext> SvXMLImport::CreateContext(sal_uInt16 nPrefix, 
	const wstring& rLocalName, 
	const AttributeList& rAttrList)
{
	return make_shared<SvXMLImportContext>(*this, nPrefix, rLocalName);
}
