#pragma once

class XmlContainer 
	: public XmlRecord
{
public:
	XmlContainer();
	XmlContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~XmlContainer();
};

