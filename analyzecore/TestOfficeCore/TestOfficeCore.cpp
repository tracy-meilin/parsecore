// TestOfficeCore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<CNDPowerpointDoc> spDoc = make_shared<CNDPowerpointDoc>();
	spDoc->OpenDoc(_T("F:\\ppttest\\1.ppt"));
	return 0;
}

