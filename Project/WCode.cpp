# include "WCode.h"

# include "Lang\\CommonID.h"
# include "Resource.h"

# include "..\\Utilities\\LocaleClass.h"
# include "..\\Utilities\\NotifyMessageBoxClass.h"
# include "..\\Utilities\\SettingsClass.h"
# include "..\\Utilities\\SplashWindowClass.h"

# include "WordCodeClass.h"
# include "MainWindowClass.h"

# define MAX_WCODE_LEN			2000
# define MAX_CODE_LEN			2000
# define MAX_DATA_LEN			2000
# define MAX_PATH_LEN			1000

# define DICTIONARY_DIR		L"Dictionary"
# define DICTIONARY_FILE	L"WordList_EN.txt"

# define S_MESSAGE_TITLE				L"Settings Error"
# define INVALID_REG_SETTINGS			0x0000103
# define S_ERROR_INVALID_REG_SETTINGS	L"Invalid Registry Sttings"

DWORD arDWDef[] = {1, 0, 0, 0, 2};

LocaleClass				Locale;
NotifyMessageBoxClass	NotifyMessageBox;
MainWindowClass			MainWindow;
SplashWindowClass		SplashWindow;
SettingsClass			Settings(HKEY_CURRENT_USER,
								 SOFTWARE_REG_KEY SETTINGS_KEY,
								 SETTINGS_ID_BASE,
								 SETTINGS_N_VAR,
								 SETTINGS_N_FLOAT,
								 SETTINGS_N_STRING);
DictionaryClass			Dictionary(DICTIONARY_DIR L"\\" DICTIONARY_FILE);
WordCodeClass			WordCode;
SuggestClass			Suggest(Dictionary);

HINSTANCE hInstance;

LPVOID tmp;
LPVOID data;
UINT dataSize;
LPWSTR path;
LPVOID string;
LPWSTR message;

BOOL bMode;
BOOL bChecksum;
UINT modeGroup;
UINT modeType;
UINT xModeType;

UINT* code;
UINT nCode;

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	::hInstance = hInstance;

	if(!Settings.Load()) {
		Settings.Set(arDWDef, NULL, NULL);
		if(!Settings.Load()) {
			MessageBox(NULL, S_ERROR_INVALID_REG_SETTINGS, S_MESSAGE_TITLE, MB_OK);
			exit(INVALID_REG_SETTINGS);
		}
	}

	::bMode = Settings.GetValue(ENCODE_O_DECODE);
	::bChecksum = Settings.GetValue(CHECKSUM);
	::modeGroup = Settings.GetValue(MODE_GROUP);
	::xModeType = modeType = Settings.GetValue(MODE_TYPE);

	::code = new UINT[MAX_CODE_LEN];
	::data = new BYTE[MAX_DATA_LEN];
	::dataSize = MAX_DATA_LEN;
	::string = new WCHAR[MAX_WCODE_LEN];
	::tmp = new BYTE[MAX_DATA_LEN];
	::message = new WCHAR[MAX_WCODE_LEN];
	::path = new WCHAR[MAX_PATH_LEN];

	::path[0] = NULL;

	MainWindow.Create();
	MainWindow.Init();
	SplashWindow.Create(hInstance, IDI_WCODE_ICON, MainWindow.hWnd);

	NotifyMessageBox.Set_hWnd(MainWindow.hWnd);

	if(Settings.GetValue(SPLASH)) {
		SplashWindow.BeginFade();
		SplashWindow.Show();
	}

	ShowWindow(MainWindow.hWnd, SW_SHOWNORMAL);

	HACCEL hAccel = LoadAccelerators(hInstance, L"WCODE");

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		if(!TranslateAccelerator(MainWindow.hWnd, hAccel, &msg))
			if(!IsDialogMessage(MainWindow.hWnd, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
	};

	return 0;
}
