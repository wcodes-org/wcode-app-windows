# include "WordCodeClass.h"

# define BYTE_BITS				8

# define INDEX_BITS				10

# define HEADER_SIZE			4
# define CHECKSUM_TYPE_SIZE		2
# define CHECKSUM_SIZE			8
# define TRAILING_BITS_SIZE		4			//BITS_FOR_INDEX_BITS
# define DATA_HEADER_P_SIZE		1

# define HEADER_BIT_SIZE		18

# define SPACE_CHR				L' '
# define SPACE_STR				L" "

# define ERROR_CHECKSUM_FAILED	-1

# ifndef MAX_TOKEN_LEN
# define MAX_TOKEN_LEN			1000
# endif

extern BOOL bChecksum;
extern DictionaryClass Dictionary;

WordCodeClass::WordCodeClass() {
	tIW = INDEX_BITS;//GetBitSize(N_WORDS);
}

VOID WordCodeClass::Encode(LPBYTE data, UINT lByteData, UINT lBitTrail, UINT lbBlock, UINT nBlock, UINT *code, UINT& nCode) {
	UINT iCE = 0;
	UINT iCI = 0;
	code[0] = 0;
	SetHeader(code, iCE, iCI, data, lByteData, lbBlock, nBlock);

	for(UINT i = 0; i < lByteData-1; i++)
		GetBits(code, iCE, iCI, data[i], BYTE_BITS);
	GetBits(code, iCE, iCI, data[lByteData-1] >> lBitTrail, BYTE_BITS - lBitTrail);

	if(iCI)
		nCode = iCE+1;
	else
		nCode = iCE;
}

BOOL WordCodeClass::Decode(UINT* code, UINT nCode, LPBYTE data, UINT& lByteData, UINT& lBitTrail, UINT lbBlock, UINT& nBlock) {
	UINT iCE = 0;
	UINT iCI = 0;
	GetHeader(code, nCode, iCE, iCI, lbBlock);
	nBlock = ((nCode*INDEX_BITS)-(Header.trail*lbBlock)-((iCE*INDEX_BITS)+iCI)) / lbBlock;
	UINT lb = nBlock*lbBlock;
	if(lb % BYTE_BITS) {
		lBitTrail = BYTE_BITS-lb%BYTE_BITS;
		lByteData = lb/BYTE_BITS+1;
	}
	else {
		lBitTrail = 0;
		lByteData = lb/BYTE_BITS;
	}
	for(UINT i = 0; i < lByteData; i++)
		SetBits(data[i], BYTE_BITS, code, nCode, iCE, iCI);

	if(bChecksum)
		if(Header.checksum != CRC8(data, lByteData))
			return FALSE;
	
	return TRUE;
}

VOID WordCodeClass::PrintCode(LPWSTR message, UINT &len, UINT *code, UINT n) {
	UINT i = 0;
	while(TRUE) {
		wcscat_s(message, len, OutCode(code[i]));
		if(++i == n)
			break;
		else
			wcscat_s(message, len, SPACE_STR);
	}
	len = (UINT)wcslen(message);
}

LPWSTR WordCodeClass::OutCode(UINT code) {
	return Dictionary.Token(code);
}

BOOL WordCodeClass::ReadCode(LPWSTR message, UINT len, UINT *code, UINT &n) {
	LPWSTR token = new WCHAR[MAX_TOKEN_LEN];
	UINT i = 0;
		for(UINT j = 0; j < len; j++) {
			UINT k = 0;
			while(message[j] != SPACE_CHR && message[j] != NULL)
				token[k++] = message[j++];
			token[k] = NULL;
			if(!InCode(code[i++], token))
				return FALSE;
		}
		n = i;
	return TRUE;
}

BOOL WordCodeClass::InCode(UINT& index, LPWSTR token) {
	return Dictionary.Index(index, token);
}

