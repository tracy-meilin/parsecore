#pragma once
//Slide 的子节点
class Theme 
	: public XmlContainer
{
public:
	Theme();
	Theme(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Theme();
};

