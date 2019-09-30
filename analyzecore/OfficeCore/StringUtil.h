#pragma once
class CStringUtil
{
public:
	CStringUtil();
	~CStringUtil();

	static std::vector<std::wstring> ws_split(const std::wstring& in, const wstring& delim);
};

class CLanguageUtil
{
public:
	CLanguageUtil();
	~CLanguageUtil();

	static wstring GetLanguageByLCID(int LCID);
};