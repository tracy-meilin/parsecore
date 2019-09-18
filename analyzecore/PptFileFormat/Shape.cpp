#include "stdafx.h"
#include "GlobalDefines.h"
#include "Utils.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "Handle.h"
#include "ProtectionBooleans.h"
#include "ShapeType.h"
#include "ShapeTypeFactory.h"
#include "Shape.h"


Shape::Shape()
{
}


Shape::Shape(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->spid = _spBinaryReader->ReadInt32();

	unsigned long flag = _spBinaryReader->ReadUInt32();
	this->fGroup = Utils::BitmaskToBool(flag, 0x1);
	this->fChild = Utils::BitmaskToBool(flag, 0x2);
	this->fPatriarch = Utils::BitmaskToBool(flag, 0x4);
	this->fDeleted = Utils::BitmaskToBool(flag, 0x8);
	this->fOleShape = Utils::BitmaskToBool(flag, 0x10);
	this->fHaveMaster = Utils::BitmaskToBool(flag, 0x20);
	this->fFlipH = Utils::BitmaskToBool(flag, 0x40);
	this->fFlipV = Utils::BitmaskToBool(flag, 0x80);
	this->fConnector = Utils::BitmaskToBool(flag, 0x100);
	this->fHaveAnchor = Utils::BitmaskToBool(flag, 0x200);
	this->fBackground = Utils::BitmaskToBool(flag, 0x400);
	this->fHaveSpt = Utils::BitmaskToBool(flag, 0x800);
	this->_spShapeType = ShapeTypeFactory::GetInstance()->CreateShapeType(this->Instance);
}

Shape::~Shape()
{
}
