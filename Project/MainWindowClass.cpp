# include "MainWindowClass.h"
# include "Utilities\SuggestClass.h"

# include "Resource.h"
# include "MainWindowLayout.h"

# define MAX_WINDOW_CLASS_LEN	500
# define MAX_WINDOW_TITLE_LEN	500

# define WINDOW_CLASS_NAME		L"Main"
# define WINDOW_NAME			L"WCode"

# define WINDOW_TITLE			L"WCode Error"

# define S_ENCODE				L"Encode"
//# define S_DECODE				L"Decode"

# define S_OPTIONS				L"Options"
# define S_SAVE_MODE			L"*"
# define S_ABOUT				L"i"

# define S_COPY					L"Copy"
# define S_PASTE				L"Paste"

# ifdef TEST
# define S_CYCLE				L"Test"
# endif

# define S_CLEAR				L"Clear"
# define S_CONVERT				L"Convert"

# define ERROR_REG_WINDOW		L"Error Registering Window"
# define EROOR_CREATE_WINDOW	L"Error Creating Window"

# define ENCODE					0
# define DECODE					1

# define MAX_DICT_TOKEN_LEN		20
# define MAX_SUGGESTION_LIST_LEN	200

# define ERROR_ADJUST_WINDOW	-24532

# define CHECK_KEY				0x8000

extern SuggestClass Suggest;

extern BOOL bMode;
extern UINT modeGroup;
extern UINT modeType;
extern UINT xModeType;

extern BOOL bChecksum;

extern HINSTANCE hInstance;
extern LRESULT CALLBACK MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC MainWindowClass::wpXProcInBox;
BOOL MainWindowClass::bSugMode = TRUE;
BOOL MainWindowClass::bAddSpace;

HWND MainWindowClass::hWnd;
HWND MainWindowClass::hWndInBox;
HWND MainWindowClass::hWndOutBox;
HWND MainWindowClass::hWndSugBox;
HWND MainWindowClass::hWndModeButton;

MainWindowClass::MainWindowClass() {
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = MainProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW);
	wc.lpszMenuName = NULL;	// = MAIN_WINDOW_CLASS;

	szWindowClass = new WCHAR[MAX_WINDOW_CLASS_LEN];
	szWindowTitle = new WCHAR[MAX_WINDOW_TITLE_LEN];

	hWndBwsButton = NULL;
	bAddSpace = FALSE;
};

VOID MainWindowClass::Create() {
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hInstance = ::hInstance;
	wc.hIcon = LoadIcon(::hInstance, MAKEINTRESOURCE(IDI_WCODE_ICON));
	wc.hIconSm = LoadIcon(::hInstance, MAKEINTRESOURCE(IDI_WCODE_ICON));
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, ERROR_REG_WINDOW, WINDOW_TITLE, MB_ICONERROR | MB_OK);
		exit(-1);
	}

