# ifndef LOCALE_CLASS_HEADER
# define LOCALE_CLASS_HEADER

# include <Windows.h>

class LocaleClass
{
private:
	HINSTANCE hResDLL;
	LPWSTR dllFileName;
public:
	LocaleClass();
	VOID LoadLang(LCID LangID);
	int GetString(UINT id, LPWSTR string, UINT bLen);
};

# endif // LOCALE_CLASS_HEADER
