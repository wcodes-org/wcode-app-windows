# ifndef MAIN_PROC_HEADER
# define MAIN_PROC_HEADER

# define MAX_WCODE_LEN			2000
# define MAX_CODE_LEN			2000
//# define MAX_DATA_LEN			2000
# define MAX_PATH_LEN			1000

# include <Windows.h>

LRESULT CALLBACK MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

# endif // MAIN_PROC_HEADER
