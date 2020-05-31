#pragma once


class SvXMLShapeContext
	: public SvXMLImportContext
{
public:
	SvXMLShapeContext(SvXMLImport& rImport,
		const wstring& nPrfx,
		const wstring& rLName);
};


class XMLShapeImportHelper 
	
{
public:
	XMLShapeImportHelper(SvXMLImport& rImporter);
	~XMLShapeImportHelper();

	shared_ptr<SvXMLShapeContext> CreateGroupChildContext(SvXMLImport& rImport, 
		const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList, 
		const shared_ptr<CNDOdfSlide>& rSpSlide);
};

