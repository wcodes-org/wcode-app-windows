# include "DecString.h"

VOID DecStringA(LPSTR szDec, UINT maxLen, LPBYTE blkInt, UINT lBD, UINT lbT)
{
	UINT64 num = 0;
	Unpack((LPBYTE)&num, blkInt, lBD, lbT);
	//_itoa_s(num, szDec, maxLen, DECIMAL);
	_i64toa_s(num, szDec, maxLen, DECIMAL);
}

VOID IntBlkDecA(LPBYTE blkInt, UINT& lBD, UINT& lbT, LPSTR szDec, UINT len)
{
	UINT64 num = _atoi64(szDec);
		//UINT num = atoi(sDec);
	Pack(blkInt, lBD, lbT, GetBitSize(num), (LPBYTE)&num);
}
