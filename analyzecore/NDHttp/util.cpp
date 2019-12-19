#include "stdafx.h"
#include "Util.h"
#include <openssl/md5.h>

namespace NDHttp
{
	wstring	CUtil::Utf82Str(const string& str)
	{
#ifdef _UNICODE	
		return Utf8ToUnicode(str);
#else
		return Utf8ToAnsi(str);
#endif
	}

	wstring CUtil::Utf8ToUnicode(string utf)
	{
		// utf8 --> unicode
		int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, utf.c_str(), utf.length(), NULL, 0);
		wchar_t* wszString = new wchar_t[wcsLen + 1];

		MultiByteToWideChar(CP_UTF8, NULL, utf.c_str(), utf.length(), wszString, wcsLen);
		wszString[wcsLen] = '\0';

		wstring str = wszString;
		delete wszString;

		return str;
	}

	string CUtil::Utf8ToAnsi(string utf)
	{
		// utf8 --> unicode
		int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, utf.c_str(), utf.length(), NULL, 0);
		wchar_t* wszString = new wchar_t[wcsLen + 1];

		MultiByteToWideChar(CP_UTF8, NULL, utf.c_str(), utf.length(), wszString, wcsLen);
		wszString[wcsLen] = '\0';

		// unicode --> ansi
		int ansiLen = WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
		char* szAnsi = new char[ansiLen + 1];

		WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
		szAnsi[ansiLen] = '\0';

		string str = szAnsi;
		delete szAnsi;
		delete wszString;

		return str;
	}

	string CUtil::Str2Utf8(const wstring& str)
	{
#ifdef _UNICODE	
		return UnicodeToUtf8(str);
#else
		return AnsiToUtf8(str);
#endif
	}

	string CUtil::AnsiToUtf8(string ansi)
	{
		// ansi --> unicode
		int wcsLen = MultiByteToWideChar(CP_ACP, NULL, ansi.c_str(), ansi.length(), NULL, 0);
		wchar_t* wszString = new wchar_t[wcsLen + 1];

		MultiByteToWideChar(CP_ACP, NULL, ansi.c_str(), ansi.length(), wszString, wcsLen);
		wszString[wcsLen] = '\0';

		// unicode --> utf8
		int utfLen = WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
		char* szString = new char[utfLen + 1];

		WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szString, utfLen, NULL, NULL);
		szString[utfLen] = '\0';

		string str = szString;
		delete szString;
		delete wszString;

		return str;
	}

	string CUtil::UnicodeToUtf8(wstring unicode)
	{
		int utfLen = WideCharToMultiByte(CP_UTF8, NULL, unicode.c_str(), wcslen(unicode.c_str()), NULL, 0, NULL, NULL);
		char* szString = new char[utfLen + 1];

		WideCharToMultiByte(CP_UTF8, NULL, unicode.c_str(), wcslen(unicode.c_str()), szString, utfLen, NULL, NULL);
		szString[utfLen] = '\0';

		string str = szString;
		delete szString;

		return str;
	}


	DWORD CUtil::CalcCRC(char* ptr, DWORD Size)
	{
		static DWORD crcTable[256];
		static bool bTableIniFlag = false;
		if (!bTableIniFlag)
		{
			DWORD crcTmp1;
			for (int i = 0; i<256; i++)
			{
				crcTmp1 = i;
				for (int j = 8; j>0; j--)
				{
					if (crcTmp1 & 1) crcTmp1 = (crcTmp1 >> 1) ^ 0xEDB88320L;
					else crcTmp1 >>= 1;
				}

				crcTable[i] = crcTmp1;
			}
			bTableIniFlag = true;
		}


		DWORD dwRet = 0;

		DWORD crcTmp2 = 0xFFFFFFFF;
		while (Size--)
		{
			crcTmp2 = ((crcTmp2 >> 8) & 0x00FFFFFF) ^ crcTable[(crcTmp2 ^ (*ptr)) & 0xFF];
			ptr++;
		}

		dwRet = (crcTmp2 ^ 0xFFFFFFFF);
		return dwRet;
	}

	bool CUtil::DirectoryMake(const wstring& strDirectory)
	{
		if (strDirectory.empty())
		{
			return false;
		}

		int nIndex = 0;
		int nRes = 0;
		wstring strDirectoryFull = strDirectory;

		int nPathLen = strDirectoryFull.length() + 1;
		TCHAR* pszPathCopy = new TCHAR[nPathLen];

		if (!pszPathCopy)
		{
			return false;
		}
		pszPathCopy[strDirectoryFull.length()] = 0;

		_tcsncpy(pszPathCopy, strDirectoryFull.c_str(), nPathLen - 1);

		if (pszPathCopy[0])
		{
			nIndex = 1;

			while (pszPathCopy[nIndex])
			{
				if (pszPathCopy[nIndex] == _T('/') || pszPathCopy[nIndex] == _T('\\'))
				{
					if (pszPathCopy[nIndex - 1] == _T(':'))
					{
						nIndex++;
						continue;
					}

					pszPathCopy[nIndex] = 0;

					nRes = _wmkdir(pszPathCopy);
					if (nRes < 0 && errno != 17)
					{
						delete[] pszPathCopy;
						return false;
					}

					pszPathCopy[nIndex] = _T('/');
				}
				nIndex++;
			}
		}

		delete[] pszPathCopy;
		return true;
	}

	void hexchar(unsigned char c, unsigned char &hex1, unsigned char &hex2)
	{
		hex1 = c / 16;
		hex2 = c % 16;
		hex1 += hex1 <= 9 ? '0' : 'a' - 10;
		hex2 += hex2 <= 9 ? '0' : 'a' - 10;
	}

	string CUtil::UrlEncode(string s)
	{
		const char *str = s.c_str();
		vector<char> v(s.size());
		v.clear();
		for (size_t i = 0, l = s.size(); i < l; i++)
		{
			char c = str[i];
			if ((c >= '0' && c <= '9') ||
				(c >= 'a' && c <= 'z') ||
				(c >= 'A' && c <= 'Z') ||
				c == '!' || c == '#' || c == '$' || c == '&' || c == '\'' ||
				c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '-' ||
				c == '.' || c == '/' || c == ':' || c == ';' || c == '=' || c == '?' ||
				c == '@' || c == '_' || c == '~')
			{
				v.push_back(c);
			}
			else
			{
				if (c == '%')
				{
					if (i <= s.size() - 2)
					{
						char c1 = str[i + 1];
						char c2 = str[i + 2];
						if (((c1 >= '0' && c1 <= '9') ||
							(c1 >= 'a' && c1 <= 'z') ||
							(c1 >= 'A' && c1 <= 'Z')) &&
							((c2 >= '0' && c2 <= '9') ||
							(c2 >= 'a' && c2 <= 'z') ||
							(c2 >= 'A' && c2 <= 'Z')))
						{
							i = i + 2;
							v.push_back(c);
							v.push_back(c1);
							v.push_back(c2);
							continue;
						}
					}
				}

				v.push_back('%');
				unsigned char d1, d2;
				hexchar(c, d1, d2);
				v.push_back(d1);
				v.push_back(d2);
			}
		}

		return string(v.begin(), v.end());
	}

	#define BlockSize	1024*1024*10		//10M
	string CUtil::CalcFileMD5(wstring strFilePath)
	{
		FILE* fp = NULL;

		errno_t err = _tfopen_s(&fp, strFilePath.c_str(), _T("rb"));
		if (err != 0)
			return "";

		_fseeki64(fp, 0, SEEK_END);
		UINT64 dwFileSize = _ftelli64(fp);
		_fseeki64(fp, 0, SEEK_SET);

		char* pBuffer = new char[BlockSize];
		if (pBuffer == NULL)
			return "";

		UINT64 nReadLength = 0;
		MD5_CTX ctx;
		unsigned char digest[16] = { 0 };
		MD5_Init(&ctx);
		while (true)
		{
			if (dwFileSize > nReadLength + BlockSize)
			{
				fread(pBuffer, BlockSize, 1, fp);
				nReadLength += BlockSize;
				MD5_Update(&ctx, pBuffer, BlockSize);
			}
			else
			{
				if (dwFileSize == nReadLength)
					break;
				fread(pBuffer, dwFileSize - nReadLength, 1, fp);
				MD5_Update(&ctx, pBuffer, dwFileSize - nReadLength);
				break;
			}
		}
		fclose(fp);

		MD5_Final(digest, &ctx);

		delete pBuffer;

		char buf[33] = { 0 };
		char tmp[3] = { 0 };

		for (int i = 0; i < 16; i++)
		{
			sprintf(tmp, "%02x", digest[i]);
			strcat(buf, tmp);
		}

		return buf;
	}

}