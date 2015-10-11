# include "Utilities.h"

# define LONG_BITS		32
# define LONGLONG_BITS	64

UINT Random(UINT min, UINT max)
{
	return min+rand()%(max-min+1);
}

UINT RandomFz(UINT base, UINT fuzz)
{
	return Random((base > fuzz)? base-fuzz : 0, base+fuzz);
}

BOOL SetXFileTime(LPCWSTR fileName, CONST FILETIME* ptFC, CONST FILETIME* ptFA, CONST FILETIME* ptFM)
{
	BOOL bStatus = true;
	HANDLE hFile;
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(!SetFileTime(hFile, ptFC, ptFA, ptFM))
		bStatus = false;
	CloseHandle(hFile);
	return bStatus;
}

/* 8-bit CRC value using polynomial  X^8 + X^5 + X^4 + 1 */
# define POLYVAL 0x8C
BYTE CRC8(LPBYTE data, UINT len)
{
	BYTE CRC = 0;
	for(UINT i = 0; i < len; i++)
	{
		BYTE c;
		BYTE x = data[i];
		c = CRC;
		for(UINT j = 0; j < 8; j++)
		{
			if((c ^ x) & 1)
				c = (c >> 1 ) ^ POLYVAL;
			else
				c >>= 1;
			x >>= 1;
		}
		CRC = c;
	}
	return CRC;
}
/*
UINT GetBitSize(UINT max)
{
	DOUBLE bit = log((float)max)/log((float)2);
	return ((UINT)ceil(bit));
}
*/
UINT GetBitSize(UINT val)
{
	UINT i;
	for(i = 0; i < LONG_BITS; i++)
	{
		if(0x80000000 & (val<<i))
			break;
	}
	return LONG_BITS-i;
}

UINT GetBitSize(UINT64 val)
{
	UINT i;
	for(i = 0; i < LONGLONG_BITS; i++)
	{
		if(0x8000000000000000 & (val<<i))
			break;
	}
	return LONGLONG_BITS-i;
}

UINT CeilDiv(UINT dividend, UINT divisor)
{
	//return (1 + ((dividend - 1) / divisor)); //:To avoid Overflo; (dividend + divisor - 1) / y;
	UINT result = dividend/divisor;
	if(dividend % divisor)
		result++;
	return result;
}
