#pragma once


class ODFOfficeCore_API CNDOdfApplication
{
public:
	CNDOdfApplication();
	~CNDOdfApplication();

	shared_ptr<CNDOdfPowerPointDoc> OpenDoc(const wstring& strDocPath);
};

