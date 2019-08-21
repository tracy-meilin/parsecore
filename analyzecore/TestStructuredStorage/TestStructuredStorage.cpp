// TestStructuredStorage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CustomOperators.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "StructuredStorageReader.h"
#include "SimpleBinStream.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*std::vector<Product> vec_src;
	vec_src.push_back(Product("Book", 10.0f, 50));
	vec_src.push_back(Product("Phone", 25.0f, 20));
	vec_src.push_back(Product("Pillow", 8.0f, 10));
	simple::memfile_ostream<std::true_type> out;
	out << vec_src;
	out.write_to_file("file4.bin");

	simple::memfile_istream<std::true_type> in("file4.bin");
	std::vector<Product> vec_dest;
	in >> vec_dest;*/

	StructuredStorageReader st(_T("F:\\ppttest\\1.ppt"));

	return 0;
}

