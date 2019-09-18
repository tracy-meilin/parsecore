#pragma once

class PptFileFormat_API InternalBitConverter
{
public:
	InternalBitConverter();
	InternalBitConverter(bool isLittleEndian);
	~InternalBitConverter();

private:
	bool _IsLittleEndian = true;
};

