#include "stdafx.h"
#include "GlobalDefines.h"
#include "Handle.h"
#include "ProtectionBooleans.h"
#include "ShapeType.h"
#include "PictureFrameType.h"


PictureFrameType::PictureFrameType()
	: ShapeType()
{
	this->Path = _T("m@4@5l@4@11@9@11@9@5xe");

	this->m_vecFormulas.push_back(_T("if lineDrawn pixelLineWidth 0"));
	this->m_vecFormulas.push_back(_T("sum @0 1 0"));
	this->m_vecFormulas.push_back(_T("sum 0 0 @1"));
	this->m_vecFormulas.push_back(_T("prod @2 1 2"));
	this->m_vecFormulas.push_back(_T("prod @3 21600 pixelWidth"));
	this->m_vecFormulas.push_back(_T("prod @3 21600 pixelHeight"));
	this->m_vecFormulas.push_back(_T("sum @0 0 1"));
	this->m_vecFormulas.push_back(_T("prod @6 1 2"));
	this->m_vecFormulas.push_back(_T("prod @7 21600 pixelWidth"));
	this->m_vecFormulas.push_back(_T("sum @8 21600 0"));
	this->m_vecFormulas.push_back(_T("prod @7 21600 pixelHeight"));
	this->m_vecFormulas.push_back(_T("sum @10 21600 0"));

	//pictures are not stroked or fileld by default
	this->Filled = false;
	this->Stroked = false;

	//pictures have a lock on the aspect ratio by default
	this->_spLock = make_shared<ProtectionBooleans>(0);
	this->_spLock->fUsefLockAspectRatio = true;
	this->_spLock->fLockAspectRatio = true;

	this->ShapeConcentricFill = true;
	this->ConnectorType = _T("rect");
}


PictureFrameType::~PictureFrameType()
{
}
