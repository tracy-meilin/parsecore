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
	virtual ~RegularContainer();

	virtual wstring ToString(unsigned long depth){ return _T(""); };

	template<typename T>
	vector<shared_ptr<T>> AllChildrenWithType();

	template<typename T>
	shared_ptr<T> FirstChildWithType();

public:
	vector<shared_ptr<Record>> _Child;
};

template<typename T>
vector<shared_ptr<T>>
RegularContainer::AllChildrenWithType()
{
	vector<shared_ptr<T>> vecResult;
	for (auto& ele : _Child)
	{
		shared_ptr<T> spT = dynamic_pointer_cast<T>(ele);
		if (spT)
		{
			vecResult.push_back(spT);
		}
	}

	return vecResult;
}

template<typename T>
shared_ptr<T>
RegularContainer::FirstChildWithType()
{
	shared_ptr<T> spT = nullptr;
	for (auto& ele : _Child)
	{
		spT = dynamic_pointer_cast<T>(ele);
		if (spT)
		{
			return spT;
		}
	}

	return spT;
}


