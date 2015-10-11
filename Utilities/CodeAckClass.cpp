# include "CodeAckClass.h"

CodeAckClass::CodeAckClass(LPCSTR sCT, CONST UINT lCT, CONST UINT lbB):\
	sCodeTable(sCT), lCodeTable(lCT), lbB(lbB) {}

VOID CodeAckClass::StringA(LPSTR szCode, LPBYTE arCode, UINT lBD, UINT lbT)
{
	UINT lCode;
	Unpack((LPBYTE)szCode, lCode, arCode, lBD, lbT, lbB);
	TransformA((LPBYTE)szCode, lCode);
	szCode[lCode] = NULL;
}

VOID CodeAckClass::TransformA(LPBYTE sCode, UINT lCode)
{
	for(UINT i = 0; i < lCode; i++)
		sCode[i] = sCodeTable[sCode[i]];
}

VOID CodeAckClass::ArrayA(LPBYTE arCode, UINT& lBD, UINT& lbT, LPSTR sCode, UINT lCode)
{
	NormalizeA((LPBYTE)sCode, lCode);
	Pack(arCode, lBD, lbT, lbB, (LPBYTE)sCode, lCode);
}

VOID CodeAckClass::NormalizeA(LPBYTE sCode, UINT lCode)
{
	for(UINT i = 0; i < lCode; i++)
		sCode[i] = Index(sCode[i]);
}

UINT CodeAckClass::Index(UCHAR c)
{
	for(UINT j = 0; j < lCodeTable; j++)
	{
		if(sCodeTable[j] == c)
			return j;
	}
	exit(ERROR_RATIONALIZE_EXCEPTION);
}
