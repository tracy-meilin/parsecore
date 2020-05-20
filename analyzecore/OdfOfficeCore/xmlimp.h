#pragma once

#include "typed_flags_set.h"

enum class SvXMLImportFlags {
	NONE = 0x0000,
	META = 0x0001,
	STYLES = 0x0002,
	MASTERSTYLES = 0x0004,
	AUTOSTYLES = 0x0008,
	CONTENT = 0x0010,
	SCRIPTS = 0x0020,
	SETTINGS = 0x0040,
	FONTDECLS = 0x0080,
	EMBEDDED = 0x0100,
	ALL = 0xffff
};

namespace o3tl
{
	template<> struct typed_flags<SvXMLImportFlags> : is_typed_flags<SvXMLImportFlags, 0xffff>{};
}

class SvXMLImportContext;

typedef std::vector<shared_ptr<SvXMLImportContext>> SvXMLImportContexts_Impl;

class SvXMLImport
{
public:
	SvXMLImport();
	~SvXMLImport();

	SvXMLImportFlags  getImportFlags() const { return mnImportFlags; }

	virtual shared_ptr<SvXMLImportContext> CreateContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttrList);

	void startElement(const wstring& strPrefix, const wstring& strLocalName, const shared_ptr<AttributeList>& spAttributeList);

private:
	SvXMLImportFlags  mnImportFlags;
	SvXMLImportContexts_Impl mpContexts;
};

