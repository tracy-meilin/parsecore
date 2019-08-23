#pragma once
class AbstractDirectoryEntry
{
public:
	AbstractDirectoryEntry();
	AbstractDirectoryEntry(unsigned long sid);
	~AbstractDirectoryEntry();


	//get/set
	wstring GetPath(){ return _path + _name; }
	wstring GetName(){ return _name; }
	void SetName(const wstring& name){ _name = name; }

public:
	unsigned long _sid;
	unsigned long _lengthOfName;
	Common::DirectoryEntryType _type;
	Common::DirectoryEntryColor _color;
	unsigned long _leftSiblingSid;
	unsigned long _rightSiblingSid;
	unsigned long _childSiblingSid;
	//CLSID todo
	//Guid _clsId;
	unsigned long _userFlags;
	unsigned long _startSector;
	unsigned __int64 _sizeOfStream;


protected:
	wstring _path;
	wstring _name;

};

