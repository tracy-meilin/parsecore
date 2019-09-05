#pragma once

class ShapeType
{
public:
	ShapeType();
	~ShapeType();

public:
	/// <summary>
	/// This string describes a sequence of commands that define the shape’s path.<br/>
	/// This string describes both the pSegmentInfo array and pVertices array in the shape’s geometry properties.
	/// </summary>
	wstring Path;


	/// <summary>
	/// This specifies a list of formulas whose calculated values are referenced by other properties. <br/>
	/// Each formula is listed on a separate line. Formulas are ordered, with the first formula having index 0. <br/>
	/// This section can be omitted if the shape doesn’t need any guides.
	/// </summary>
	vector<string> m_vecFormulas;


	/// <summary>
	/// Specifies a comma-delimited list of parameters, or adjustment values, 
	/// used to define values for a parameterized formula. <br/>
	/// These values represent the location of an adjust handle and may be 
	/// referenced by the geometry of an adjust handle or as a parameter guide function.
	/// </summary>
	wstring AdjustmentValues;


	/// <summary>
	/// These values specify the location of connection points on the shape’s path. <br/>
	/// The connection points are defined by a string consisting of pairs of x and y values, delimited by commas.
	/// </summary>
	wstring ConnectorLocations;


	wstring ConnectorType;

	bool PreferRelative;

	bool ExtrusionOk = false;

	/// <summary>
	/// This section specifies the properties of each adjust handle on the shape. <br/>
	/// One adjust handle is specified per line. <br/>
	/// The properties for each handle correspond to values of the ADJH structure 
	/// contained in the pAdjustHandles array in the shape’s geometry properties.
	/// </summary>
	vector<shared_ptr<Handle>> m_vecHandles;


	/// <summary>
	/// Specifies one or more text boxes inscribed inside the shape. <br/>
	/// A textbox is defined by one or more sets of numbers specifying (in order) the left, top, right, and bottom points of the rectangle. <br/>
	/// Multiple sets are delimited by a semicolon. <br/>
	/// If omitted, the text box is the same as the geometry’s bounding box.
	/// </summary>
	wstring TextboxRectangle;


	/// <summary>
	/// 
	/// </summary>
	bool ShapeConcentricFill;

	/// <summary>
	/// Specifies what join style the shape has. <br/>
	/// Since there is no UI for changing the join style, 
	/// all shapes of this type will always have the specified join style.
	/// </summary>
	JoinStyleSpace::JoinStyle Joins;

	/// <summary>
	/// Specifies the (x,y) coordinates of the limo stretch point.<br/>
	/// Some shapes that have portions that should be constrained to a fixed aspect ratio, are designed with limo-stretch to keep those portions at the fixed aspect ratio.<br/>
	/// </summary>
	wstring Limo;

	/// <summary>
	/// Associated with each connection site, there is a direction which specifies at what angle elbow and curved connectors should attach to it<br/>
	/// </summary>
	wstring ConnectorAngles;

	/// <summary>
	/// Specifies if a shape of this type is filled by default
	/// </summary>
	bool Filled = true;

	/// <summary>
	/// Specifies if a shape of this type is stroked by default
	/// </summary>
	bool Stroked = true;

	/// <summary>
	/// Speicfies the locked properties of teh shape.
	/// By default nothing is locked.
	/// </summary>
	shared_ptr<ProtectionBooleans> _spLock;// = new ProtectionBooleans(0);

	bool LockShapeType;

	bool TextPath;

	bool TextKerning;

	unsigned long TypeCode;
};

