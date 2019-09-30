#include "stdafx.h"
#include <regex>
#include "StringUtil.h"


CStringUtil::CStringUtil()
{
}


CStringUtil::~CStringUtil()
{
}

std::vector<std::wstring> CStringUtil::ws_split(const std::wstring& in, const wstring& delim)
{
	std::wregex re{ delim };
	return std::vector<std::wstring> {
		std::wsregex_token_iterator(in.begin(), in.end(), re, -1),
			std::wsregex_token_iterator()
	};
}

std::wstring CLanguageUtil::GetLanguageByLCID(int LCID)
{
	WCHAR szISOLang[5] = { 0 };
	WCHAR szISOCountry[5] = { 0 };
	int iLen = 0;

	::GetLocaleInfo(LCID,
		LOCALE_SISO639LANGNAME,
		szISOLang,
		sizeof(szISOLang) / sizeof(WCHAR));

	::GetLocaleInfo(LCID,
		LOCALE_SISO3166CTRYNAME,
		szISOCountry,
		sizeof(szISOCountry) / sizeof(WCHAR));

	return wstring(szISOLang) + _T("-") + wstring(szISOCountry);
}
