#include "stdafx.h"
#include "GlobalDefines.h"
#include "Singleton.h"
#include "Handle.h"
#include "ProtectionBooleans.h"
#include "ShapeType.h"
#include "RectangleType.h"
#include "PictureFrameType.h"
#include "ShapeTypeFactory.h"


ShapeTypeFactory::ShapeTypeFactory()
{
}


ShapeTypeFactory::~ShapeTypeFactory()
{
}

std::shared_ptr<ShapeType> ShapeTypeFactory::CreateShapeType(unsigned long typeCode)
{
	shared_ptr<ShapeType> spShapeType = nullptr;

	switch (typeCode)
	{
	case 0x00000001:
	{
		spShapeType = make_shared<RectangleType>();
	}
		break;
	case 0x0000004b:
	{
		spShapeType = make_shared<PictureFrameType>();
	}
		break;
	default:
		break;
	}

	return spShapeType;
}
