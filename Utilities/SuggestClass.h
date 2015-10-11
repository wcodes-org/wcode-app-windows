# include "DictionaryClass.h"
# include "AlphaTreeClass.h"

class SuggestClass
{
private:
	AlphaTreeClass AlphaTree;

	LPWSTR szBase;
	LPWSTR szMid;
	UINT lBase;
	LPWSTR *arSugRems;
	UINT nSug;

public:
	SuggestClass(DictionaryClass& Dictionary);
	~SuggestClass();
	BOOL Suggest(const WCHAR c, LPWSTR& szSugList);
	UINT GetTerm(UINT iLocal, LPWSTR& sRemn);
	BOOL IsValid();
	VOID Reset();
};
