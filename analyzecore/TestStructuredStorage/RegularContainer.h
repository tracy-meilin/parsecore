#pragma once

/// <summary>
/// Regular containers are containers with Record children.<br/>
/// (There also is containers that only have a zipped XML payload.
/// </summary>
class RegularContainer 
	: public Record
{
public:
	RegularContainer();
	RegularContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~RegularContainer();

public:
	vector<shared_ptr<Record>> _Child;
};

