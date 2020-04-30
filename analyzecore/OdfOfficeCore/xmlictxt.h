#pragma once

class SvXMLImport;

class SvXMLImportContext
{
public:
	SvXMLImportContext(SvXMLImport& rImport, 
		sal_uInt16 nPrfx,
		const wstring& rLName);
	virtual ~SvXMLImportContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(sal_uInt16 nPrefix, 
		const wstring& rLocalName, 
		const AttributeList& rAttributeList);

	virtual void StartElement();

	virtual void EndElement();

	virtual void Characters();

protected:
	SvXMLImport& GetImport(){ return mrImport; }
	const SvXMLImport& GetImport() const{ return mrImport; }

private:
	SvXMLImport& mrImport;
};

