#pragma once

class SvXMLShapeContext;

class SdXMLShapeContext 
	: public SvXMLShapeContext
{
public:
	SdXMLShapeContext(SvXMLImport& rImport,
		const wstring& nPrfx,
		const wstring& rLName, 
		const shared_ptr<AttributeList>& rAttributeList,
		const shared_ptr<CNDOdfSlide>& rSpSlide);

	~SdXMLShapeContext();

	virtual void StartElement(const shared_ptr<AttributeList>& rAttributeList) override;

	virtual void EndElement() override;

	virtual void processAttribute(const wstring& nPrfx,
		const wstring& rLName,
		const wstring& rValue);

private:
	shared_ptr<CNDOdfSlide> mspSlide = nullptr;
	shared_ptr<AttributeList> mspAttributeList = nullptr;
};

// draw:frame
class SdXMLFrameShapeContext
	: public SdXMLShapeContext
{
public:
	SdXMLFrameShapeContext(SvXMLImport& rImport,
		const wstring& nPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttributeList,
		const shared_ptr<CNDOdfSlide>& rSpSlide);

	virtual ~SdXMLFrameShapeContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList);
};

