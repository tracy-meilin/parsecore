#pragma once

class BlipStoreEntry 
	: public Record
{
public:
	BlipStoreEntry();
	BlipStoreEntry(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~BlipStoreEntry();

public:
	/// <summary>
	/// Required type on Win32 
	/// </summary>
	BlipStoreSpace::BlipType btWin32;

	/// <summary>
	/// Required type on Mac 
	/// </summary>
	BlipStoreSpace::BlipType btMacOS;

	/// <summary>
	/// Identifier of blip
	/// </summary>
	unsigned char* rgbUid = nullptr;

	/// <summary>
	/// currently unused
	/// </summary>
	signed short tag;

	/// <summary>
	/// Blip size in stream
	/// </summary>
	unsigned long size;

	/// <summary>
	/// Reference count on the blip
	/// </summary>
	unsigned long cRef;

	// File offset in the delay stream 
	unsigned long foDelay;

	/// <summary>
	/// How this blip is used (MSOBLIPUSAGE)
	/// </summary>
	BlipStoreSpace::BlipUsage usage;

	/// <summary>
	/// length of the blip name 
	/// </summary>
	unsigned char cbName;

	/// <summary>
	/// for the future 
	/// </summary>
	unsigned char unused2;

	/// <summary>
	/// for the future
	/// </summary>
	unsigned char unused3;

	/// <summary>
	/// The primary UID - this defaults to 0, in which case the primary ID is that of the internal data. <br/>
	/// NOTE!: The primary UID is only saved to disk if (blip_instance ^ blip_signature == 1). <br/>
	/// Blip_instance is MSOFBH.inst and blip_signature is one of the values defined in MSOBI
	/// </summary>
	unsigned char* m_rgbUid = nullptr;

	/// <summary>
	/// optional based on the above check.
	/// </summary>
	unsigned char* m_rgbUidPrimary = nullptr;

	/// <summary>
	/// 
	/// </summary>
	unsigned char m_bTag;

	/// <summary>
	/// Cache of the metafile size 
	/// </summary>
	signed short m_cb;

	//RECT m_rcBounds; // Boundary of metafile drawing commands 
	//POINT m_ptSize; // Size of metafile in EMUs 

	/// <summary>
	/// Cache of saved size (size of m_pvBits) 
	/// </summary>
	signed short m_cbSave;

	/// <summary>
	/// Compression
	/// </summary>
	unsigned char m_fCompression;

	/// <summary>
	/// always msofilterNone
	/// </summary>
	unsigned char m_fFilter;

	shared_ptr<Record> _spBlip = nullptr;
};

