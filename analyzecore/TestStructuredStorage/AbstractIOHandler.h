#pragma once

class AbstractHeader;
class AbstractIOHandler
{
public:
	AbstractIOHandler();
	~AbstractIOHandler();

	unsigned long GetIOStreamSize();

	void InitBitConverter(bool isLittleEndian);

	void SetHeaderReference(shared_ptr<AbstractHeader> spHeader);

	void CloseStream();

protected:
	shared_ptr<simple::file_istream<std::true_type>> _spStream = nullptr;
	shared_ptr<AbstractHeader> _spHeader;
	shared_ptr<InternalBitConverter> _spBitConverter;
};

