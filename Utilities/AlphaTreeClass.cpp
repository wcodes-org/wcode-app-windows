# include "AlphaTreeClass.h"

# define N_ALPHABETS		26
# define ALPHA_OFFSET		L'a'
# define MAX_WORD_LEN		20

# define R_F

AlphaTreeClass::AlphaTreeClass() {
	traced = trunk = new Branch[N_ALPHABETS]();
}

AlphaTreeClass::~AlphaTreeClass() {
	delete[] trunk;
}

VOID AlphaTreeClass::Load(DictionaryClass& Dictionary) {
	Branch* traced;
	for(UINT i = 0; i < Dictionary.NTokens(); i++) {
		traced = trunk;
		LPWSTR dictWord = Dictionary.Token(i);
		UINT lDictWord = Dictionary.TokenLen(i);
		for(UINT j = 0; j < lDictWord-1; j++) {
			UINT index = dictWord[j]-ALPHA_OFFSET;
			if(traced[index].arBranch == NULL)
				traced[index].arBranch = new Branch[N_ALPHABETS]();
			traced = traced[index].arBranch;
		}
		traced[dictWord[lDictWord-1]-ALPHA_OFFSET].bValid = TRUE;
	}
}

VOID AlphaTreeClass::Reset() {
	traced = trunk;
	bValid = FALSE;
	trace.Reset(traced);
}

BOOL AlphaTreeClass::TraceC(WCHAR c) {
	if(traced[c-ALPHA_OFFSET].arBranch != NULL || traced[c-ALPHA_OFFSET].bValid) {
		bValid = (traced[c-ALPHA_OFFSET]).bValid;
		traced = (traced[c-ALPHA_OFFSET]).arBranch;
		trace.Reset(traced);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL AlphaTreeClass::IsValid() {
	return bValid;//traced
}

BOOL AlphaTreeClass::GetNextRemn(LPWSTR szRemn) {
	while(trace.GetNext());
	return trace.GetTraced(szRemn);
}
