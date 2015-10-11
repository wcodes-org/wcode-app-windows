# ifndef CODEACK_HEADER
# define CODEACK_HEADER

# define ERROR_RATIONALIZE_EXCEPTION	0x0ec1

# include <Windows.h>
# include "PackUnpack.h"

class CodeAckClass
{
private:
	LPCSTR sCodeTable;
	CONST UINT lCodeTable;
	CONST UINT lbB;
public:
	CodeAckClass(LPCSTR sCT, CONST UINT lCT, CONST UINT lbB);
	VOID StringA(LPSTR szCode, LPBYTE arCode, UINT lBD, UINT lbT);
	inline VOID TransformA(LPBYTE sCode, UINT lCode);
	VOID ArrayA(LPBYTE arCode, UINT& lBD, UINT& lbT, LPSTR sCode, UINT lCode);
	inline VOID NormalizeA(LPBYTE sCode, UINT lCode);
	inline UINT Index(UCHAR c);
};

# endif // CODEACK_HEADER
