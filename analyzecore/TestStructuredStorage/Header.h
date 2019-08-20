#pragma once

class Header
	: public AbstractHeader
{
public:
	Header();
	Header(shared_ptr<InputHandler> spfileHandler);
	~Header();

private:
	void ReadHeader();
};

