#pragma once
class SlidePersistAtom 
	: public Record
{
public:
	SlidePersistAtom();
	SlidePersistAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~SlidePersistAtom();

public:
	/// <summary>
	/// logical reference to the slide persist object
	/// </summary>
	unsigned long PersistIdRef;

	/// <summary>
	/// Bit 1: Slide outline view is collapsed
	/// Bit 2: Slide contains shapes other than placeholders
	/// </summary>
	unsigned long Flags;

	/// <summary>
	/// number of placeholder texts stored with the persist object.
	/// Allows to display outline view without loading the slide persist objects
	/// </summary>
	signed long NumberText;

	/// <summary>
	/// Unique slide identifier, used for OLE link monikers for example
	/// </summary>
	unsigned long SlideId;
};

