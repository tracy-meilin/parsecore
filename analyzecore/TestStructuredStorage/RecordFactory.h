#pragma once

class RecordFactory 
	: public util::Singleton<RecordFactory>
{
public:
	RecordFactory();
	~RecordFactory();

	shared_ptr<Record> CreateRecord(shared_ptr<VirtualStream> spVirtualStream);
};

