# ifndef WORDCODE_CLASS_HEADER
# define WORDCODE_CLASS_HEADER

# include <Windows.h>

# include "Utilities\Utilities.h"
# include "Utilities\DictionaryClass.h"
# include "Utilities\AlphaTreeClass.h"
# include "Utilities\SuggestClass.h"

struct HeaderStruct
{
//	BYTE header;
//	BYTE checksumType;
	BYTE checksum;
	BYTE trail;
//	BYTE dataHeaderP;
};

class WordCodeClass
{
private:
//	UINT tN;
	UINT tIW;	// Trail Index Width~~
	HeaderStruct Header;

	UINT MaxNTrailBlock(UINT lbBlock);
	UINT NTrailBlock(UINT lbBlock, UINT nBlock, UINT iCI);

public:
	WordCodeClass();
	VOID Encode(LPBYTE data, UINT lBytD, UINT lBitT, UINT lbBlock, UINT nBlock, UINT *code, UINT& n);//LPBYTE data, UINT lBytD, UINT lBitT, UINT* code, UINT& n);
	BOOL Decode(UINT* code, UINT n, LPBYTE data, UINT& lBD, UINT& lbT, UINT lbBlock, UINT& nBlock);
	VOID PrintCode(LPWSTR message, UINT &len, UINT* code, UINT n);
	LPWSTR OutCode(UINT code);
	BOOL ReadCode(LPWSTR message, UINT len, UINT *code, UINT &n);
	BOOL InCode(UINT&index, LPWSTR token);
	VOID SetHeader(UINT* code, UINT& iCE, UINT& iCI, LPBYTE data, UINT lBytD, UINT lbBlock, UINT nBlock);
	VOID GetHeader(UINT* code, UINT n, UINT& iCE, UINT& iCI, UINT lbBlock);
	VOID GetBits(UINT* code, UINT& iCE, UINT& iCI, BYTE data, UINT bitSz);
	VOID SetBits(BYTE& data, UINT bitSz, UINT* code, UINT n, UINT& iCE, UINT& iCI);
};

# endif // WORDCODE_CLASS_HEADER
