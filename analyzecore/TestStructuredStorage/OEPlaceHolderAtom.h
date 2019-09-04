#pragma once

class OEPlaceHolderAtom 
	: public Record
{
public:
	OEPlaceHolderAtom();
	OEPlaceHolderAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~OEPlaceHolderAtom();

	bool IsObjectPlaceholder();

public:
	/// <summary>
	/// A signed integer that specifies an ID for the placeholder shape.
	/// It SHOULD be unique among all PlaceholderAtom records contained in the corresponding slide.
	/// The value 0xFFFFFFFF specifies that the corresponding shape is not a placeholder shape.
	/// </summary>
	signed short Position;

	/// <summary>
	/// A PlaceholderEnum enumeration that specifies the type of the placeholder shape.
	/// </summary>
	OEPlaceHolderAtomSpace::PlaceholderEnum PlacementId;

	/// <summary>
	/// A PlaceholderSize enumeration that specifies the preferred size of the placeholder shape.
	/// </summary>
	unsigned char PlaceholderSize;
};

