# include "Clipboard.h"

BOOL CopyToClpBrd(LPVOID data, UINT len, UINT uFormat)
{
	BOOL bStatus = false;
	if(OpenClipboard(NULL))
	{
		EmptyClipboard();
		HGLOBAL hMem = NULL;
		switch(uFormat)
		{
		case CF_TEXT:
			{
			hMem = GlobalAlloc(GMEM_DDESHARE, len);
			LPTSTR ptxt = (LPTSTR)GlobalLock(hMem);
			strcpy_s((char *)ptxt, len, (LPSTR)data);
			} break;
		case CF_UNICODETEXT:
			{
			hMem = GlobalAlloc(GMEM_DDESHARE, len*2);
			LPWSTR ptxt = (LPWSTR)GlobalLock(hMem);
			wcscpy_s((LPWSTR)ptxt, len, (LPWSTR)data);
			} break;
		}
		if(hMem)
		{
			GlobalUnlock(hMem);
			bStatus = (SetClipboardData(uFormat, hMem) != NULL);
		}
		CloseClipboard();
	}
	return bStatus;
}

BOOL PasteFrmClpBrd(LPVOID data, UINT len, UINT uFormat)
{
	BOOL bStatus = false;
	if(OpenClipboard(NULL))
	{
		HGLOBAL hMem = NULL;
		hMem = GetClipboardData(uFormat);
		LPVOID str = GlobalLock(hMem);
		switch(uFormat)
		{
		case CF_TEXT:
			strcpy_s((LPSTR)data, len, (LPSTR)str);
			break;
		case CF_UNICODETEXT:
			wcscpy_s((LPWSTR)data, len, (LPWSTR)str);
			break;
		}
		if(hMem)
			GlobalUnlock(hMem);
		CloseClipboard();
	}
	return bStatus;
}
