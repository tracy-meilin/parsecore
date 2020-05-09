#pragma once

class SvXMLImport;

class SvXMLImportContext
{
public:
	SvXMLImportContext(SvXMLImport& rImport, 
		const wstring& strPrefix,
		const wstring& rLName);
	virtual ~SvXMLImportContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName, 
		const shared_ptr<AttributeList>& rAttributeList);

	virtual void StartElement(const shared_ptr<AttributeList>& rAttributeList);

	virtual void EndElement();

	virtual void Characters();

protected:
	SvXMLImport& GetImport(){ return mrImport; }
	const SvXMLImport& GetImport() const{ return mrImport; }

private:
	SvXMLImport& mrImport;
};

