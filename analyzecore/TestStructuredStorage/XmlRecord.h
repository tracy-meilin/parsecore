#pragma once

/// <summary>
/// XML records are containers with a XML payload.
/// </summary>
class XmlRecord 
	: public Record
{
public:
	XmlRecord();
	XmlRecord(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~XmlRecord();
};

