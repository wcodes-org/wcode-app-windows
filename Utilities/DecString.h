# ifndef DEC_STRING_HEADER
# define DEC_STRING_HEADER

# include <Windows.h>
//# include <Math.h>

# include "PackUnpack.h"
# include "Utilities.h"

# define BYTE_BITS				8
# define DECIMAL				10

VOID DecStringA(LPSTR szDec, UINT maxLen, LPBYTE blkInt, UINT n, UINT lbT);
VOID IntBlkDecA(LPBYTE blkInt, UINT& lBD, UINT& lbT, LPSTR szDec, UINT len);

# endif // DEC_STRING_HEADER
