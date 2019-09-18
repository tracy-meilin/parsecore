#pragma once

class PptFileFormat_API Header
	: public AbstractHeader
{
public:
	Header();
	Header(shared_ptr<InputHandler> spfileHandler);
	~Header();

	virtual void GetVirtual() override{};

	void ReadHeader();
};

