# include "SettingsClass.h"

# define MAX_VALUE_NAME_LEN				100
# define MAX_REG_STRING_LEN				50

extern LocaleClass Locale;

SettingsClass::SettingsClass(HKEY hKey, LPWSTR szSubKey, UINT iBase, UINT nVar, UINT nFloat, UINT nString):
	hKey(hKey), szSubKey(szSubKey), iBase(iBase), nVar(nVar), nFloat(nFloat), nString(nString)
{
	valueName = new WCHAR[MAX_VALUE_NAME_LEN];
	values = new UINT[nVar];
	floats = new FLOAT[nFloat];
	strings = new LPWSTR[nString];
	for(UINT i = 0; i < nString; i++)
		strings[i] = new WCHAR[MAX_REG_STRING_LEN];
}

BOOL SettingsClass::Set(LPDWORD arDWDef, FLOAT* arFlDef, LPWSTR* arWStrDef)
{
	HKEY hkSoftware;
	RegCreateKeyEx(hKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSoftware, NULL);
	for(UINT i = 0; i < nVar; i++)
	{
		Locale.GetString(iBase+i, valueName, MAX_VALUE_NAME_LEN);
		if(RegSetValueEx(hkSoftware, valueName, 0, REG_DWORD, (LPBYTE)&arDWDef[i], sizeof(DWORD)) != ERROR_SUCCESS)
		{
			RegCloseKey(hkSoftware);
			return FALSE;
		}
	}
	for(UINT i = 0; i < nFloat; i++)
	{
		Locale.GetString(iBase+nVar+i, valueName, MAX_VALUE_NAME_LEN);
		if(RegSetValueEx(hkSoftware, valueName, 0, REG_BINARY, (LPBYTE)&arFlDef[i], sizeof(FLOAT)) != ERROR_SUCCESS)
		{
			RegCloseKey(hkSoftware);
			return FALSE;
		}
	}
	for(UINT i = 0; i < nString; i++)
	{
		Locale.GetString(iBase+nVar+nFloat+i, valueName, MAX_VALUE_NAME_LEN);
		if(RegSetValueEx(hkSoftware, valueName, 0, REG_SZ, (LPBYTE)(arWStrDef[i]), (DWORD)wcslen(arWStrDef[i])*2+1) != ERROR_SUCCESS)
		{
			RegCloseKey(hkSoftware);
			return FALSE;
		}
	}
	return TRUE;
}

BOOL SettingsClass::Load()
{
	HKEY hkSoftware;
	DWORD nBytes;
	RegOpenKeyEx(hKey, szSubKey, NULL, KEY_QUERY_VALUE, &hkSoftware);
	for(UINT i = 0; i < nVar; i++)
	{
		Locale.GetString(iBase+i, valueName, MAX_VALUE_NAME_LEN);
		nBytes = sizeof UINT;
		if(RegQueryValueEx(hkSoftware, valueName, NULL, NULL, (LPBYTE)&values[i], &nBytes) != ERROR_SUCCESS)
		{
			RegCloseKey(hkSoftware);
			return FALSE;
		}
	};
	for(UINT i = 0; i < nFloat; i++)
	{
		Locale.GetString(iBase+nVar+i, valueName, MAX_VALUE_NAME_LEN);
		nBytes = sizeof FLOAT;
		if(RegQueryValueEx(hkSoftware, valueName, NULL, NULL, (LPBYTE)&floats[i], &nBytes) != ERROR_SUCCESS)
		{
			RegCloseKey(hkSoftware);
			return FALSE;
		}
	};
	for(UINT i = 0; i < nString; i++)
	{
		Locale.GetString(iBase+nVar+nFloat+i, valueName, MAX_VALUE_NAME_LEN);
		nBytes = MAX_VALUE_NAME_LEN;
		if(RegQueryValueEx(hkSoftware, valueName, NULL, NULL, (LPBYTE)strings[i], &nBytes) != ERROR_SUCCESS)
		{
			RegCloseKey(hkSoftware);
			return FALSE;
		}
	};
	RegCloseKey(hkSoftware);
	return TRUE;
}

BOOL SettingsClass::Save()
{
	HKEY hkSoftware;
	DWORD nBytes;
	RegOpenKeyEx(hKey, szSubKey, NULL, KEY_SET_VALUE, &hkSoftware);
	for(UINT i = 0; i < nVar; i++)
	{
		Locale.GetString(iBase+i, valueName, MAX_VALUE_NAME_LEN);
		nBytes = sizeof UINT;
		RegSetValueEx(hkSoftware, valueName, NULL, REG_DWORD, (LPBYTE)&values[i], nBytes);
	};
	for(UINT i = 0; i < nFloat; i++)
	{
		Locale.GetString(iBase+nVar+i, valueName, MAX_VALUE_NAME_LEN);
		nBytes = sizeof FLOAT;
		RegSetValueEx(hkSoftware, valueName, NULL, REG_BINARY, (LPBYTE)&floats[i], nBytes);
	};
	for(UINT i = 0; i < nString; i++)
	{
		Locale.GetString(iBase+nVar+nFloat+i, valueName, MAX_VALUE_NAME_LEN);
		nBytes = (DWORD)wcslen(strings[i])*2+1;
		RegSetValueEx(hkSoftware, valueName, NULL, REG_SZ, (LPBYTE)strings[i], nBytes);
	};
	RegCloseKey(hkSoftware);
	MessageBeep(MB_ICONASTERISK);
	return TRUE;
}

UINT SettingsClass::GetValue(UINT id)
{
	return values[id];
}

VOID SettingsClass::SetValue(UINT id, DWORD value)
{
	values[id] = value;
}

FLOAT SettingsClass::GetFValue(UINT id)
{
	return floats[id];
}

VOID SettingsClass::SetFValue(UINT id, FLOAT value)
{
	floats[id] = value;
}

LPWSTR SettingsClass::GetString(UINT id)
{
	return strings[id];
}

VOID SettingsClass::SetString(UINT id, LPWSTR string)
{
	wcscpy_s(strings[id], MAX_REG_STRING_LEN, string);
}

BOOL SettingsClass::BackUp()
{
	
	return TRUE;
}
