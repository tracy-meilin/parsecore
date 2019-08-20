#pragma once
class InternalBitConverter
{
public:
	InternalBitConverter();
	InternalBitConverter(bool isLittleEndian);
	~InternalBitConverter();

private:
	bool _IsLittleEndian = true;
};

