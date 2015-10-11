# include "LocaleClass.h"
# include "NotifyMessageBoxClass.h"

# define MAX_MESSAGE_LEN				200
# define MAX_TITLE_LEN					100

# define S_MESSAGE_TITLE				L"Settings Error"
# define INVALID_REG_SETTINGS			0x0000103
# define S_ERROR_INVALID_REG_SETTINGS	L"Invalid Registry Sttings"
# define MAX_VALUE_NAME_LEN				100
# define MAX_REG_STRING_LEN				50

extern LocaleClass Locale;

NotifyMessageBoxClass::NotifyMessageBoxClass()
{
	title = new WCHAR[MAX_TITLE_LEN];
	message = new WCHAR[MAX_MESSAGE_LEN];
	hWnd = hWnd;
}

VOID NotifyMessageBoxClass::Set_hWnd(HWND hWnd)
{
	NotifyMessageBoxClass::hWnd = hWnd;
}

int NotifyMessageBoxClass::NotifyMessage(UINT messageID, UINT titleID, UINT messageType)
{
	Locale.GetString(messageID, message, MAX_MESSAGE_LEN);
	if(titleID)
		Locale.GetString(titleID, title, MAX_TITLE_LEN);
	else
		GetWindowText(hWnd, title, MAX_TITLE_LEN);
	return MessageBox(NULL, message, title, messageType);
}
