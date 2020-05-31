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

protected:
	shared_ptr<CNDOdfSlide> mspSlide = nullptr;
	shared_ptr<AttributeList> mspAttributeList = nullptr;

	wstring			maDrawStyleName;
	wstring			maShapeId;
	wstring			maLayerName;
	wstring			maPresentationClass;
	
	awt::Size		maSize;
	awt::Point		maPosition;

	bool			mbHaveXmlId;
	bool			mbIsPlaceholder;
	bool			mbClearDefaultAttributs;
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

private:
	shared_ptr<SvXMLImportContext> mspImplContext = nullptr;
};


// draw:text-box
class SdXMLTextBoxShapeContext 
	: public SdXMLShapeContext
{
public:
	SdXMLTextBoxShapeContext(SvXMLImport& rImport,
		const wstring& nPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttributeList,
		const shared_ptr<CNDOdfSlide>& rSpSlide);
	virtual ~SdXMLTextBoxShapeContext ();

	virtual void StartElement(const shared_ptr<AttributeList>& rAttributeList) override;

	virtual void processAttribute(const wstring& nPrfx,
		const wstring& rLName,
		const wstring& rValue);

private:

};