VOID WordCodeClass::GetHeader(UINT* code, UINT n, UINT& iCE, UINT& iCI, UINT lbBlock) {
//	SetBits(Header.header, HEADER_SIZE, code, iCE, iCI);
//	SetBits(Header.checksumType, CHECKSUM_TYPE_SIZE, code, iCE, iCI);
	if(bChecksum)
		SetBits(Header.checksum, CHECKSUM_SIZE, code, n, iCE, iCI);
	UINT lbMTB = GetBitSize(MaxNTrailBlock(lbBlock));
	SetBits(Header.trail, lbMTB, code, n, iCE, iCI);
//	SetBits(Header.dataHeaderP, DATA_HEADER_P_SIZE, code, iCE, iCI);
}
 
VOID WordCodeClass::SetHeader(UINT* code, UINT& iCE, UINT& iCI, LPBYTE data, UINT lBytD, UINT lbBlock, UINT nBlock) {
//	Header.header = 0;
//	Header.dataHeaderP = 0;

//	GetBits(code, iCE, iCI, Header.header, HEADER_SIZE);			// Header			//iCI = 4;
//	GetBits(code, iCE, iCI, Header.checksumType, CHECKSUM_TYPE_SIZE);// CheckSum Type	//iCI = 6;
	if(bChecksum) {
//		Header.checksumType = 0;
		Header.checksum = CRC8(data, lBytD);
		GetBits(code, iCE, iCI, Header.checksum, BYTE_BITS);			// CheckSum
	}
	UINT lbMTB = GetBitSize(MaxNTrailBlock(lbBlock));
	Header.trail = NTrailBlock(iCI+lbMTB/*+DATA_HEADER_P_SIZE*/, lbBlock, nBlock);
	GetBits(code, iCE, iCI, Header.trail, lbMTB);		// Trailing Zeroes
//	GetBits(code, iCE, iCI, Header.dataHeaderP, DATA_HEADER_P_SIZE);// Header Bit
}

VOID WordCodeClass::GetBits(UINT* code, UINT& iCE, UINT& iCI, BYTE data, UINT bitSz) { //BitSz < 8 - LSB data 
	UINT bfr;
	if(iCI + bitSz > WordCodeClass::tIW) {
		UINT lBitNxt = iCI + bitSz - WordCodeClass::tIW;
		bfr = data >> lBitNxt;
		code[iCE] |= bfr;
		code[++iCE] = 0;
		bfr = data & ~(0xFFFFFFFF << lBitNxt);  
		code[iCE] |= bfr << (WordCodeClass::tIW - lBitNxt);
		iCI = lBitNxt;
	}
	else {
		UINT lBitLft = WordCodeClass::tIW - (iCI + bitSz);
		code[iCE] |= (data << lBitLft);
		iCI += bitSz;
		if(iCI == WordCodeClass::tIW) {
			code[++iCE] = 0;
			iCI = 0;
		}
	}
}

VOID WordCodeClass::SetBits(BYTE& data, UINT bitSz, UINT* code, UINT n, UINT& iCE, UINT& iCI)
{
	BYTE bfr;
	if(iCI + bitSz > WordCodeClass::tIW) {
		UINT lBitNxt = iCI + bitSz - WordCodeClass::tIW;
		bfr = code[iCE] << lBitNxt;
		data = bfr & ~(0xFF << bitSz);
		iCE++;
		if(iCE < n) {
			bfr = code[iCE] >> (WordCodeClass::tIW - lBitNxt);
			data |= bfr;
		}	//iCI now contributes to lbT
		iCI = lBitNxt;
	}
	else {
		UINT lBitRmn = WordCodeClass::tIW - (iCI + bitSz);
		bfr = code[iCE] >> lBitRmn;
		data = bfr & ~(0xFF << bitSz);
		iCI += bitSz;
	}
}

UINT WordCodeClass::MaxNTrailBlock(UINT lbBlock) {
	return WordCodeClass::tIW/lbBlock;
}

UINT WordCodeClass::NTrailBlock(UINT iCI, UINT lbBlock, UINT nBlock) {
	UINT tlVb = (iCI+lbBlock*nBlock)%WordCodeClass::tIW;
	if(tlVb) {
		UINT tlb = WordCodeClass::tIW-tlVb;
		return tlb/lbBlock;
	}
	else
		return 0;
}