# define WINDOW_STYLE	WS_OVERLAPPEDWINDOW

	RECT rWindow;
	rWindow.left = 0;
	rWindow.top = 0;
	rWindow.right = WINDOW_WIDTH;
	rWindow.bottom = WINDOW_HEIGHT;
	if(!AdjustWindowRectEx(&rWindow, WINDOW_STYLE, FALSE, 0))
		exit(ERROR_ADJUST_WINDOW);
	hWnd = CreateWindowEx(
		0,
		WINDOW_CLASS_NAME,
		WINDOW_NAME,
		WINDOW_STYLE,
		(GetSystemMetrics(SM_CXSCREEN) - (rWindow.right-rWindow.left))/2,
		(GetSystemMetrics(SM_CYSCREEN) - (rWindow.bottom-rWindow.top))/2,
		rWindow.right-rWindow.left, rWindow.bottom-rWindow.top,
		NULL, NULL, ::hInstance, NULL);

	if(hWnd == NULL) {
		MessageBox(NULL, EROOR_CREATE_WINDOW, WINDOW_TITLE, MB_ICONERROR | MB_OK);
		exit(-2);
	}

	hWndModeButton = CreateWindowEx(
		0,
		L"BUTTON", S_ENCODE, WS_VISIBLE | WS_CHILD | BS_FLAT | WS_GROUP | WS_TABSTOP,
		MODE_BUTTON_H_MRGN, MODE_BUTTON_V_MRGN, MODE_BUTTON_WIDTH, MODE_BUTTON_HEIGHT, hWnd, (HMENU)MODE_BUTTON_ID, NULL, NULL);

	hWndGroupList = CreateWindowEx(
		0,
		L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,
		GROUP_LIST_H_MRGN, GROUP_LIST_V_MRGN, GROUP_LIST_WIDTH, GROUP_LIST_T_HEIGHT, hWnd, (HMENU)GROUP_LIST_WINDOW_ID, NULL, NULL);

	hWndTypeList = CreateWindowEx(
		0,
		L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,
		TYPE_LIST_H_MRGN, TYPE_LIST_V_MRGN, TYPE_LIST_WIDTH, TYPE_LIST_T_HEIGHT, hWnd, (HMENU)TYPE_LIST_WINDOW_ID, NULL, NULL);

	hWndOptionsButton = CreateWindowEx(
		0,
		L"BUTTON", S_OPTIONS, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		OPTIONS_BUTTON_H_MRGN, OPTIONS_BUTTON_V_MRGN, OPTIONS_BUTTON_WIDTH, OPTIONS_BUTTON_HEIGHT, hWnd, (HMENU)OPTIONS_BUTTON_ID, NULL, NULL);

	hWndCsmButton = CreateWindowEx(
		0,
		L"BUTTON", S_CHECKSUM_T, WS_VISIBLE | WS_CHILD | BS_FLAT | WS_TABSTOP,
		CHECKSUM_BUTTON_H_MRGN, CHECKSUM_BUTTON_V_MRGN, CHECKSUM_BUTTON_WIDTH, CHECKSUM_BUTTON_HEIGHT, hWnd, (HMENU)CSM_CHECK_WINDOW_ID, NULL, NULL);

	hWndSaveModeButton = CreateWindowEx(
		0,
		L"BUTTON", S_SAVE_MODE, WS_VISIBLE | WS_CHILD | BS_FLAT | WS_TABSTOP,
		SAVE_MODE_BUTTON_H_MRGN, SAVE_MODE_BUTTON_V_MRGN, SAVE_MODE_BUTTON_WIDTH, SAVE_MODE_BUTTON_HEIGHT, hWnd, (HMENU)SAVE_MODE_BUTTON_ID, NULL, NULL);

	hWndAboutButton = CreateWindowEx(
		0,
		L"BUTTON", S_ABOUT, WS_VISIBLE | WS_CHILD | BS_FLAT | WS_TABSTOP,
		ABOUT_BUTTON_H_MRGN, ABOUT_BUTTON_V_MRGN, ABOUT_BUTTON_WIDTH, ABOUT_BUTTON_HEIGHT, hWnd, (HMENU)ABOUT_BUTTON_ID, NULL, NULL);

# ifdef TEST
	hWndCycle = CreateWindowEx(
		0,
		L"BUTTON", S_CYCLE, WS_VISIBLE | WS_CHILD,
		CYCLE_BUTTON_H_MRGN, CYCLE_BUTTON_V_MRGN, CYCLE_BUTTON_WIDTH, CYCLE_BUTTON_HEIGHT, hWnd, (HMENU)CYCLE_BUTTON_ID, NULL, NULL);
