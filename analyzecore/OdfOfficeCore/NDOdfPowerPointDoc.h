#pragma once

class ODFOfficeCore_API CNDOdfPowerPointDoc
{
public:
	CNDOdfPowerPointDoc();
	~CNDOdfPowerPointDoc();

	bool OpenDoc(const wstring& strDocPath);
};

