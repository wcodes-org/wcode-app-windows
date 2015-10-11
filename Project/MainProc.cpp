# include "MainProc.h"

# include "Resource.h"

# include "..\\Utilities\\SettingsClass.h"
# include "..\\Utilities\\SplashWindowClass.h"
# include "..\\Utilities\\CodeAckClass.h"
# include "..\\Utilities\\Codes.h"
# include "..\\Utilities\\DecString.h"
# include "..\\Utilities\\LatLngClass.h"
# include "..\\Utilities\\Clipboard.h"
# include "..\\Utilities\\FileIO.h"
# include "ModeSets.h"
# include "MainWindowClass.h"
# include "WordCodeClass.h"
# include "..\\Utilities\\PackUnpack.h"

extern MainWindowClass		MainWindow;
extern SettingsClass		Settings;
extern SplashWindowClass	SplashWindow;
extern WordCodeClass		WordCode;
extern SuggestClass			Suggest;

extern LPVOID tmp;

extern LPVOID data;
extern UINT dataSize;

extern LPWSTR path;
extern LPVOID string;
extern LPWSTR message;

extern UINT* code;
extern UINT nCode;

extern BOOL bChecksum;
extern UINT modeGroup;
extern UINT modeType;
extern BOOL bMode;

UINT in_uFormat;
UINT out_uFormat;

# define S_DATA_CHECKSUM_BAD	L"Data Checksum Mismatch"
# define S_TOKEN_ERROR			L"Wrong Token used"

LPWSTR szError[] = {L"Invalid Binary String",
					L"Invalid Octal String",
					L"Invalid Decimal String",
					L"Invalid Hex String",
					L"Invalid Base32 String",
					L"Invalid Base64 String"};

# define S_WCODE_MESSAGE		L"WCode"

# define S_ENCODE				L"Encode"
# define S_DECODE				L"Decode"

BOOL X1(UINT& lTmp, UINT type);

