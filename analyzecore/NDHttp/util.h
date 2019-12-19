#pragma once
#include "stdafx.h"

namespace NDHttp
{
	class CUtil
	{
	public:
		wstring		Utf82Str(const string& str);
		string		Str2Utf8(const wstring& str);
		wstring		Utf8ToUnicode(string utf);
		string		Utf8ToAnsi(string ansi);
		string		AnsiToUtf8(string ansi);
		string		UnicodeToUtf8(wstring unicode);

		DWORD		CalcCRC(char* ptr, DWORD Size);
		bool		DirectoryMake(const wstring& strDirectory);
		string		UrlEncode(string str);


		string		CalcFileMD5(wstring strFilePath);

	};
}

