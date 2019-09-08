#pragma once

class XmlStringAtom
	: public XmlRecord
{
public:
	XmlStringAtom();
	XmlStringAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~XmlStringAtom();
};

