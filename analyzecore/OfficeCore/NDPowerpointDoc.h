#pragma once

class OfficeCore_API CNDPowerpointDoc
{
public:
	CNDPowerpointDoc();
	~CNDPowerpointDoc();

	bool OpenDoc(const wstring& strDocPath);

private:
	std::vector<shared_ptr<CNDSlide>> m_vecSlides;
};