# endif

	hWndInBox = CreateWindowEx(
		WS_EX_STATICEDGE,
		L"EDIT", NULL, WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_CENTER | ES_AUTOVSCROLL | WS_TABSTOP,
		IN_BOX_H_MRGN, IN_BOX_V_MRGN, IN_BOX_WIDTH, IN_BOX_HEIGHT, hWnd, (HMENU)TEXT_IN_WINDOW_ID, NULL, NULL);
	wpXProcInBox = (WNDPROC) SetWindowLongPtr(hWndInBox, GWLP_WNDPROC, (LONG_PTR)(ProcInBox));

	hWndInCpyButton = CreateWindowEx(
		0,
		L"BUTTON", S_COPY, WS_VISIBLE | WS_CHILD | WS_GROUP | WS_TABSTOP,
		IN_COPY_BUTTON_H_MRGN, IN_COPY_BUTTON_V_MRGN, IN_COPY_BUTTON_WIDTH, IN_COPY_BUTTON_HEIGHT, hWnd, (HMENU)IN_COPY_BUTTON_ID, NULL, NULL);

	hWndInPstButton = CreateWindowEx(
		0,
		L"BUTTON", S_PASTE, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		IN_PASTE_BUTTON_H_MRGN, IN_PASTE_BUTTON_V_MRGN, IN_PASTE_BUTTON_WIDTH, IN_PASTE_BUTTON_HEIGHT, hWnd, (HMENU)IN_PASTE_BUTTON_ID, NULL, NULL);

	hWndInClrButton = CreateWindowEx(
		0,
		L"BUTTON", S_CLEAR, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		IN_CLEAR_BUTTON_H_MRGN, IN_CLEAR_BUTTON_V_MRGN, IN_CLEAR_BUTTON_WIDTH, IN_CLEAR_BUTTON_HEIGHT, hWnd, (HMENU)IN_CLEAR_BUTTON_ID, NULL, NULL);

	hWndCnvButton = CreateWindowEx(
		0,
		L"BUTTON", S_CONVERT, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CONVERT_BUTTON_H_MRGN, CONVERT_BUTTON_V_MRGN, CONVERT_BUTTON_WIDTH, CONVERT_BUTTON_HEIGHT, hWnd, (HMENU)CONVERT_BUTTON_ID, NULL, NULL);

	hWndOutBox = CreateWindowEx(
		WS_EX_STATICEDGE,
		L"EDIT", NULL, WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_CENTER | ES_AUTOVSCROLL | ES_READONLY/*WS_VISIBLE | WS_CHILD | SS_EDITCONTROL | SS_CENTER | ES_AUTOVSCROLL*/,
		OUT_BOX_H_MRGN, OUT_BOX_V_MRGN, OUT_BOX_WIDTH, OUT_BOX_HEIGHT, hWnd, (HMENU)TEXT_OUT_WINDOW_ID, NULL, NULL);

	hWndOutCpyButton = CreateWindowEx(
		0,
		L"BUTTON", S_COPY, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		OUT_COPY_BUTTON_H_MRGN, OUT_COPY_BUTTON_V_MRGN, OUT_COPY_BUTTON_WIDTH, OUT_COPY_BUTTON_HEIGHT, hWnd, (HMENU)OUT_COPY_BUTTON_ID, NULL, NULL);

	hWndOutPstButton = CreateWindowEx(
		0,
		L"BUTTON", S_PASTE, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		OUT_PASTE_BUTTON_H_MRGN, OUT_PASTE_BUTTON_V_MRGN, OUT_PASTE_BUTTON_WIDTH, OUT_PASTE_BUTTON_HEIGHT, hWnd, (HMENU)OUT_PASTE_BUTTON_ID, NULL, NULL);

	hWndOutClrButton = CreateWindowEx(
		0,
		L"BUTTON", S_CLEAR, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		OUT_CLEAR_BUTTON_H_MRGN, OUT_CLEAR_BUTTON_V_MRGN, OUT_CLEAR_BUTTON_WIDTH, OUT_CLEAR_BUTTON_HEIGHT, hWnd, (HMENU)OUT_CLEAR_BUTTON_ID, NULL, NULL);

	hWndSugBox = CreateWindowEx(
		0,
		L"STATIC", NULL, WS_CHILD | ES_CENTER,// | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		SUG_BOX_H_MRGN, SUG_BOX_V_MRGN, SUG_BOX_WIDTH, SUG_BOX_HEIGHT, hWnd, (HMENU)TEXT_SUG_WINDOW_ID, NULL, NULL);
};

