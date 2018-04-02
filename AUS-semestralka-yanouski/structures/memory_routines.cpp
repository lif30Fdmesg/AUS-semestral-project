#include "memory_routines.h"

namespace structures {
	byte & MemoryRoutines::byteSet(byte & B)
	{
		
		return B = MAX_BYTE;
	}
	byte & MemoryRoutines::byteReset(byte & B)
	{
		
		return B = 0;
	}
	byte &MemoryRoutines::byteXOR(byte & B)
	{

		B ^= 255;
		return B;
	}

	byte & MemoryRoutines::byteSHL(byte & B)
	{
		
		return B <<= 1;
	}
	byte & MemoryRoutines::byteSHR(byte & B)
	{
		
		return B >>= 1;
	}
	bool MemoryRoutines::byteNthBitGet(byte & B, int n)
	{
		return (B >> n) & 1;
		
	}

	byte & MemoryRoutines::byteNthBitTo0(byte & B, int n)
	{
		return B = B ^ (1 << n);
	}

	byte & MemoryRoutines::byteNthBitTo1(byte & B, int n)
	{
		return B = B | (1 << n);
	}

	byte & MemoryRoutines::byteNthBitToggle(byte & B, int n)
	{
		return B = (byteNthBitGet(B, n)) ? byteNthBitTo0(B, n) : byteNthBitTo1(B, n);
	}

	MemoryRoutines::MemoryRoutines()
	{
	}

}
