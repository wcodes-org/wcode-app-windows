# include "FileIO.h"

# define WINDOW_TITLE			L"WCode Error"

# define MSG_FILE_NOT_FOUND		L"LC Error #0 File Not Found"
# define MSG_PATH_NOT_FOUND		L"LC Error #1 Path Not Found"
# define MSG_UNKNOWN_ERROR		L"LC Error #2 Unknown Error"

# define MSG_FILE_NOT_CREATED	L"File Creation Error"
# define MSG_FILE_NOT_WRITTEN	L"File Write Error"

# define BROWSE_FILE_FILTER		L"Text Files\0*.txt\0All Files\0*.*\0\0";

VOID LoadData(LPBYTE& data, UINT& dataSize, UINT& len, LPWSTR szDataFile)
// datasize = data buffer size. will be used if data buffer has to be resized
{
	HANDLE hFile;
	DWORD dwNumRead;
	BOOL bTest;
	DWORD size;

	hFile = CreateFile(szDataFile, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		switch(GetLastError())
		{
			case ERROR_FILE_NOT_FOUND:
				MessageBox(NULL, MSG_FILE_NOT_FOUND, WINDOW_TITLE, MB_OK | MB_ICONEXCLAMATION);
				break;
			case ERROR_PATH_NOT_FOUND:
				MessageBox(NULL, MSG_PATH_NOT_FOUND, WINDOW_TITLE, MB_OK | MB_ICONEXCLAMATION);
				break;
			default:
				MessageBox(NULL, MSG_UNKNOWN_ERROR, WINDOW_TITLE, MB_OK | MB_ICONEXCLAMATION);
		}
	size = GetFileSize(hFile,NULL);
	if(dataSize < size)
	{
		delete data;
		dataSize = size;
		data = new BYTE[size];
	}

	bTest = ReadFile(hFile, data, size, &dwNumRead,NULL);
	len = size;
	CloseHandle(hFile);
}

VOID WriteData(LPBYTE& data, UINT& len, LPWSTR szDataFile)
{
	HANDLE hFile;
	DWORD dwNumWritten;

	hFile = CreateFile(szDataFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(!hFile)
		MessageBox(NULL, MSG_FILE_NOT_CREATED, WINDOW_TITLE, MB_OK);
	if(!WriteFile(hFile, data, len, &dwNumWritten, NULL))
		MessageBox(NULL, MSG_FILE_NOT_WRITTEN, WINDOW_TITLE, MB_OK);
	CloseHandle(hFile);
}

BOOL BrowseFileOpenDialog(HWND hWndOwn, LPWSTR szFilePath)
{
	OPENFILENAME ofn;
//	LPWSTR szFileName = new WCHAR[MAX_PATH];
	szFilePath[0] = NULL;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWndOwn;
	ofn.lpstrFilter = BROWSE_FILE_FILTER;
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	//wcscpy_s(ofn.lpstrDefExt, ,"txt";

	if(GetOpenFileName(&ofn))
		return TRUE;
	else
		return FALSE;
}

BOOL BrowseFileSaveDialog(HWND hWndOwn, LPWSTR szFilePath)
{
	OPENFILENAME ofn;
//	LPWSTR szFileName = new WCHAR[MAX_PATH];
	szFilePath[0] = NULL;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWndOwn;
	ofn.lpstrFilter = BROWSE_FILE_FILTER;
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	//wcscpy_s(ofn.lpstrDefExt, ,"txt";

	if(GetSaveFileName(&ofn))
		return TRUE;
	else
		return FALSE;
}
