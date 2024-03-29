# ifndef MAIN_WINDOW_CLASS_HEADER
# define MAIN_WINDOW_CLASS_HEADER

# include "BuildSets.h"
// TEST

# include <Windows.h>

# define S_CHECKSUM_T			L"Checksum"
# define S_CHECKSUM_F			L"No Chksm"

class MainWindowClass
{
private:
	WNDCLASSEX wc;
	LPWSTR szWindowClass;
	LPWSTR szWindowTitle;

	static BOOL bSugMode;
	static BOOL bAddSpace;

public:
	static WNDPROC wpXProcInBox;
	static LRESULT APIENTRY ProcInBox(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static HWND hWnd;
	static HWND hWndModeButton;
	HWND hWndGroupList;
	HWND hWndTypeList;
	HWND hWndCsmButton;
	HWND hWndOptionsButton;
	HWND hWndBwsButton;
	HWND hWndAboutButton;
	HWND hWndSaveModeButton;
//	HWND hWndLeadCheck;
# ifdef TEST
	HWND hWndCycle;
# endif
	static HWND hWndInBox;
	static HWND hWndOutBox;
	static HWND hWndSugBox;
	HWND hWndCnvButton;
	HWND hWndInCpyButton;
	HWND hWndInPstButton;
	HWND hWndInClrButton;
	HWND hWndOutCpyButton;
	HWND hWndOutPstButton;
	HWND hWndOutClrButton;

	MainWindowClass();
	VOID Create();
	VOID Init();
	VOID Destroy();
	VOID AddBrowseButton();
	static VOID SwapInProc();
	static VOID ToggleSug();
	static VOID OverSpace();
};

# endif // MAIN_WINDOW_CLASS_HEADER
