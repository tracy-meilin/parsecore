// TestOfficeCore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<CNDPowerpointDoc> spDoc = make_shared<CNDPowerpointDoc>();
	spDoc->OpenDoc(_T("F:\\ppttest\\1.ppt"));

	std::vector<shared_ptr<CNDSlide>> vecSlides = spDoc->GetSlides();

	for (auto& slide : vecSlides)
	{
		std::vector<shared_ptr<CNDShape>> vecShapes = slide->GetShapes();
		for (auto& shape : vecShapes)
		{
			shape->GetTxBody();
		}
	}

	return 0;
}

