# include "ModeSets.h"

# include "MainWindowClass.h"

extern MainWindowClass MainWindow;

extern BOOL bMode;
extern UINT modeType;

extern UINT in_uFormat;
extern UINT out_uFormat;

extern LPVOID tmp;
extern LPWSTR path;

UINT GetBlockSize(UINT modeGroup, UINT typeGroup)
{
	switch(modeGroup)
	{
	case GROUP_RAW:
		switch(modeType)
		{
		case TYPE_BINARY:	return BIN_BLOCK_BIT_SIZE;
			break;
		case TYPE_OCTAL:	return OCT_BLOCK_BIT_SIZE;
			break;
		case TYPE_DECIMAL:	return BIN_BLOCK_BIT_SIZE;
			break;
		case TYPE_HEX:		return HEX_BLOCK_BIT_SIZE;
			break;
		case TYPE_BASE32:	return BASE_32_BLOCK_BIT_SIZE;
			break;
		case TYPE_BASE64:	return BASE_64_BLOCK_BIT_SIZE;
			break;
		case TYPE_FILE:		return FILE_BLOCK_BIT_SIZE;
			break;
		default:			exit(0x0BAD);
		} break;
	case GROUP_TEXT:
		switch(modeType)
		{
		case TYPE_ASCII:	return ASCII_BLOCK_BIT_SIZE;
			break;
		case TYPE_ANSI:		return ANSI_BLOCK_BIT_SIZE;
			break;
		case TYPE_UNICODE:	return UNICODE_BLOCK_BIT_SIZE;
			break;
		default:			exit(0x0BAD);
		} break;
	case GROUP_NUMBER:		exit(0x0BAD);
		break;
	case GROUP_OBJECT:
		switch(modeType)
		{
		case TYPE_LATLONG:	return BIN_BLOCK_BIT_SIZE;
			break;
		default:			exit(0x0BAD);
		}
	default:				exit(0x0BAD);
	}
	return 0;
}

VOID SetModeVars(UINT modeGroup)
{
	BOOL bOutRO; //Out - ReadOnly
	switch(modeGroup)
	{
	case GROUP_RAW:
		switch(modeType)
		{
		case TYPE_FILE:
			if(!MainWindow.hWndBwsButton)
				MainWindow.AddBrowseButton();
			ShowWindow(MainWindow.hWndBwsButton, SW_SHOW);
			in_uFormat = CF_UNICODETEXT;
			out_uFormat = CF_UNICODETEXT;

			if(bMode == DECODE)
				bOutRO = FALSE;
			else
				bOutRO = TRUE;
			break;
		default:
			if(MainWindow.hWndBwsButton)
				ShowWindow(MainWindow.hWndBwsButton, SW_HIDE);
			in_uFormat = CF_TEXT;
			out_uFormat = CF_UNICODETEXT;
			bOutRO = TRUE;
		} break;
	case GROUP_TEXT:
		switch(modeType)
		{
		case TYPE_ASCII:
		case TYPE_ANSI:
			in_uFormat = CF_TEXT;
			out_uFormat = CF_TEXT;
			bOutRO = true;
			break;
		default:
			in_uFormat = CF_UNICODETEXT;
			out_uFormat = CF_UNICODETEXT;
			bOutRO = true;
		} break;
	case GROUP_NUMBER:
		in_uFormat = CF_UNICODETEXT;
		out_uFormat = CF_UNICODETEXT;
		bOutRO = true;
		break;
	case GROUP_OBJECT:
		in_uFormat = CF_UNICODETEXT;
		out_uFormat = CF_UNICODETEXT;
		bOutRO = true;
	}
	if(bOutRO) {
		EnableWindow(MainWindow.hWndOutPstButton, FALSE);
		SendMessage(MainWindow.hWndOutBox, EM_SETREADONLY, TRUE, 0);
	}
	else {
		EnableWindow(MainWindow.hWndOutPstButton, TRUE);
		SendMessage(MainWindow.hWndOutBox, EM_SETREADONLY, FALSE, 0);
	}
}

VOID OutMode() {
	GetWindowTextA(MainWindow.hWndOutBox, (LPSTR)tmp, MAX_DATA_LEN);
	if(*((LPSTR)tmp) == NULL) {
		EnableWindow(MainWindow.hWndOutClrButton, FALSE);
		EnableWindow(MainWindow.hWndOutCpyButton, FALSE);
	}
	else {
		EnableWindow(MainWindow.hWndOutClrButton, TRUE);
		EnableWindow(MainWindow.hWndOutCpyButton, TRUE);
	}
}
