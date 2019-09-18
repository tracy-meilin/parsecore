#pragma once

class PptFileFormat_API ProtectionBooleans
{
public:
	ProtectionBooleans();
	ProtectionBooleans(unsigned long entryOperand);
	~ProtectionBooleans();

public:

	bool fLockAgainstGrouping;
	bool fLockAdjustHandles;
	bool fLockText;
	bool fLockVertices;
	bool fLockCropping;
	bool fLockAgainstSelect;
	bool fLockPosition;
	bool fLockAspectRatio;
	bool fLockRotation;
	bool fLockAgainstUngrouping;

	bool fUsefLockAgainstGrouping;
	bool fUsefLockAdjustHandles;
	bool fUsefLockText;
	bool fUsefLockVertices;
	bool fUsefLockCropping;
	bool fUsefLockAgainstSelect;
	bool fUsefLockPosition;
	bool fUsefLockAspectRatio;
	bool fUsefLockRotation;
	bool fUsefLockAgainstUngrouping;
};

