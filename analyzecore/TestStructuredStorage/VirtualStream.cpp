#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include <math.h>


VirtualStream::VirtualStream()
{
}


VirtualStream::VirtualStream(shared_ptr<AbstractFat> spFat, unsigned long startSector, __int64 sizeOfStream, wstring name)
{
	_spFat = spFat;
	_length = sizeOfStream;
	_name = name;
	if (startSector == Common::SectorId::ENDOFCHAIN || _length == 0)
	{
		return;
	}

	Init(startSector);
}

VirtualStream::~VirtualStream()
{
}

unsigned short VirtualStream::ReadUInt16()
{
	unsigned char byteArray[2] = { 0 };
	Read(byteArray, 2);
	return Common::bytes2T<unsigned short>(byteArray);
}

unsigned long VirtualStream::ReadUInt32()
{
	unsigned char byteArray[4] = { 0 };
	Read(byteArray, 4);
	return Common::bytes2T<unsigned long>(byteArray);
}

int VirtualStream::Read(unsigned char* p, size_t size)
{
	return Read(p, 0, size);
}

int VirtualStream::Read(unsigned char* p, int offset, size_t size)
{
	return Read(p, offset, size, _position);
}

int VirtualStream::Read(char* p, int offset, size_t size)
{
	return Read((unsigned char*)p, offset, size, _position);
}

/// <summary>
/// Reads bytes from the virtual stream.
/// </summary>
/// <param name="array">Array which will contain the read bytes after successful execution.</param>
/// <param name="offset">Offset in the array.</param>
/// <param name="count">Number of bytes to read.</param>
/// <param name="position">Start position in the stream.</param>
/// <returns>The total number of bytes read into the buffer. 
/// This might be less than the number of bytes requested if that number 
/// of bytes are not currently available, or zero if the end of the stream is reached.</returns>
int VirtualStream::Read(unsigned char* p, int offset, size_t size, __int64 position)
{
	if (size < 1 || position < 0 || offset < 0)
	{
		return 0;
	}

	if (position + size > _length)
	{
		size = _length - position;
		if (size < 1)
			return 0;
	}

	_position = position;

	int sectorInChain = (int)(position / _spFat->GetSectorSize());
	int bytesRead = 0;
	int totalBytesRead = 0;
	int positionInArray = offset;

	// Read part in first relevant sector
	int positionInSector = (int)(position % _spFat->GetSectorSize());
	_spFat->SeekToPositionInSector(_sectors[sectorInChain], positionInSector);
	int bytesToReadInFirstSector = (size > _spFat->GetSectorSize() - positionInSector) 
		? (_spFat->GetSectorSize() - positionInSector) : size;

	bytesRead = _spFat->UncheckedRead(p, positionInArray, bytesToReadInFirstSector);
	// Update variables
	_position += bytesRead;
	positionInArray += bytesRead;
	totalBytesRead += bytesRead;
	sectorInChain++;
	if (bytesRead != bytesToReadInFirstSector)
	{
		return totalBytesRead;
	}

	// Read full sectors
	while (totalBytesRead + _spFat->GetSectorSize() < size)
	{
		_spFat->SeekToPositionInSector(_sectors[sectorInChain], 0);
		bytesRead = _spFat->UncheckedRead(p, positionInArray, _spFat->GetSectorSize());

		// Update variables
		_position += bytesRead;
		positionInArray += bytesRead;
		totalBytesRead += bytesRead;
		sectorInChain++;
		if (bytesRead != _spFat->GetSectorSize())
		{
			return totalBytesRead;
		}
	}

	// Finished reading
	if (totalBytesRead >= size)
	{
		return totalBytesRead;
	}

	// Read remaining part in last relevant sector
	_spFat->SeekToPositionInSector(_sectors[sectorInChain], 0);

	bytesRead = _spFat->UncheckedRead(p, positionInArray, size - totalBytesRead);

	// Update variables
	_position += bytesRead;
	positionInArray += bytesRead;
	totalBytesRead += bytesRead;

	return totalBytesRead;
}

__int64 VirtualStream::Seek(__int64 offset, int way)
{
	switch (way)
	{
	case SEEK_SET:
		_position = offset;
		break;
	case SEEK_CUR:
		_position += offset;
		break;
	case SEEK_END:
		_position = _length - offset;
		break;
	default:
		break;
	}

	if (_position < 0)
	{
		_position = 0;
	}
	else if (_position > _length)
	{
		_position = _length;
	}

	return _position;
}

void VirtualStream::Init(unsigned long startSector)
{
	_sectors = _spFat->GetSectorChain(startSector, (unsigned __int64)ceil((double)_length / _spFat->GetSectorSize()), _name);
	CheckConsistency();
}

void VirtualStream::CheckConsistency()
{
	if (((unsigned __int64)_sectors.size()) != ceil((double)_length / _spFat->GetSectorSize()))
	{
		//throw new ChainSizeMismatchException(_name);
	}
}
