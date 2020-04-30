#include "stdafx.h"
#include "xmltoken.h"
#include "xmltkmap.h"


using namespace ::xmloff::token;

class SvXMLTokenMapEntry_Impl
{
	sal_uInt16  nPrefixKey;
	wstring     sLocalName;
	sal_uInt16  nToken;

public:

	sal_uInt16 GetToken() const { return nToken; }

	SvXMLTokenMapEntry_Impl(sal_uInt16 nPrefix, const wstring& rLName,
		sal_uInt16 nTok = XML_TOK_UNKNOWN) :
		nPrefixKey(nPrefix),
		sLocalName(rLName),
		nToken(nTok)
	{}

	explicit SvXMLTokenMapEntry_Impl(const SvXMLTokenMapEntry& rEntry) :
		nPrefixKey(rEntry.nPrefixKey),
		sLocalName(GetXMLToken(rEntry.eLocalName)),
		nToken(rEntry.nToken)
	{}

	bool operator<(const SvXMLTokenMapEntry_Impl& r) const
	{
		return nPrefixKey < r.nPrefixKey ||
			(nPrefixKey == r.nPrefixKey &&
			sLocalName < r.sLocalName);
	}
};

class SvXMLTokenMap_Impl : public std::set<SvXMLTokenMapEntry_Impl> {};

SvXMLTokenMap::SvXMLTokenMap(const SvXMLTokenMapEntry *pMap)
	: m_pImpl(new SvXMLTokenMap_Impl)
{
	while (pMap->eLocalName != XML_TOKEN_INVALID)
	{
		m_pImpl->insert(SvXMLTokenMapEntry_Impl(*pMap));
		pMap++;
	}
}

SvXMLTokenMap::~SvXMLTokenMap()
{
}

sal_uInt16 SvXMLTokenMap::Get(sal_uInt16 nKeyPrefix,
	const wstring& rLName) const
{
	SvXMLTokenMapEntry_Impl const* pEntry = nullptr;
	SvXMLTokenMapEntry_Impl aTst(nKeyPrefix, rLName);

	SvXMLTokenMap_Impl::iterator it = m_pImpl->find(aTst);
	if (it != m_pImpl->end())
	{
		pEntry = &*it;
	}

	if (pEntry)
		return pEntry->GetToken();
	else
		return XML_TOK_UNKNOWN;
}