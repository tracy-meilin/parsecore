#pragma once

class AbstractHeader;
class PptFileFormat_API AbstractIOHandler
{
public:
	AbstractIOHandler();
	~AbstractIOHandler();

	virtual unsigned long GetIOStreamSize() = 0;

	void InitBitConverter(bool isLittleEndian);

	void SetHeaderReference(weak_ptr<AbstractHeader> spHeader);

	void CloseStream();

protected:
	shared_ptr<simple::file_istream> _spStream = nullptr;
	shared_ptr<InternalBitConverter> _spBitConverter = nullptr;
	
	weak_ptr<AbstractHeader> _spHeader;
};

