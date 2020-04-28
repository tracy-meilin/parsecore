#pragma once

class PPTXOfficeCore_API CNDPPTXPowerpointDoc
{
public:
	CNDPPTXPowerpointDoc();
	~CNDPPTXPowerpointDoc();

	bool OpenDoc(const wstring& strDocPath);

	std::vector<shared_ptr<CNDPPTXSlide>>& GetSlides();

private:
	std::vector<shared_ptr<CNDPPTXSlide>> m_vecSlides;
	shared_ptr<ZipArchive> m_spZipArchive = nullptr;
};

