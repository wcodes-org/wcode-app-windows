# include "DictionaryClass.h"

# define MAX_N_TOKENS				2048

# define MAX_TOKEN_LEN				100
# define COMMENT_CHAR				L'\''

# define ERROR_MAX_TOKEN_BOUND_OVER	-4548575
# define ERROR_TOKEN				-5687453

# define CARRIAGE_RETURN			L'\r'
# define LINE_FEED					L'\n'

# define UNICODE_HEADER				0xFEFF

VOID DictionaryClass::Create() {
	token = new LPWSTR[MAX_N_TOKENS];
	tokenLen = new UINT[MAX_N_TOKENS];
	iToken = 0;
	nTokens = 0;
}

DictionaryClass::DictionaryClass() {
	Create();
}

DictionaryClass::DictionaryClass(LPWSTR szConfigFile) {
	Create();
	Load(szConfigFile);
}

DictionaryClass::~DictionaryClass() {
	delete[] token;
	delete tokenLen;
}

VOID DictionaryClass::Load(LPWSTR szConfigFile) {

	HANDLE hFile;
	DWORD dwNumRead;
	BOOL bTest;
	WCHAR *buffer;
	DWORD size;

	hFile = CreateFile(szConfigFile, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		switch(GetLastError()) {
			case ERROR_FILE_NOT_FOUND:
				MessageBox(NULL, L"LC Error #0 File Not Found", L"Console", MB_OK | MB_ICONEXCLAMATION);
				break;
			case ERROR_PATH_NOT_FOUND:
				MessageBox(NULL, L"LC Error #1 Path Not Found", L"Console", MB_OK | MB_ICONEXCLAMATION);
				break;
			default:
				MessageBox(NULL, L"LC Error #2 Unknown Error", L"Console", MB_OK | MB_ICONEXCLAMATION);
		}
	size = GetFileSize(hFile,NULL);
	buffer = new WCHAR[size/2];

	bTest = ReadFile(hFile, buffer, size, &dwNumRead,NULL);
	CloseHandle(hFile);

	for(UINT i = 1; i < size/2;) {
		if(buffer[i] == COMMENT_CHAR) {
			i++;
			while(i < size + 1)
				if(buffer[i++] == 0x000d) {
					if(buffer[i++] == 0x000a)
						break;
					i--;
				};
			continue;
		}
		if(buffer[i] == 0x000d) {
			i++;
			if(buffer[i++] == 0x000a)
				continue;
			i--;
		}
		token[nTokens] = new WCHAR[MAX_TOKEN_LEN];
		
		{
		UINT j;
		for(j = 0; !(buffer[i] == 0x000d); i++,j++)
			token[nTokens][j] = buffer[i];
		if(j >= MAX_TOKEN_LEN)
			exit(ERROR_MAX_TOKEN_BOUND_OVER);
		token[nTokens][j] = NULL;
		tokenLen[nTokens] = j;
		nTokens++;
		}
	}
	if(nTokens > MAX_N_TOKENS)
		exit(-34787);

}

UINT DictionaryClass::NTokens() {
	return nTokens;
}

LPWSTR DictionaryClass::Token(UINT i) {
	return token[i];
}

UINT DictionaryClass::TokenLen(UINT i) {
	return tokenLen[i];
}

BOOL DictionaryClass::Index(UINT& index, LPWSTR token) {
	for(UINT i = 0; i < nTokens; i++) {
		if(!wcscmp(token, DictionaryClass::token[i])) {
			index = i;
			return TRUE;
		}
	}
	return FALSE;
}
