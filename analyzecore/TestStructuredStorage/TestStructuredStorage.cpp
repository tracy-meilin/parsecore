// TestStructuredStorage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "CustomOperators.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "AbstractDirectoryEntry.h"
#include "DirectoryEntry.h"
#include "DirectoryTree.h"
#include "MiniFat.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include "StructuredStorageReader.h"
#include "BinaryReader.h"
#include "Record.h"
#include "CurrentUserAtom.h"
#include "UserEditAtom.h"
#include "Pictures.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "SlidePersisAtom.h"
#include "RegularContainer.h"
#include "List.h"
#include "SlideListWithText.h"
#include "DocumentContainer.h"
#include "PowerPointDocument.h"
#include "SimpleBinStream.h"

class MyClass
{
public:
	MyClass();
	~MyClass();

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}


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

	shared_ptr<MyClass> spTmp = make_shared<MyClass>();
	spTmp = nullptr;

	int n = sizeof(char);
	n = sizeof(unsigned char);

	char  buf[7] = { 'a', 'b', 'c', '\0', 'e', 'f' };
	string  str1, str2, str3;
	str1 = string(buf);

	str2.assign(buf);
	int n3 = sizeof(buf);
	str3.assign(buf, sizeof(buf) / sizeof(char));

	cout << "when str1 = string(buf) :\nstr1  is\t" << str1 << endl;
	cout << "when str2.assign(buf): \nstr2 is\t" << str2 << endl;
	cout << "when str3.assign(buf,sizeof(buf)/sizeof(char)) : \nstr3 is\t" << str3 << endl;

	auto& str = "String!\0 This is a string too!";
	std::string s(std::begin(str), std::end(str));
	std::cout << s.size() << '\n' << s << '\n';


	shared_ptr<StructuredStorageReader> st = make_shared<StructuredStorageReader>(_T("F:\\ppt\\1.ppt"));
	shared_ptr<PowerPointDocument> spPPT = make_shared<PowerPointDocument>(st);
	//StructuredStorageReader st(_T("F:\\ppttest\\1.ppt"));

	return 0;
}

