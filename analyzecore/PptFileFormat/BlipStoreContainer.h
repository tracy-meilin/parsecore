#pragma once

class PptFileFormat_API BlipStoreContainer
	: public RegularContainer
{
public:
	BlipStoreContainer();
	BlipStoreContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~BlipStoreContainer();
};

