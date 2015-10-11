# ifndef SETTINGS_CLASS_HEADER
# define SETTINGS_CLASS_HEADER

# include "LocaleClass.h"

class SettingsClass
{
private:
	HKEY hKey;
	LPWSTR szSubKey;

	UINT iBase;
	UINT nVar;
	UINT nFloat;
	UINT nString;

	LPWSTR valueName;
	UINT *values;
	FLOAT *floats;
	LPWSTR *strings;

public:
	SettingsClass(HKEY hKey, LPWSTR szSubKey, UINT iBase, UINT nVar, UINT nFloat, UINT nString);
	BOOL Set(LPDWORD arDWDef, FLOAT* arFlDef, LPWSTR* arWStrDef);
	BOOL Load();
	BOOL Save();
	BOOL BackUp();
	UINT GetValue(UINT id);
	VOID SetValue(UINT id, DWORD value);
	FLOAT GetFValue(UINT id);
	VOID SetFValue(UINT id, FLOAT value);
	LPWSTR GetString(UINT id);
	VOID SetString(UINT id, LPWSTR string);
};

# endif // SETTINGS_CLASS_HEADER
