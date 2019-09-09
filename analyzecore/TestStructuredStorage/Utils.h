#pragma once
class Utils
{
public:
	Utils();
	~Utils();

	static bool BitmaskToBool(signed long value, signed long mask);

	static bool BitmaskToBool(unsigned long value, unsigned long mask);

	static bool BitmaskToBool(signed short value, signed short mask);

	static bool BitmaskToBool(unsigned short value, unsigned short mask);
};

