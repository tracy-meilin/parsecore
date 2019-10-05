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
			switch (shape->GetShapeType())
			{
			case NDShapeType::HeaderGroupShape:
				shape->GetNvGrpSpPr();
				shape->GetGrpSpPr();
				break;
			case NDShapeType::NormalShape:
			{
				shape->GetNvSpPr();
				shape->GetSpPr();
				shared_ptr<CNDTextBody> spNDTxtBody = shape->GetTxBody();
				if (spNDTxtBody)
				{
					vector<shared_ptr<NDParagraph>> vec = spNDTxtBody->GetPs();
					for (auto& p : vec)
					{
						if (p->spRun && p->spRun->spT)
							wstring str = p->spRun->spT->strText;
					}
				}
				break;
			}
			case NDShapeType::PicShape:
			{
				shared_ptr<CNDPicShape> spNDPicShape = dynamic_pointer_cast<CNDPicShape>(shape);
				if (spNDPicShape)
				{
					spNDPicShape->GetNvPicPr();
					spNDPicShape->GetBlipFill();
					spNDPicShape->GetSpPr();
				}
			}
				break;
			default:
				break;
			}
		}
	}

	return 0;
}

