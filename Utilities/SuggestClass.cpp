# include "SuggestClass.h"

# define MAX_DICT_TOKEN_LEN		20

# define MAX_N_SUGGESTIONS		10
# define MAX_SUG_LIST_LEN		200
# define ALPHA_W_OFFSET			L'a'

# define BASE_DECIMAL			10

//extern DictionaryClass Dictionary;

SuggestClass::SuggestClass(DictionaryClass& Dictionary)
{
	AlphaTree.Load(Dictionary);
	szBase = new WCHAR[MAX_DICT_TOKEN_LEN];
	szMid = new WCHAR[MAX_DICT_TOKEN_LEN];
	arSugRems = new LPWSTR[MAX_N_SUGGESTIONS];
	for(UINT i = 0; i < MAX_N_SUGGESTIONS; i++)
		arSugRems[i] = new WCHAR[MAX_DICT_TOKEN_LEN];
	nSug = 0;
	lBase = 0;
}

SuggestClass::~SuggestClass()
{
	delete[] arSugRems;
}

BOOL SuggestClass::Suggest(const WCHAR c, LPWSTR& szSugList)
{
	szSugList[0] = NULL;
	WCHAR szIndex[5];
	if(AlphaTree.TraceC(c))
	{
		szBase[lBase++] = c;
		szBase[lBase] = NULL;
		for(nSug = 0; nSug < MAX_N_SUGGESTIONS && AlphaTree.GetNextRemn(arSugRems[nSug]); nSug++)
		{
			if(nSug%5==0)
			{
				if(nSug)
					wcscat_s(szSugList, MAX_SUG_LIST_LEN, L"\n\n");
			}
			else
				wcscat_s(szSugList, MAX_SUG_LIST_LEN, L"    ");
			if(nSug == 9)
				szIndex[0] = L'0';
			else
				szIndex[0] = L'0'+nSug+1;//_itow_s(nSug+1, szIndex, 5, BASE_DECIMAL);
			szIndex[1] = NULL;
			wcscat_s(szSugList, MAX_SUG_LIST_LEN, szIndex);
			wcscat_s(szSugList, MAX_SUG_LIST_LEN, L"-");
			wcscat_s(szSugList, MAX_SUG_LIST_LEN, szBase);
			wcscat_s(szSugList, MAX_SUG_LIST_LEN, arSugRems[nSug]);
		}
		if(nSug == 1)
		{
			szSugList[0] = L' ';
			szSugList[1] = L' ';
		}
		return TRUE;
	}
	else
		return FALSE;
}

UINT SuggestClass::GetTerm(UINT i, LPWSTR& sRemn)
{
	if(i >= nSug)
		return 0;
	else
	{
		sRemn = arSugRems[i];
		return (UINT)wcslen(arSugRems[i]);
	}
}

BOOL SuggestClass::IsValid()
{
	return AlphaTree.IsValid();
}

VOID SuggestClass::Reset()
{
	nSug = 0;
	szBase[0] = NULL;
	lBase = 0;
	AlphaTree.Reset();
}
