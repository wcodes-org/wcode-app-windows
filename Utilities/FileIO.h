# ifndef FILE_IO_HEADER
# define FILE_IO_HEADER

# include <Windows.h>

VOID LoadData(LPBYTE& data, UINT& dataSize, UINT& len, LPWSTR szDataFile);
VOID WriteData(LPBYTE& data, UINT& len, LPWSTR szDataFile);

BOOL BrowseFileOpenDialog(HWND hWndOwn, LPWSTR szFilePath);
BOOL BrowseFileSaveDialog(HWND hWndOwn, LPWSTR szFilePath);

# endif // FILE_IO_HEADER