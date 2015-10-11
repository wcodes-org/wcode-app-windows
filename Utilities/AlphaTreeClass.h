# ifndef ALPHATREE_CLASS_HEADER
# define ALPHATREE_CLASS_HEADER

# include <Windows.h>

# include "DictionaryClass.h"
# include "BranchStruct.h"
# include "TraceClass.h"

class AlphaTreeClass
{
private:
	Branch* trunk;
	Branch* traced;
	TraceClass trace;
	BOOL bValid;

public:
	AlphaTreeClass();
	~AlphaTreeClass();
	VOID Load(DictionaryClass &Dictionary);
	VOID Reset();
	BOOL TraceC(WCHAR c);
	BOOL IsValid();
	// Get Next into szRemn
	BOOL GetNextRemn(LPWSTR szRemn);
};

# endif
