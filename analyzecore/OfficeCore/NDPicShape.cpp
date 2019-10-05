#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDTextBody.h"
#include "NDShape.h"
#include "NDPicShape.h"


CNDPicShape::CNDPicShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: CNDShape(spShapeContainer)
{
}


CNDPicShape::~CNDPicShape()
{
}

NDShapeType CNDPicShape::GetShapeType()
{
	return NDShapeType::PicShape;
}

std::shared_ptr<NDBlipFill> CNDPicShape::GetBlipFill()
{
	if (m_spShapeContainer == nullptr
		|| m_spBlipFill != nullptr)
		return m_spBlipFill;

	unsigned long indexOfPicture = 0;

	shared_ptr<ShapeOptions> spShapeOptions = m_spShapeContainer->FirstChildWithType<ShapeOptions>();
	if (spShapeOptions)
	{
		vector<shared_ptr<OptionEntry>> vecTmp = spShapeOptions->m_vecOptions;
		for (auto& ele : vecTmp)
		{
			switch (ele->pid)
			{
			case ShapeOptionsSpace::PropertyId::Pib:
				indexOfPicture = ele->op - 1;
				break;
			case ShapeOptionsSpace::PropertyId::pibName:
				//    name = Encoding.Unicode.GetString(en.opComplex);
				//    name = name.Substring(0, name.Length - 1).Replace("\0","");
				break;
			case ShapeOptionsSpace::PropertyId::pibPrintName:
				//TODO:
				break;
			default:
				break;
			}
		}
	}

	Slide* pSlide = m_spShapeContainer->FirstAncestorWithType<Slide>();
	if (pSlide == nullptr)
		return m_spBlipFill;

	PowerPointDocument* pPPT = pSlide->GetPowerPointDoc();
	if (pPPT == nullptr)
		return m_spBlipFill;

	shared_ptr<DocumentContainer> spDocumentContainer = pPPT->_spDocumentRecord;
	if (spDocumentContainer == nullptr)
		return m_spBlipFill;

	shared_ptr<PPDrawingGroup> spPPDrawingGroup = spDocumentContainer->FirstChildWithType<PPDrawingGroup>();
	if (spPPDrawingGroup == nullptr 
		|| spPPDrawingGroup->_Child.size() <= 0)
		return m_spBlipFill;

	shared_ptr<DrawingGroup> spDrawingGroup = dynamic_pointer_cast<DrawingGroup>(spPPDrawingGroup->_Child[0]);
	if (spDrawingGroup == nullptr)
		return m_spBlipFill;

	shared_ptr<BlipStoreContainer> spBlipStoreContainer = spDrawingGroup->FirstChildWithType<BlipStoreContainer>();
	if (spBlipStoreContainer == nullptr 
		|| spBlipStoreContainer->_Child.size() <= 0)
		return m_spBlipFill;

	shared_ptr<BlipStoreEntry> spBlipStoreEntry = dynamic_pointer_cast<BlipStoreEntry>(spBlipStoreContainer->_Child[indexOfPicture]);
	if (spBlipStoreEntry == nullptr)
		return m_spBlipFill;

	shared_ptr<Pictures> spPictures = pPPT->_spPictures;
	if (spPictures == nullptr)
		return m_spBlipFill;

	auto& picEle = spPictures->_pictures.find(spBlipStoreEntry->foDelay);
	if (picEle == spPictures->_pictures.end())
		return m_spBlipFill;

	shared_ptr<BitmapBlip> spBitmapBlip = dynamic_pointer_cast<BitmapBlip>(picEle->second);
	if (spBitmapBlip == nullptr)
		return m_spBlipFill;

#ifdef _DEBUG
	//TODO: Test code
	TCHAR lpTempPathBuffer[MAX_PATH];
	TCHAR szTempFileName[MAX_PATH];

	DWORD dwRt = GetTempPath(MAX_PATH,          // length of the buffer
		lpTempPathBuffer); // buffer for path 

	dwRt = GetTempFileName(lpTempPathBuffer, // directory for tmp files
		_T("ND_TMP"),     // temp file name prefix 
		0,                // create unique name 
		szTempFileName);  // buffer for name 

	shared_ptr<FileStream> spFileStream = make_shared<FileStream>(szTempFileName);
	if (spFileStream)
	{
		shared_ptr<BinaryWriter> spBinaryWriter = make_shared<BinaryWriter>(spFileStream);
		if (spBinaryWriter)
		{
			spBinaryWriter->Write(spBitmapBlip->m_pvBits, spBitmapBlip->m_nBitsLength);
			spBinaryWriter->Close();
			spFileStream->Close();
		}
	}
#endif // DEBUG

	//shared_ptr<MetafilePictBlip> sp
	
	return m_spBlipFill;
}

std::shared_ptr<NDNVPicProperties> CNDPicShape::GetNvPicPr()
{
	if (m_spShapeContainer == nullptr
		|| m_spNvPicPr != nullptr)
		return m_spNvPicPr;

	shared_ptr<Shape> spShape = m_spShapeContainer->FirstChildWithType<Shape>();
	if (spShape == nullptr)
		return m_spNvPicPr;

	m_spNvPicPr = make_shared<NDNVPicProperties>();
	m_spNvPicPr->spCNvPr->spId = spShape->spid;
	m_spNvPicPr->spCNvPr->strName = _T("");
	m_spNvPicPr->spCNvPr->strDescr = _T("");

	m_spNvPicPr->spCNvPicPr->spPicLocks->bNoChangeArrowheads = true;
	m_spNvPicPr->spCNvPicPr->spPicLocks->bNoChangeAspect = true;

	//TODO:
	m_spNvPicPr->spNvPr = nullptr;

	return m_spNvPicPr;
}
