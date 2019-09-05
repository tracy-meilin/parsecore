#pragma once

class Shape 
	: public Record
{
public:
	Shape();
	Shape(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Shape();

public:
	signed long spid;

	/// <summary>
	/// This shape is a group shape 
	/// </summary>
	bool fGroup;

	/// <summary>
	/// Not a top-level shape 
	/// </summary>
	bool fChild;

	/// <summary>
	/// This is the topmost group shape.<br/>
	/// Exactly one of these per drawing. 
	/// </summary>
	bool fPatriarch;

	/// <summary>
	/// The shape has been deleted 
	/// </summary>
	bool fDeleted;

	/// <summary>
	/// The shape is an OLE object 
	/// </summary>
	bool fOleShape;

	/// <summary>
	/// Shape has a hspMaster property 
	/// </summary>
	bool fHaveMaster;

	/// <summary>
	/// Shape is flipped horizontally 
	/// </summary>
	bool fFlipH;

	/// <summary>
	/// Shape is flipped vertically 
	/// </summary>
	bool fFlipV;

	/// <summary>
	/// Connector type of shape 
	/// </summary>
	bool fConnector;

	/// <summary>
	/// Shape has an anchor of some kind 
	/// </summary>
	bool fHaveAnchor;

	/// <summary>
	/// Background shape 
	/// </summary>
	bool fBackground;

	/// <summary>
	/// Shape has a shape type property
	/// </summary>
	bool fHaveSpt;
};