LRESULT CALLBACK MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		PostQuitMessage(WM_QUIT);
		return 0;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case TEXT_IN_WINDOW_ID:
				//if(HIWORD(wParam) == EN_CHANGE)
				GetWindowTextA(MainWindow.hWndInBox, (LPSTR)tmp, dataSize);
				if(*((LPSTR)tmp) == NULL) {
					EnableWindow(MainWindow.hWndInClrButton, FALSE);
					EnableWindow(MainWindow.hWndInCpyButton, FALSE);
					EnableWindow(MainWindow.hWndCnvButton, FALSE);
				}
				else {
					EnableWindow(MainWindow.hWndInClrButton, TRUE);
					EnableWindow(MainWindow.hWndInCpyButton, TRUE);
					EnableWindow(MainWindow.hWndCnvButton, TRUE);
				}
				break;
			case TEXT_OUT_WINDOW_ID:
				OutMode();
				break;
			case OPTIONS_BUTTON_ID:

				break;
			case CSM_CHECK_WINDOW_ID:
				if(bChecksum) {
					SendMessage(MainWindow.hWndCsmButton, WM_SETTEXT, NULL, (LPARAM)S_CHECKSUM_F);
					bChecksum = FALSE;
				}
				else {
					SendMessage(MainWindow.hWndCsmButton, WM_SETTEXT, NULL, (LPARAM)S_CHECKSUM_T);
					bChecksum = TRUE;
				}
				break;
			case ABOUT_BUTTON_ID:
				SplashWindow.BeginFade();
				SplashWindow.Show();
				break;
			case SAVE_MODE_BUTTON_ID:
				Settings.SetValue(ENCODE_O_DECODE, bMode);
				Settings.SetValue(CHECKSUM, bChecksum);
				Settings.SetValue(MODE_GROUP, modeGroup);
				Settings.SetValue(MODE_TYPE, modeType);
				Settings.Save();
				break;
			case BROWSE_BUTTON_ID:
				if(bMode == ENCODE) {
					BrowseFileOpenDialog(MainWindow.hWnd, path);
					SetWindowText(MainWindow.hWndInBox, path);
				}
				else {
					BrowseFileSaveDialog(MainWindow.hWnd, path);
					SetWindowText(MainWindow.hWndOutBox, path);
				}
				break;
			case CONVERT_BUTTON_ID:
				if(bMode == ENCODE)
				{
				UINT lBD;
				UINT lbT;
				UINT lbBlock;
				UINT nBlock;
				switch(modeGroup)
				{
				case GROUP_RAW:
					switch(modeType)
					{
					case TYPE_BINARY:
						{
						UINT lTmp;
						if(!X1(lTmp, TYPE_BINARY))
							return 0;
						CodeAckClass codeAck(BASE2_TABLE, (UINT)sizeof(BASE2_TABLE), BIN_BLOCK_BIT_SIZE);
						codeAck.ArrayA((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = BIN_BLOCK_BIT_SIZE;
						nBlock = lTmp;
						} break;
					case TYPE_OCTAL:
						{
						UINT lTmp;
						if(!X1(lTmp, TYPE_OCTAL))
							return 0;
						CodeAckClass codeAck(BASE8_TABLE, (UINT)sizeof(BASE8_TABLE), OCT_BLOCK_BIT_SIZE);
						codeAck.ArrayA((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = OCT_BLOCK_BIT_SIZE;
						nBlock = lTmp;
						} break;
					case TYPE_DECIMAL:
						{
						UINT lTmp;
						if(!X1(lTmp, TYPE_DECIMAL))
							return 0;
						IntBlkDecA((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = BIN_BLOCK_BIT_SIZE;
						nBlock = lBD*BYTE_BITS-lbT;
						} break;
					case TYPE_HEX:
						{
						UINT lTmp;
						if(!X1(lTmp, TYPE_HEX))
							return 0;
						CodeAckClass codeAck(BASE16_TABLE, (UINT)sizeof(BASE16_TABLE), HEX_BLOCK_BIT_SIZE);
						codeAck.ArrayA((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = HEX_BLOCK_BIT_SIZE;
						nBlock = lTmp;
						} break;
					case TYPE_BASE32:
						{
						UINT lTmp;
						if(!X1(lTmp, TYPE_BASE32))
							return 0;
						CodeAckClass codeAck(BASE32_TABLE, (UINT)sizeof(BASE32_TABLE), BASE_32_BLOCK_BIT_SIZE);
						codeAck.ArrayA((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = BASE_32_BLOCK_BIT_SIZE;
						nBlock = lTmp;
						} break;
					case TYPE_BASE64:
						{
						UINT lTmp;
						if(!X1(lTmp, TYPE_BASE64))
							return 0;
						CodeAckClass codeAck(BASE64_TABLE, (UINT)sizeof(BASE64_TABLE), BASE_64_BLOCK_BIT_SIZE);
						codeAck.ArrayA((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = BASE_64_BLOCK_BIT_SIZE;
						nBlock = lTmp;
						} break;
					case TYPE_FILE:
						GetWindowText(MainWindow.hWndInBox, path, MAX_PATH_LEN);
						LoadData((LPBYTE &)data, dataSize, lBD, path);
						lbT = 0;
						lbBlock = FILE_BLOCK_BIT_SIZE;
						nBlock = lBD;
						break;
					} break;
				case GROUP_TEXT:
					switch(modeType)
					{
					case TYPE_ASCII:
						GetWindowTextA(MainWindow.hWndInBox, (LPSTR)tmp, dataSize);
						lbBlock = ASCII_BLOCK_BIT_SIZE;
						nBlock = (UINT)(strlen((LPSTR)tmp));
						Pack((LPBYTE)data, lBD, lbT, lbBlock, (LPBYTE)tmp, nBlock);
						break;
					case TYPE_ANSI:
						GetWindowTextA(MainWindow.hWndInBox, (LPSTR)data, dataSize);
						lbT = 0;
						lBD = (UINT)(strlen((LPSTR)data));
						lbBlock = ANSI_BLOCK_BIT_SIZE;
						nBlock = lBD;
						break;
					case TYPE_UNICODE:
						GetWindowTextW(MainWindow.hWndInBox, (LPWSTR)data, dataSize);
						lbT = 0;
						lBD = (UINT)(wcslen((LPWSTR)data)*2);
						lbBlock = UNICODE_BLOCK_BIT_SIZE;
						nBlock = lBD;
						break;
					} break;
				case GROUP_NUMBER:
					{
					GetWindowTextA(MainWindow.hWndInBox, (LPSTR)data, dataSize);
					lBD = (UINT)(strlen((LPSTR)data));
/*					switch(SendMessage(MainWindow.hWndLeadCheck, BM_GETCHECK, 0, 0))
					{
					case BST_UNCHECKED:
						{
						
						} break;
					case BST_CHECKED:
						{
						UINT lZero = 0;
						for(UINT i = 0; i < lBD; i++)
							if(((LPSTR)data)[i] == '0')
								lZero++;
							else
								break;
						} break;
					}
*/
					__int64 number;
					number = _atoi64((LPSTR)data);
//					UINT i;
//					packInt((LPBYTE)data, lBD, i, number);
					} break;
				case GROUP_OBJECT:
					switch(modeType)
					{
					case TYPE_LATLONG:
						{
						GetWindowTextA(MainWindow.hWndInBox, (LPSTR)tmp, dataSize);
						UINT lTmp = (UINT)(strlen((LPSTR)tmp));
						LatLngClass LatLng;
						LatLng.Encode((LPBYTE)data, lBD, lbT, (LPSTR)tmp, lTmp);
						lbBlock = BIN_BLOCK_BIT_SIZE;
						nBlock = lBD*BYTE_BITS-lbT;
						} break;
					} break;
				}
				WordCode.Encode(LPBYTE(data), lBD, lbT, lbBlock, nBlock, code, nCode);
				message[0] = NULL;
				UINT lMsg = MAX_WCODE_LEN;
				WordCode.PrintCode(message, lMsg, code, nCode);
				SetWindowText(MainWindow.hWndOutBox,
# if defined SIMUL_EXAMPLE
				L"Cat Apple Mango Tomato"
# elif defined SIMUL_EXAMPLE_CSM
				L"Cat Apple Mango Tomato Ant"
# else
				message
# endif
				);
				SendMessage(MainWindow.hWndOutBox, WM_PRINTCLIENT, NULL, NULL);
				OutMode();
				} //break;

/*DECODE*/		else
				{
				ShowWindow(MainWindow.hWndSugBox, SW_HIDE);
				ShowWindow(MainWindow.hWndOutBox, SW_SHOW);

				UINT lBD;
				UINT lbT;
				UINT lbBlock;
				UINT nBlock;
				GetWindowText(MainWindow.hWndInBox, message, MAX_WCODE_LEN);
				if(WordCode.ReadCode(message, (UINT)wcslen(message), code, nCode))
				{
					lbBlock = GetBlockSize(modeGroup, modeType);
					if(WordCode.Decode(code, nCode, (LPBYTE)tmp, lBD, lbT, lbBlock, nBlock))
					{
						switch(modeGroup)
						{
						case GROUP_RAW:
							switch(modeType)
							{
							case TYPE_BINARY:
								{
								CodeAckClass codeAck(BASE2_TABLE, (UINT)sizeof(BASE2_TABLE), BIN_BLOCK_BIT_SIZE);
								codeAck.StringA((LPSTR)data, (LPBYTE)tmp, lBD, lbT);
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								} break;
							case TYPE_OCTAL:
								{
								CodeAckClass codeAck(BASE8_TABLE, (UINT)sizeof(BASE8_TABLE), OCT_BLOCK_BIT_SIZE);
								codeAck.StringA((LPSTR)data, (LPBYTE)tmp, lBD, lbT);
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								} break;
							case TYPE_DECIMAL:
								{
								DecStringA((LPSTR)data, MAX_DATA_LEN, (LPBYTE)tmp, lBD, lbT);
								SetWindowTextA(MainWindow.hWndOutBox,
# ifdef SIMUL_EXAMPLE
									"9801234567"
# else
									(LPSTR)data
# endif
								);
								} break;
							case TYPE_HEX:
								{
								CodeAckClass codeAck(BASE16_TABLE, (UINT)sizeof(BASE16_TABLE), HEX_BLOCK_BIT_SIZE);
								codeAck.StringA((LPSTR)data, (LPBYTE)tmp, lBD, (lbT==0? FALSE : TRUE));
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								} break;
							case TYPE_BASE32:
								{
								CodeAckClass codeAck(BASE32_TABLE, (UINT)sizeof(BASE32_TABLE), BASE_32_BLOCK_BIT_SIZE);
								codeAck.StringA((LPSTR)data, (LPBYTE)tmp, lBD, lbT);
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								} break;
							case TYPE_BASE64:
								{
								CodeAckClass codeAck(BASE64_TABLE, (UINT)sizeof(BASE64_TABLE), BASE_64_BLOCK_BIT_SIZE);
								codeAck.StringA((LPSTR)data, (LPBYTE)tmp, lBD, lbT);
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								} break;
							case TYPE_FILE:
								GetWindowText(MainWindow.hWndOutBox, path, MAX_PATH_LEN);
								WriteData((LPBYTE &)tmp, lBD, path);
								break;
							} break;
						case GROUP_TEXT:
							switch(modeType)
							{
							case TYPE_ASCII:
								UINT l;
								Unpack((LPBYTE)data, l, (LPBYTE)tmp, lBD, lbT, ASCII_BLOCK_BIT_SIZE);
								((LPSTR)data)[l] = NULL;
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								break;
							case TYPE_ANSI:
								((LPSTR)tmp)[lBD] = NULL;
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)tmp);
								break;
							default:
								((LPWSTR)tmp)[lBD/2] = NULL;
								SetWindowTextW(MainWindow.hWndOutBox, (LPWSTR)tmp);
							} break;
						case GROUP_NUMBER:
							break;
						case GROUP_OBJECT:
							switch(modeType)
							{
							case TYPE_LATLONG:
								{
								LatLngClass LatLng;
								LatLng.Decode((LPSTR)data, (LPBYTE)tmp, lBD, lbT);
								SetWindowTextA(MainWindow.hWndOutBox, (LPSTR)data);
								} break;
							} break;
						}
					}
					else
					{
# if defined SIMUL_EXAMPLE_CSM
						DecStringA((LPSTR)data, MAX_DATA_LEN, (LPBYTE)tmp, lBD, lbT);
						SetWindowTextA(MainWindow.hWndOutBox, "9801234567");
# else
						MessageBox(MainWindow.hWnd, S_DATA_CHECKSUM_BAD, S_WCODE_MESSAGE, MB_OK);
# endif
					}
				}
				else
					MessageBox(MainWindow.hWnd, S_TOKEN_ERROR, S_WCODE_MESSAGE, MB_OK);
				}
				 break;
			case IN_COPY_BUTTON_ID:
				{
				UINT lBD;
				if(in_uFormat == CF_UNICODETEXT) {
					GetWindowTextW(MainWindow.hWndInBox, (LPWSTR)string, MAX_WCODE_LEN);
					lBD = (UINT)wcslen((LPWSTR)string);
				}
				else {
					GetWindowTextA(MainWindow.hWndInBox, (LPSTR)string, MAX_WCODE_LEN);
					lBD = (UINT)strlen((LPSTR)string);
				}
				CopyToClpBrd((LPVOID)string, lBD+1, in_uFormat);

				} break;
			case IN_PASTE_BUTTON_ID:
				{
				/*
				LPWSTR string = new WCHAR[MAX_TEXT_LEN];
				PasteFrmClpBrd((LPVOID)string, MAX_TEXT_LEN);
				SetWindowText(MainWindow.hWndInBox, string);
				*/
				SendMessage(MainWindow.hWndInBox, WM_PASTE, 0, 0);
				} break;
			case IN_CLEAR_BUTTON_ID:
				SetWindowText(MainWindow.hWndInBox, NULL);
				SetWindowText(MainWindow.hWndOutBox, NULL);
				Suggest.Reset();
				break;
			case CYCLE_BUTTON_ID:
				GetWindowText(MainWindow.hWndOutBox, (LPWSTR)string, MAX_WCODE_LEN);
				SetWindowText(MainWindow.hWndOutBox, NULL);
				SetWindowText(MainWindow.hWndInBox, (LPWSTR)string);
				SendMessage(MainWindow.hWnd, WM_COMMAND, (WPARAM)(MAKELONG(MODE_BUTTON_ID, 0)), (LPARAM)MainWindow.hWndModeButton);
				SendMessage(MainWindow.hWnd, WM_COMMAND, (WPARAM)(MAKELONG(CONVERT_BUTTON_ID, 0)), (LPARAM)MainWindow.hWndCnvButton);
				break;
			case OUT_COPY_BUTTON_ID:
				UINT lBD;
				if(out_uFormat == CF_UNICODETEXT) {
					GetWindowText(MainWindow.hWndOutBox, (LPWSTR)string, MAX_WCODE_LEN);
					lBD = (UINT)wcslen((LPWSTR)string);
				}
				else {
					GetWindowTextA(MainWindow.hWndOutBox, (LPSTR)string, MAX_WCODE_LEN);
					lBD = (UINT)strlen((LPSTR)string);
				}
				CopyToClpBrd((LPVOID)string, lBD+1, out_uFormat);
				break;
			case OUT_PASTE_BUTTON_ID:
				SendMessage(MainWindow.hWndOutBox, WM_PASTE, 0, 0);
				break;
			case OUT_CLEAR_BUTTON_ID:
				SetWindowText(MainWindow.hWndOutBox, NULL);
				break;
			case MODE_BUTTON_ID:
				{
					if(bMode == ENCODE) {
						bMode = DECODE;
						ShowWindow(MainWindow.hWndOutBox, SW_HIDE);
						ShowWindow(MainWindow.hWndSugBox, SW_SHOW);
						SendMessage(MainWindow.hWndModeButton, WM_SETTEXT, NULL, (LPARAM)S_DECODE);
						SetWindowLongPtr(MainWindow.hWndInBox, GWLP_WNDPROC, (LONG_PTR)MainWindow.ProcInBox);
					}
					else {
						ShowWindow(MainWindow.hWndSugBox, SW_HIDE);
						ShowWindow(MainWindow.hWndOutBox, SW_SHOW);
						bMode = ENCODE;
						SendMessage(MainWindow.hWndModeButton, WM_SETTEXT, NULL, (LPARAM)S_ENCODE);
						SetWindowLongPtr(MainWindow.hWndInBox, GWLP_WNDPROC, (LONG_PTR)MainWindow.wpXProcInBox);
					}
					SendMessage(MainWindow.hWnd, WM_COMMAND, (WPARAM)MAKELONG(TYPE_LIST_WINDOW_ID, CBN_SELCHANGE), 0);
				} break;
			case GROUP_LIST_WINDOW_ID:
				switch(HIWORD(wParam))
				{
				case CBN_DROPDOWN:
					//UINT i = 0;
					break;
				case CBN_SELCHANGE:
					modeGroup = (UINT)SendMessage(MainWindow.hWndGroupList, CB_GETCURSEL, 0, 0);
					SendMessage(MainWindow.hWndTypeList, CB_RESETCONTENT, 0, 0);
					switch(modeGroup)
					{
					case GROUP_RAW:
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_BINARY);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_OCTAL);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_DECIMAL);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_HEX);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_BASE32);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_BASE64);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_FILE);
						break;
					case GROUP_TEXT:
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_ASCII);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_ANSI);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_UNICODE);
						break;
					case GROUP_NUMBER:
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_WHOLE);
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_FLOAT);
						break;
					case GROUP_OBJECT:
						SendMessage(MainWindow.hWndTypeList, CB_ADDSTRING, 0, (LPARAM)LABEL_TYPE_LATLONG);
						//break;
					}
					SendMessage(MainWindow.hWndTypeList, CB_SETCURSEL, (WPARAM)0, 0);
					SendMessage(MainWindow.hWnd, WM_COMMAND, (WPARAM)MAKELONG(TYPE_LIST_WINDOW_ID, CBN_SELCHANGE ), 0);
				} break;
			case TYPE_LIST_WINDOW_ID:
				switch(HIWORD(wParam))
				{
				case CBN_SELCHANGE:
					modeType = (UINT)SendMessage(MainWindow.hWndTypeList, CB_GETCURSEL, 0, 0);
					SetModeVars(modeGroup);
				} break;
			case START_FOCUS_ID:
				SetFocus(MainWindow.hWndModeButton);
				return 0;
			case TOGGLE_SUG_ID:
				MainWindow.ToggleSug();
				return 0;
			case OVER_SPACE:
				MainWindow.OverSpace();
				return 0;
			case IN_FOCUS:
				SetFocus(MainWindow.hWndInBox);
				return 0;
			}
		}
		break;
	case WM_SETFOCUS:
		if(CountClipboardFormats()) {
			EnableWindow(MainWindow.hWndInPstButton, TRUE);
			if(bMode == DECODE)
				if(modeGroup == GROUP_RAW)
					if(modeType == TYPE_FILE)
						EnableWindow(MainWindow.hWndOutCpyButton, FALSE);
		}
		else {
			EnableWindow(MainWindow.hWndInPstButton, FALSE);
			if(bMode == DECODE)
				if(modeGroup == GROUP_RAW)
					if(modeType == TYPE_FILE)
						EnableWindow(MainWindow.hWndOutCpyButton, FALSE);
		}
		SetFocus(MainWindow.hWndInBox);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

BOOL X1(UINT& lTmp, UINT type) {
	GetWindowTextA(MainWindow.hWndInBox, (LPSTR)tmp, MAX_WCODE_LEN);
	lTmp = (UINT)strlen((LPSTR)tmp);
	UINT rVal = RationalizeA(type, (LPSTR)tmp, lTmp);
	if(rVal != -1) {
		MessageBox(MainWindow.hWnd, szError[type], S_WCODE_MESSAGE, MB_OK);
		SetFocus(MainWindow.hWndInBox);
		SendMessage(MainWindow.hWndInBox, EM_SETSEL, (WPARAM)rVal, (LPARAM)rVal+1);
		return FALSE;
	}
	else
		return TRUE;
}
