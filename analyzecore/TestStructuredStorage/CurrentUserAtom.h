#pragma once
class CurrentUserAtom 
	: public Record
{
public:
	CurrentUserAtom();
	CurrentUserAtom(shared_ptr<VirtualStream> spVirtualStream,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~CurrentUserAtom();

	virtual wstring ToString(unsigned long depth) override;
};

