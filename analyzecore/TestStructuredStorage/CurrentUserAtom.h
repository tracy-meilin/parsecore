#pragma once

class CurrentUserAtom 
	: public Record
{
public:
	CurrentUserAtom();
	CurrentUserAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~CurrentUserAtom();

	virtual wstring ToString(unsigned long depth) override;

	//get/set
	wstring GetUserName(){ return UserNameUnicode.empty() ? Common::Utf8ToUnicode(UserNameANSI) : UserNameUnicode; }

public:
	unsigned long Size;
	unsigned long HeaderToken;
	unsigned long OffsetToCurrentEdit;
	unsigned short LengthUserName;
	unsigned short DocFileVersion;
	char MajorVersion;
	char MiniorVersion;
	string UserNameANSI;
	wstring UserNameUnicode;
	unsigned long ReleaseVersion;
};

