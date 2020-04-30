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

class SvXMLImport
{
public:
	SvXMLImport();
	~SvXMLImport();

	SvXMLImportFlags  getImportFlags() const { return mnImportFlags; }

	shared_ptr<SvXMLImportContext> CreateContext(sal_uInt16 nPrefix,
		const wstring& rLocalName,
		const AttributeList& rAttrList);

private:
	SvXMLImportFlags  mnImportFlags;
};

