# include "TraceClass.h"
# include "BranchStruct.h"

# define MAX_TRACE_DEPTH	64
# define N_ALPHABETS		26
# define ALPHA_OFFSET		L'a'

# define MAX_MID_LEN		50
# define ERROR_PUSH_DEPTH	-45432

WCHAR AlphaCode(UINT index)
{
	return (WCHAR)index+ALPHA_OFFSET;
}

TraceClass::TraceClass()
{
	traceStack = new TraceStackStruct[MAX_TRACE_DEPTH];
	sTraced = new WCHAR[MAX_MID_LEN];
//	lTraceStack ; - instead Resetting
}

TraceClass::~TraceClass()
{
	delete[] traceStack;
	delete sTraced;
}

BOOL TraceClass::Push(Branch* arBranch, UINT index)
{
	if(lTraceStack == MAX_TRACE_DEPTH)
		return FALSE;
	else {
		traceStack[lTraceStack].arBranch = arBranch;
		traceStack[lTraceStack].index = 0;
		lTraceStack++;
		return TRUE;
	}
}

BOOL TraceClass::Pop()
{
	if(lTraceStack > 1)
	{
		lTraceStack--;
		return TRUE;
	}
	else
		return FALSE;
}

VOID TraceClass::Reset(Branch* arBranch)
{
	traceStack[0].arBranch = arBranch;
	traceStack[0].index = 0;
	lTraceStack = 1;
}

BOOL TraceClass::GetNext()	// next?
{
	while(lTraceStack)
	{
		UINT top = lTraceStack-1;
		Branch* xBranch = traceStack[top].arBranch;
		if(!xBranch)
		{
			bValid = FALSE;
			return FALSE;
		}
		UINT index = traceStack[top].index;

		if(traceStack[top].index < N_ALPHABETS-1)
			(traceStack[top].index)++;
		else
			if(!Pop())
			{
				bValid = FALSE;
				return FALSE;
			}

		bValid = (xBranch[index]).bValid;
		bBranch = (xBranch[index]).arBranch != NULL;
		if(bValid || bBranch)
		{
			sTraced[lTraceStack-1] = AlphaCode(index);
			if(bBranch)
				if(!Push((xBranch[index]).arBranch, 0))	//if(lTraceStack)
					exit(ERROR_PUSH_DEPTH);
			if(bValid)
				return FALSE;
			else
				return TRUE;
		}
	};
	return FALSE;
}

BOOL TraceClass::GetTraced(LPWSTR szTraced)
{
	if(bValid)
	{
		UINT l;

		if(bBranch)
			l = lTraceStack - 1;
		else
			l = lTraceStack;

		for(UINT i = 0; i < l; i++)
			szTraced[i] = TraceClass::sTraced[i];
		szTraced[l] = NULL;
		return TRUE;
	}
	else
		return FALSE;
}
