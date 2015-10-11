# include "LocaleClass.h"

# define MAX_FILENAME_LEN			100
# define MAX_LANGID_LEN				10
# define DEFAULT_LANG_ID			0x0409
# define RESOURCE_PATH				L"Lang\\"
# define RESOURCE_FILENAME			L"Res"
# define RESOURCE_FILENAME_EXTN		L".DLL.mui"

LocaleClass::LocaleClass() {
	dllFileName = new WCHAR[MAX_FILENAME_LEN];
	LCID LangID = GetThreadLocale();
	LoadLang(LangID);
	if (!hResDLL) {
		LoadLang(DEFAULT_LANG_ID);
		if (!hResDLL)
			exit(-2);
	}
}

VOID LocaleClass::LoadLang(LCID LangID) {
	LPWSTR lpszLangID = new WCHAR[MAX_LANGID_LEN];
	_itow_s(LangID, lpszLangID, MAX_LANGID_LEN, 16);
	wcscpy_s(dllFileName, MAX_FILENAME_LEN, RESOURCE_PATH RESOURCE_FILENAME);
	wcscat_s(dllFileName, MAX_FILENAME_LEN, lpszLangID);
	wcscat_s(dllFileName, MAX_FILENAME_LEN, RESOURCE_FILENAME_EXTN);
	hResDLL = LoadLibraryEx(dllFileName, NULL, LOAD_LIBRARY_AS_DATAFILE);
	delete lpszLangID;
}

int LocaleClass::GetString(UINT id, LPWSTR string, UINT bLen) {
	return LoadString(hResDLL, id, string, bLen);
}
