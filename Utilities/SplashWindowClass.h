# ifndef SPLASH_WINDOW_CLASS_HEADER
# define SPLASH_WINDOW_CLASS_HEADER

# include "Lang\\CommonID.h"

# include "LocaleClass.h"
# include "NotifyMessageBoxClass.h"

class SplashWindowClass
{
private:
	WNDCLASSEX wc;
	LPWSTR szWindowClass;
	LPWSTR szWindowTitle;
	HWND hWnd;

public:
	HBITMAP hBM_Splash;
	SplashWindowClass();
	VOID Create(HINSTANCE hInstance, UINT uID, HWND hWnd);
	//HWND HWnd();
	VOID Show();
	VOID BeginFade();
	static LRESULT CALLBACK SplashProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

LRESULT CALLBACK SplashProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

# endif // SPLASH_WINDOW_CLASS_HEADER
