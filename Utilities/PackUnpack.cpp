# include "PackUnpack.h"

# define BYTE_BITS		8

//Zero the Container prior.
VOID Pack(LPBYTE arOut, UINT& lBD, UINT& lbT, UINT lbB, LPBYTE vIn)
{
	UINT i;
	for(i = 0; i < lbB/BYTE_BITS; i++)
		arOut[i] = vIn[i];
	lbT = (BYTE_BITS - lbB%BYTE_BITS) % BYTE_BITS;
	if(lbT)
	{
		lBD = i+1;
		arOut[i] = vIn[i] << lbT;
	}
	else
		lBD = i;
}

//Zero the Container prior.
VOID Unpack(LPBYTE arOut, LPBYTE arIn, UINT lBD, UINT lbT)
{
	UINT lbB = lBD*BYTE_BITS-lbT;
	UINT i;
	for(i = 0; i < lbB/BYTE_BITS; i++)
		arOut[i] = arIn[i];
	if(lbT)
		arOut[i] = arIn[i] >> lbT;
	//UINT64& num = *(UINT64 *)arOut;
	//num = 0;
	//UINT i;
	//for(i = 0; i < lBD-1; i++)
	//	num |= arIn[i] << i*BYTE_BITS;
	//if(i)
	//	num |= (UINT64)(arIn[i]) << (i*BYTE_BITS-lbT);
	//else
	//	num = *arIn >> lbT; // i = 0
}

VOID Pack(LPBYTE arOut, UINT& lBD, UINT& lbT, UINT lbB, LPBYTE arIn, UINT l)
{
	UINT iCE = 0;
	UINT iCI = 0;
	BYTE bfr = 0;
	for(UINT i = 0; i < l; i++)
	{
		BYTE val = arIn[i];
		if(iCI + lbB > BYTE_BITS)
		{
			UINT lbNxt = iCI + lbB - BYTE_BITS;
			arOut[iCE++] = bfr | (val >> lbNxt);
			bfr = (val << (BYTE_BITS-lbNxt));
			iCI = lbNxt;
		}
		else
		{
			UINT lbRmn = BYTE_BITS - (iCI + lbB);
			bfr |= val << lbRmn;
			if(lbRmn)
				iCI += lbB;
			else // == BYTE_BITS
			{
				iCI = 0;
				arOut[iCE++] = bfr;
				bfr = 0;
			}
		}
	}
	if(iCI)
	{
		arOut[iCE++] = bfr;
		lbT = BYTE_BITS-iCI;
	}
	else
		lbT = 0;
	lBD = iCE;
}

VOID Unpack(LPBYTE arOut, UINT& l, LPBYTE arIn, UINT lBD, UINT lbT, UINT lbB)
{
	UINT iCE = 0;
	UINT iCI = 0;
	UINT j = 0;
	for(UINT i = 0; iCE < lBD; i++) {
		BYTE val;
		if(iCE == lBD-1)
			if(BYTE_BITS-iCI == lbT)
				break;
		if(iCI + lbB > BYTE_BITS) {
			UINT lbNxt = iCI + lbB - BYTE_BITS;
			BYTE bfr = (arIn[iCE] << lbNxt) & ~(0xFF << lbB);
			iCE++;
		
		if(iCE == lBD)
			exit(-10);// Exception
		
			val = bfr | arIn[iCE] >> (BYTE_BITS - lbNxt);
			iCI = lbNxt;
		}
		else
		{
			UINT lbRmn = BYTE_BITS - (iCI + lbB);
			val = (arIn[iCE] >> lbRmn) & ~(0xFF << lbB);
			if(lbRmn)
				iCI += lbB;
			else// iCI : BYTE_BITS
			{
				iCE++;
				iCI = 0;
			}
		}
		arOut[j++] = val;
	}
	l = j;
//	szBase32[j] = NULL;
}
