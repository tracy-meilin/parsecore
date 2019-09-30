#pragma once
const unsigned long HEADER_SIZE_IN_BYTES = (16 + 16 + 32) / 8;

class PptFileFormat_API Record
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
	T* FirstAncestorWithType();

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
T* Record::FirstAncestorWithType()
{
	Record* pCurAncetor = this->_pParentRecord;
	while (pCurAncetor)
	{
		T* t = dynamic_cast<T*>(pCurAncetor);
		if (t)
			return t;

		pCurAncetor = pCurAncetor->GetParentRecord();
	}

	return nullptr;
}