VOID MainWindowClass::Init()
{
	if(bMode != ENCODE) {
		bMode = ENCODE;
		SendMessage(hWnd, WM_COMMAND, (WPARAM)(MAKELONG(MODE_BUTTON_ID, CBN_SELCHANGE)), (LPARAM)hWndModeButton);
	}
	else {
		SendMessage(hWnd, WM_COMMAND, (WPARAM)(MAKELONG(MODE_BUTTON_ID, CBN_SELCHANGE)), (LPARAM)hWndModeButton);
		SendMessage(hWnd, WM_COMMAND, (WPARAM)(MAKELONG(MODE_BUTTON_ID, CBN_SELCHANGE)), (LPARAM)hWndModeButton);
	}
	SendMessage(hWndGroupList, CB_ADDSTRING, 0, (LPARAM)LABEL_GROUP_RAW);
	SendMessage(hWndGroupList, CB_ADDSTRING, 0, (LPARAM)LABEL_GROUP_TEXT);
	SendMessage(hWndGroupList, CB_ADDSTRING, 0, (LPARAM)LABEL_GROUP_NUMBER);
	SendMessage(hWndGroupList, CB_ADDSTRING, 0, (LPARAM)LABEL_GROUP_OBJECT);

	SendMessage(hWndGroupList, CB_SETCURSEL, (WPARAM)modeGroup, 0);
	SendMessage(hWnd, WM_COMMAND, (WPARAM)(MAKELONG(GROUP_LIST_WINDOW_ID, CBN_SELCHANGE)), (LPARAM)hWndGroupList);
	SendMessage(hWndTypeList, CB_SETCURSEL, (WPARAM)xModeType, 0);
	SendMessage(hWnd, WM_COMMAND, (WPARAM)(MAKELONG(TYPE_LIST_WINDOW_ID, CBN_SELCHANGE)), (LPARAM)hWndTypeList);

	if(!bChecksum)
		SendMessage(hWndCsmButton, WM_SETTEXT, NULL, (LPARAM)S_CHECKSUM_F);

	EnableWindow(hWndInClrButton, FALSE);
	EnableWindow(hWndInCpyButton, FALSE);
	EnableWindow(hWndCnvButton, FALSE);
	EnableWindow(hWndOutClrButton, FALSE);
	EnableWindow(hWndOutPstButton, FALSE);
	EnableWindow(hWndOutCpyButton, FALSE);

	SetFocus(hWndInBox);
}

VOID MainWindowClass::Destroy() {
	SetWindowLongPtr(hWndInBox, GWLP_WNDPROC, (LONG)wpXProcInBox);
}

VOID MainWindowClass::AddBrowseButton() {
	hWndBwsButton = CreateWindowEx(
		0,
		L"BUTTON", L"Browse", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		BROWSE_BUTTON_H_MRGN, BROWSE_BUTTON_V_MRGN, BROWSE_BUTTON_WIDTH, BROWSE_BUTTON_HEIGHT, hWnd, (HMENU)BROWSE_BUTTON_ID, NULL, NULL);
}

