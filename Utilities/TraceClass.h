# include <Windows.h>

# include "BranchStruct.h"

struct TraceStackStruct
{
	Branch*	arBranch;
	UINT index;
};

class TraceClass
{
private:
	TraceStackStruct* traceStack;
	UINT lTraceStack;

	LPWSTR sTraced;

	BOOL bValid;
	BOOL bBranch;

	BOOL Push(Branch* arBranch, UINT index);
	BOOL Pop();

public:
	TraceClass();
	~TraceClass();
	VOID Reset(Branch* arBranch);

	BOOL GetNext();
	BOOL GetTraced(LPWSTR szTraced);
};
