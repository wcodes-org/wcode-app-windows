# ifndef NOTIFY_MESSAGE_BOX_HEADER
# define NOTIFY_MESSAGE_BOX_HEADER

# include <Windows.h>

class NotifyMessageBoxClass
{
	HWND hWnd;
	LPWSTR title;
	LPWSTR message;
public:
	NotifyMessageBoxClass();
	VOID Set_hWnd(HWND hWnd);
	int NotifyMessage(UINT messageID, UINT titleID, UINT messageType);
};

# endif // NOTIFY_MESSAGE_BOX_HEADER
