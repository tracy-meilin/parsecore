#pragma once

class TextRunStyleAtom 
	: public TextStyleAtom
{
public:
	TextRunStyleAtom();
	TextRunStyleAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~TextRunStyleAtom();

	virtual bool DoAutomaticVerifyReadToEnd() override { return false; }

	virtual void AfterTextHeaderSet() override;
};

