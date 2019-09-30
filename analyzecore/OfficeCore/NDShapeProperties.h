#pragma once

#include "NDGen.h"

// p:cNvPr
struct NDNVCanvasProperties
{
	signed long spId;
	wstring strName;
};

// p:cNvGrpSpPr
struct NDNVCanvasGrpShapeProperties
{

};

// p:cNvSpPr
struct NDNVCanvasShapeProperties
{

};

// p:ph
struct NDPH
{
	wstring strType;
};

// p:nvPr
struct NDNVProperties
{
	NDNVProperties()
	{
		spPh = make_shared<NDPH>();
	}

	shared_ptr<NDPH> spPh = nullptr;
};


// p:nvGrpSpPr
struct NDNVGrpShapeProperties
{
	NDNVGrpShapeProperties()
	{
		spCNvPr = make_shared<NDNVCanvasProperties>();
		spCNvGrpSpPr = make_shared<NDNVCanvasGrpShapeProperties>();
		spNvPr = make_shared<NDNVProperties>();
	}

	shared_ptr<NDNVCanvasProperties> spCNvPr = nullptr;
	shared_ptr<NDNVCanvasGrpShapeProperties> spCNvGrpSpPr = nullptr;
	shared_ptr<NDNVProperties> spNvPr = nullptr;
};

//////////////////////////////////////////////////////////////////////////

// a:xfrm
struct NDXfrm
{
	Point ptOff;
	Size sizeExt;
	Point ptChOff;
	Size sizeChExt;

	bool bFlipH = false;
	bool bFlipV = false;
};

// p:grpSpPr
struct NDGrpShapeProperties
{
	NDGrpShapeProperties()
	{
		spXfrm = make_shared<NDXfrm>();
	}

	shared_ptr<NDXfrm> spXfrm = nullptr;
};

//////////////////////////////////////////////////////////////////////////

// p:nvSpPr
struct NDNVShapeProperties
{
	NDNVShapeProperties()
	{
		spCNvPr = make_shared<NDNVCanvasProperties>();
		spCNvSpPr = make_shared<NDNVCanvasShapeProperties>();
		spNvPr = make_shared<NDNVProperties>();
	}

	shared_ptr<NDNVCanvasProperties> spCNvPr = nullptr;
	shared_ptr<NDNVCanvasShapeProperties> spCNvSpPr = nullptr;
	shared_ptr<NDNVProperties> spNvPr = nullptr;
};


//////////////////////////////////////////////////////////////////////////

// a:ln
struct NDLn
{

};

struct NDNoFill
{
	bool bNoFill = false;
};

// a:avLst
struct NDAvLst
{

};

// a:prstGeom
struct NDPrstGeom
{
	wstring strPrst;
};

// p:spPr
struct NDShapeProperties
{
	NDShapeProperties()
	{
		spXfrm = make_shared<NDXfrm>();
		spPrstGeom = make_shared<NDPrstGeom>();
		spAvLst = make_shared<NDAvLst>();
		spNoFill = make_shared<NDNoFill>();
		spLn = make_shared<NDLn>();
	}

	shared_ptr<NDXfrm> spXfrm = nullptr;
	shared_ptr<NDPrstGeom> spPrstGeom = nullptr;
	shared_ptr<NDAvLst> spAvLst = nullptr;
	shared_ptr<NDNoFill> spNoFill = nullptr;
	shared_ptr<NDLn> spLn = nullptr;
};

//////////////////////////////////////////////////////////////////////////

// a:bodyPr
struct NDBodyProperties
{
	unsigned long lIns;			//left
	unsigned long tIns;			//top
	unsigned long rIns;			//right
	unsigned long bIns;			//bottom

	wstring strWrap;			//wrap
	wstring strAnchor;			//anchor

	bool bAnchorCtrl = false;	//anchorCtr
};

// a:lstStyle
struct NDLstStyle
{

};

// a:buChar
struct NDBuChar
{
	wstring strChar;
};

// a:pPr
struct NDParagraphProperties
{
	NDParagraphProperties()
	{
		spBuChar = make_shared<NDBuChar>();
	}

	wstring strAlgn;
	shared_ptr<NDBuChar> spBuChar = nullptr;
};

// a:rPr
struct NDRunProperties
{
	wstring strLang;
	unsigned long sz;
};

// a:t
struct NDText
{
	wstring strText;
};

// a:r
struct NDRun
{
	NDRun()
	{
		spRPr = make_shared<NDRunProperties>();
		spT = make_shared<NDText>();
	}

	shared_ptr<NDRunProperties> spRPr = nullptr;
	shared_ptr<NDText> spT = nullptr;
};

// a:endParaRPr
struct NDEndParaRProperties
{

};

// a:p
struct NDParagraph
{
	NDParagraph()
	{
		spPPr = make_shared<NDParagraphProperties>();
		spRun = make_shared<NDRun>();
		spEndParaRPr = make_shared<NDEndParaRProperties>();
	}

	shared_ptr<NDParagraphProperties> spPPr = nullptr;
	shared_ptr<NDRun> spRun = nullptr;
	shared_ptr<NDEndParaRProperties> spEndParaRPr = nullptr;
};

//////////////////////////////////////////////////////////////////////////

// a:picLocks
struct NDPicLocks
{
	bool bNoChangeArrowheads = false;
	bool bNoChangeAspect = false;
};

// p:cNvPicPr
struct NDNVCanvasPicProperties
{
	NDNVCanvasPicProperties()
	{
		spPicLocks = make_shared<NDPicLocks>();
	}

	shared_ptr<NDPicLocks> spPicLocks = nullptr;
};

// p:nvPicPr
struct NDNVPicProperties
{
	NDNVPicProperties()
	{
		spNvPr = make_shared<NDNVProperties>();
		spNvPr = make_shared<NDNVProperties>();
	}

	shared_ptr<NDNVCanvasProperties> spCNvPr = nullptr;
	shared_ptr<NDNVProperties> spNvPr = nullptr;
};


//////////////////////////////////////////////////////////////////////////

// a:blip
struct NDBlip
{
	wstring strEmbed;
};

// a:srcRect
struct NDSrcRect
{

};

// a:fillRect
struct NDFillRect
{

};

// a:stretch
struct NDStretch
{
	NDStretch()
	{
		spFillRect = make_shared<NDFillRect>();
	}

	shared_ptr<NDFillRect> spFillRect = nullptr;
};

// p:blipFill
struct NDBlipFill
{
	NDBlipFill()
	{
		spBlipFill = make_shared<NDBlipFill>();
		spSrcRect = make_shared<NDSrcRect>();
		spStretch = make_shared<NDStretch>();
	}

	shared_ptr<NDBlipFill> spBlipFill = nullptr;
	shared_ptr<NDSrcRect> spSrcRect = nullptr;
	shared_ptr<NDStretch> spStretch = nullptr;
};


//////////////////////////////////////////////////////////////////////////