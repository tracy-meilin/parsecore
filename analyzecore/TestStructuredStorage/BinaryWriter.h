#pragma once
class BinaryWriter
{
public:
	BinaryWriter();
	BinaryWriter(shared_ptr<BaseStream> spBaseStream);
	~BinaryWriter();

	size_t Write(const unsigned char* p, size_t size);

	size_t Write(const char* p, size_t size);

	bool Close();

protected:
	shared_ptr<BaseStream> _spBaseStream = nullptr;
};

