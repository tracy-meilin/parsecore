#include "stdafx.h"
#include <codecvt>
#include "Common.h"

namespace Common
{
	wstring Utf8ToUnicode(const string& strUtf8)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(strUtf8);
	}

	wstring Utf8ToUnicode(const char* pszUtf8)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(pszUtf8);
	}

	string UnicodeToUtf8(const wstring& strUnicode)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(strUnicode);
	}

	string UnicodeToUtf8(const wchar_t* pszUnicode)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(pszUnicode);
	}
}