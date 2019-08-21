#pragma once

namespace Common{
	template<typename T>
	static T bytes2T(unsigned char *bytes)
	{
		T res = 0;
		int n = sizeof(T);
		memcpy(&res, bytes, n);
		return res;
	}

	template<typename T>
	static unsigned char * T2bytes(T u)
	{
		int n = sizeof(T);
		unsigned char* b = new unsigned char[n];
		memcpy(b, &u, n);
		return b;
	}
}