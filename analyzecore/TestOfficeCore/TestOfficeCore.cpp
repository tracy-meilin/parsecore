// TestOfficeCore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "libxml/SAX2.h"
#include "libxml/xmlstring.h"
#include "libzippp/libzippp.h"
using namespace libzippp;

void TestLibXMLSax()
{
	xmlInitParser();
}

void TestLibZippp()
{
	/*const char* txtFile = "this is some data";
	int len = strlen(txtFile);

	ZipArchive z1("test.zip");
	z1.open(ZipArchive::WRITE);
	z1.addData("somedata/in/subfolder/data.txt", txtFile, len);
	z1.addEntry("somedata/");
	z1.addEntry("in/");
	z1.addEntry("in/subfolder/");
	z1.close();*/
}

//PPT格式的读取
void TestOfficeCore()
{
	shared_ptr<CNDPowerpointDoc> spDoc = make_shared<CNDPowerpointDoc>();
	spDoc->OpenDoc(_T("..\\..\\analyzecore\\testCase\\1.ppt"));

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
}

//PPTX格式的读取
void TestPPTXOfficeCore()
{
	shared_ptr<CNDPPTXPowerpointDoc> spDoc = make_shared<CNDPPTXPowerpointDoc>();
	if (!spDoc->OpenDoc(_T("..\\..\\analyzecore\\testCase\\1.pptx")))
		return;


}

int _tmain(int argc, _TCHAR* argv[])
{
	TestPPTXOfficeCore();
	return 0;
}

