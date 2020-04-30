#pragma once

class SvXMLTokenMap_Impl;

#define XML_TOK_UNKNOWN 0xffffU
#define XML_TOKEN_MAP_END { 0xffffU, ::xmloff::token::XML_TOKEN_INVALID, 0U }

struct SvXMLTokenMapEntry
{
	sal_uInt16  nPrefixKey;
	enum ::xmloff::token::XMLTokenEnum eLocalName;
	sal_uInt16  nToken;
};

class SvXMLTokenMap
{
	std::unique_ptr<SvXMLTokenMap_Impl>  m_pImpl;

public:

	SvXMLTokenMap(const SvXMLTokenMapEntry* pMap);
	~SvXMLTokenMap();

	sal_uInt16 Get(sal_uInt16 nPrefix, const wstring& rLName) const;
};