LRESULT APIENTRY MainWindowClass::ProcInBox(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPWSTR szRemn = new WCHAR[MAX_DICT_TOKEN_LEN];

	switch(uMsg)
	{
	case WM_KEYDOWN:
		switch(wParam) {
		case VK_LEFT:
		case VK_RIGHT:
			bSugMode = FALSE;
			Suggest.Reset();
			SetWindowText(hWndSugBox, L"");
			CallWindowProc(wpXProcInBox, hWnd, uMsg, wParam, lParam);
		}
		return 0;
	case WM_CHAR:
		if(bSugMode)
		{
			if(wParam >= '0' && wParam <='9')
			{
				UINT iOption;
				if(wParam == '0')
					iOption = 9;
				else
					iOption = (UINT)(wParam - '0' - 1);

				UINT lRemn = Suggest.GetTerm(iOption, szRemn);
				if(lRemn)
				{
					for(UINT i = 0; i < lRemn; i++)
						CallWindowProc(wpXProcInBox, hWnd, uMsg, (WPARAM)szRemn[i], lParam);
					Suggest.Reset();
					SetWindowText(hWndSugBox, NULL);
					bAddSpace = TRUE;
				}
				return 0;
			}
			else
			{
				switch(wParam)
				{
				case VK_RETURN:
					SendMessage(MainWindowClass::hWnd, WM_COMMAND, (WPARAM)(MAKELONG(CONVERT_BUTTON_ID, 0)), (LPARAM)GetDlgItem(MainWindowClass::hWnd, CONVERT_BUTTON_ID));
					return 0;
				case VK_SPACE:
					if(bAddSpace) {
						bAddSpace = FALSE;
						CallWindowProc(wpXProcInBox, hWnd, uMsg, (WPARAM)VK_SPACE, lParam);
					}
					else if(Suggest.IsValid()) {
						Suggest.Reset();
						CallWindowProc(wpXProcInBox, hWnd, uMsg, wParam, lParam);
						bAddSpace = FALSE;
					}
					else {
						MessageBox(hWnd, L"Invalid", L"WCode", MB_OK);
						SetFocus(hWndInBox);
					}
					return 0;
				case VK_TAB:
					CallWindowProc(ProcInBox, hWnd, uMsg, (WPARAM)'1', lParam);
					return 0;
				case VK_BACK:
				case VK_DELETE:
					bSugMode = FALSE;
					Suggest.Reset();
					SetWindowText(hWndSugBox, L"");
					CallWindowProc(wpXProcInBox, hWnd, uMsg, wParam, lParam);
					return 0;
				default:
					if(bAddSpace) {
						bAddSpace = FALSE;
						CallWindowProc(wpXProcInBox, hWnd, uMsg, (WPARAM)VK_SPACE, lParam);
					}
					static LPWSTR szSugList = new WCHAR[MAX_SUGGESTION_LIST_LEN];
					if(iswalpha((WCHAR)wParam)) {
						WCHAR inChar = towlower((WCHAR)wParam);
						if(Suggest.Suggest((WCHAR)inChar, szSugList)) {
							CallWindowProc(wpXProcInBox, hWnd, uMsg, inChar, lParam);
							SetWindowText(hWndSugBox, szSugList);
						}
						else {
							MessageBox(NULL, L"Invalid word", L"WCode", MB_OK);
							SetFocus(hWndInBox);
						}
					}
					else {
						MessageBox(NULL, L"Invalid character", L"WCode", MB_OK);
						SetFocus(hWndInBox);
					}
					return 0;
				}
			}
		}
		else
			return CallWindowProc(wpXProcInBox, hWnd, uMsg, wParam, lParam);
		//break
	case WM_SETFOCUS:
		{
		if(bMode == ENCODE) {
			ShowWindow(hWndSugBox, SW_HIDE);
			ShowWindow(hWndOutBox, SW_SHOW);
		}
		else {
			ShowWindow(hWndOutBox, SW_HIDE);
			ShowWindow(hWndSugBox, SW_SHOW);
		}
		}
	default:
		return CallWindowProc(wpXProcInBox, hWnd, uMsg, wParam, lParam);
	}
}

VOID MainWindowClass::ToggleSug() {
	bSugMode = !bSugMode;
	Suggest.Reset();
	SetWindowText(hWndSugBox, L"");
}

VOID MainWindowClass::OverSpace() {
	Suggest.Reset();
	SetWindowText(hWndSugBox, L"");
	CallWindowProc(wpXProcInBox, hWndInBox, WM_CHAR, (WPARAM)VK_SPACE, (LPARAM)0x390001);
}
