#pragma once

class OfficeCore_API CNDPowerpointDoc
{
public:
	CNDPowerpointDoc();
	~CNDPowerpointDoc();

	bool OpenDoc(const wstring& strDocPath);

	std::vector<shared_ptr<CNDSlide>>& GetSlides();

private:
	std::vector<shared_ptr<CNDSlide>> m_vecSlides;
	shared_ptr<PowerPointDocument> m_spPowerPointDoc = nullptr;
};

