# include "SplashWindowClass.h"

# define MAX_WINDOW_CLASS_LEN	1000
# define MAX_WINDOW_TITLE_LEN	1000

# define IDB_SPLASH			110
# define ID_TIMER_SPLASH	111
# define SPLASH_T_FADE_I	1000
# define SPLASH_T_FADE		100
# define SPLASH_BITMAP		L"Splash.bmp"
# define ALPHA_MAX_VALUE	255
# define ALPHA_STEP_VALUE	10

extern NotifyMessageBoxClass	NotifyMessageBox;
extern LocaleClass				Locale;

SplashWindowClass::SplashWindowClass()
{
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = SplashProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	szWindowClass = new WCHAR[MAX_WINDOW_CLASS_LEN];
	szWindowTitle = new WCHAR[MAX_WINDOW_TITLE_LEN];
	hBM_Splash = (HBITMAP)LoadImage(NULL, SPLASH_BITMAP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(hBM_Splash == NULL)
		NotifyMessageBox.NotifyMessage(IDS_BM_LOAD_FAIL, IDS_ERROR, MB_ICONERROR | MB_OK);
};

VOID SplashWindowClass::Create(HINSTANCE hInstance, UINT uID, HWND parent_hWnd)
{
	Locale.GetString(IDS_SPLASH_WINDOW_CLASS, szWindowClass, MAX_WINDOW_CLASS_LEN);
	Locale.GetString(IDS_SPLASH_WINDOW_TITLE, szWindowTitle, MAX_WINDOW_TITLE_LEN);
	wc.lpszClassName = szWindowClass;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(uID));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(uID));
	if(!RegisterClassEx(&wc))
	{
		int x = GetLastError();
		NotifyMessageBox.NotifyMessage(IDS_W_REG_FAIL, IDS_ERROR, MB_ICONERROR | MB_OK);
		exit(-1);
	}

	BITMAP bitmap;
	HDC dc = GetDC(NULL);
	HDC hDcMem = CreateCompatibleDC(dc);
	SelectObject(hDcMem, hBM_Splash);
	GetObject(hBM_Splash, sizeof(bitmap), &bitmap);
	SIZE size = { bitmap.bmWidth, bitmap.bmHeight };
	POINT ppsrc = { 0, 0 };
	BLENDFUNCTION pblend = { AC_SRC_OVER, 0, ALPHA_MAX_VALUE, AC_SRC_ALPHA };

	hWnd = CreateWindowEx(
		WS_EX_LAYERED,
		szWindowClass,
		szWindowTitle,
		WS_POPUP,
		(GetSystemMetrics(SM_CXSCREEN) - bitmap.bmWidth)/2,
		(GetSystemMetrics(SM_CYSCREEN) - bitmap.bmHeight)/2,
		bitmap.bmWidth, bitmap.bmHeight,
		parent_hWnd, NULL, hInstance, NULL);

	if(hWnd == NULL)
	{
		NotifyMessageBox.NotifyMessage(IDS_W_CREATE_FAIL, IDS_ERROR, MB_ICONERROR | MB_OK);
		exit(-2);
	}

	if ( 0 == UpdateLayeredWindow(hWnd, NULL, NULL, &size, hDcMem, &ppsrc, 0, &pblend, ULW_ALPHA) )
		NotifyMessageBox.NotifyMessage(IDS_W_UL_FAIL, IDS_ERROR, MB_ICONERROR | MB_OK);
};

//VOID SplashWindowClass::hWnd()
//{
//	return hWnd;
//}

VOID SplashWindowClass::Show()
{
	ShowWindow(hWnd, SW_SHOW);
}

VOID SplashWindowClass::BeginFade()
{
	BLENDFUNCTION pblend = {AC_SRC_OVER, 0, ALPHA_MAX_VALUE, AC_SRC_ALPHA};
	if (0 == UpdateLayeredWindow(hWnd, NULL, NULL, NULL, NULL, NULL, 0, &pblend, ULW_ALPHA))
		NotifyMessageBox.NotifyMessage(IDS_W_UL_FAIL, IDS_ERROR, MB_ICONERROR | MB_OK);
	SetTimer(hWnd, ID_TIMER_SPLASH, SPLASH_T_FADE_I, NULL);
}

LRESULT CALLBACK SplashWindowClass::SplashProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BYTE alpha = ALPHA_MAX_VALUE;
	static BLENDFUNCTION pblend = {AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};

	switch(msg)
	{
	case WM_TIMER:
		switch(wParam)
		{
		case ID_TIMER_SPLASH:

			pblend.SourceConstantAlpha = alpha;

			if(alpha < ALPHA_STEP_VALUE)
			{
				KillTimer(hWnd, ID_TIMER_SPLASH);
				alpha = ALPHA_MAX_VALUE;
				ShowWindow(hWnd, SW_HIDE);
			}
			else if(alpha == ALPHA_MAX_VALUE)
			{
				alpha--;
				KillTimer(hWnd, ID_TIMER_SPLASH);
				SetTimer(hWnd, ID_TIMER_SPLASH, SPLASH_T_FADE, NULL);
			}
			else
				alpha -= ALPHA_STEP_VALUE;

			if (0 == UpdateLayeredWindow(hWnd, NULL, NULL, NULL, NULL, NULL, 0, &pblend, ULW_ALPHA))
				NotifyMessageBox.NotifyMessage(IDS_W_UL_FAIL, IDS_ERROR, MB_ICONERROR | MB_OK);
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
