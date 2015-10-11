# ifndef CLIPBOARD_HEADER
# define CLIPBOARD_HEADER

# include "Windows.h"

BOOL CopyToClpBrd(LPVOID data, UINT len, UINT uFormat);
BOOL PasteFrmClpBrd(LPVOID data, UINT len, UINT uFormat);

# endif CLIPBOARD_HEADER
