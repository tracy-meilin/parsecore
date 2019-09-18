#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "ShapeContainer.h"
#include "GroupContainer.h"


GroupContainer::GroupContainer()
{
}


GroupContainer::GroupContainer(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	for (int i = 0; i < this->_Child.size(); ++i)
	{
		shared_ptr<Record> spGroupChild = this->_Child[i];
		if (spGroupChild && spGroupChild->TypeCode == 0xF003)
		{
			// the child is a subgroup
			shared_ptr<GroupContainer> spGroup = dynamic_pointer_cast<GroupContainer>(spGroupChild);
			if (spGroup)
			{
				spGroup->Index = i;
				//C# this.Children[i] = group;
			}
		}
		else if (spGroupChild && spGroupChild->TypeCode == 0xF004)
		{
			// the child is a shape
			shared_ptr<ShapeContainer> spShape = dynamic_pointer_cast<ShapeContainer>(spGroupChild);
			if (spShape)
			{
				spShape->Index = i;
				//C# this.Children[i] = shape;
			}
		}
	}
}

GroupContainer::~GroupContainer()
{
}
