#pragma once
const unsigned long HEADER_SIZE_IN_BYTES = (16 + 16 + 32) / 8;

class Record
{
public:
	Record();
	Record(shared_ptr<BinaryReader> spVirtualStream,
		unsigned long bodySize,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Record();

	virtual wstring ToString(unsigned long depth);

	virtual bool DoAutomaticVerifyReadToEnd(){ return true; }

	void VerifyReadToEnd();

	unsigned long GetTotalSize(){ return HeaderSize + BodySize; }

	template<typename T>
	shared_ptr<T> FirstAncestorWithType();

	//get/set
	Record* GetParentRecord(){ return _pParentRecord; }
	void SetParentRecord(Record* pRecord){ _pParentRecord = pRecord; }

public:
	unsigned long HeaderSize = HEADER_SIZE_IN_BYTES;
	unsigned long BodySize;

	/// <summary>
	/// Index of sibling, 0 for first child in container, 1 for second child and so on...
	/// </summary>
	unsigned long SiblingIdx;
	unsigned long TypeCode;
	unsigned long Version;
	unsigned long Instance;

	unsigned char* RawData;

protected:
	shared_ptr<BinaryReader> _spBinaryReader = nullptr;
	Record* _pParentRecord = nullptr;
};

template<typename T>
shared_ptr<T> Record::FirstAncestorWithType()
{
	shared_ptr<Record> spCurAncestor = make_shared<Record>(*(this->_pParentRecord));
	while (spCurAncestor)
	{
		shared_ptr<T> t = dynamic_pointer_cast<T>(spCurAncestor);
		if (t)
			return t;

		spCurAncestor = make_shared<Record>(*(spCurAncestor->GetParentRecord()));
	}

	return nullptr;
}

