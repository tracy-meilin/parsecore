#pragma once

class RecordFactory 
	: public util::Singleton<RecordFactory>
{
public:
	RecordFactory();
	~RecordFactory();

	shared_ptr<Record> CreateRecord(shared_ptr<BaseStream> spVirtualStream);

	shared_ptr<Record> CreateRecord(shared_ptr<BinaryReader> spBinaryReader);
};

