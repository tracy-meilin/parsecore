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
