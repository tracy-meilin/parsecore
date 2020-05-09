#pragma once


class CNDOdfApplication
{
public:
	CNDOdfApplication();
	~CNDOdfApplication();

	shared_ptr<CNDOdfPowerPointDoc> OpenDoc(const wstring& strDocPath);
};

