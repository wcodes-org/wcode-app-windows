# ifndef UTILITIES_HEADER
# define UTILITIES_HEADER

# include <Windows.h>
# include <Math.h>

UINT Random(UINT min, UINT max);
UINT RandomFz(UINT base, UINT fuzz);
BOOL SetXFileTime(LPCWSTR fileName, CONST FILETIME* ptFC, CONST FILETIME* ptFA, CONST FILETIME* ptFM);

BYTE CRC8(LPBYTE data, UINT len);
UINT GetBitSize(UINT val);
UINT GetBitSize(UINT64 val);

UINT CeilDiv(UINT dividend, UINT divisor);

# endif // UTILITIES_HEADER
