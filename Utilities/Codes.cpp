# include "Codes.h"

# define ERROR_EXCEPTION

UINT Find(LPCSTR sCode, UINT lCode, LPCSTR table, UINT lTable);

UINT RationalizeA(UINT type, LPSTR sCode, UINT lCode) // To standard form
{
	switch(type)
	{
	case TYPE_BINARY:
		return Find(sCode, lCode, BASE2_TABLE, sizeof BASE2_TABLE);
	case TYPE_OCTAL:
		return Find(sCode, lCode, BASE8_TABLE, sizeof BASE8_TABLE);
	case TYPE_DECIMAL:	
		return Find(sCode, lCode, BASE10_TABLE, sizeof BASE10_TABLE);
	case TYPE_HEX:
		return Find(sCode, lCode, BASE16_TABLE, sizeof BASE16_TABLE);
	case TYPE_BASE32:
		return Find(sCode, lCode, BASE32_TABLE, sizeof BASE32_TABLE);
	case TYPE_BASE64:
		return Find(sCode, lCode, BASE64_TABLE, sizeof BASE64_TABLE);
	default:
		exit(-54523);
	}
}

UINT Find(LPCSTR sCode, UINT lCode, LPCSTR table, UINT lTable)
{
	for(UINT i = 0; i < lCode; i++)
	{
		UINT j;
		for(j = 0; j < lTable; j++)
			if(sCode[i] == table[j])
				break;
		if(j == lTable)
			return i;
	}
	return -1;
}
