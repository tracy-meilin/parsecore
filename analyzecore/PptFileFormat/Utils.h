#pragma once
class PptFileFormat_API Utils
{
public:
	Utils();
	~Utils();

	static signed long MasterCoordToEMU(signed long mc);

	static signed long EMUToMasterCoord(signed long emu);

	static bool BitmaskToBool(signed long value, signed long mask);

	static bool BitmaskToBool(unsigned long value, unsigned long mask);

	static bool BitmaskToBool(signed short value, signed short mask);

	static bool BitmaskToBool(unsigned short value, unsigned short mask);

	static wstring PlaceholderIdToXMLValue(OEPlaceHolderAtomSpace::PlaceholderEnum pid);

	static wstring GetPrstForShape(unsigned long shapeInstance);
};

