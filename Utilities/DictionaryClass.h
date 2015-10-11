# ifndef DICTIONARY_CLASS_HEADER
# define DICTIONARY_CLASS_HEADER

# include <Windows.h>

class DictionaryClass
{
private:
	LPWSTR* token;
	UINT* tokenLen;
	UINT iToken;
	UINT nTokens;

	VOID Create();

public:
	DictionaryClass();
	DictionaryClass(LPWSTR szConfigFile);
	~DictionaryClass();
	VOID Load(LPWSTR szConfigFile);
	UINT NTokens();
	LPWSTR Token(UINT i);
	UINT TokenLen(UINT i);
	BOOL Index(UINT&index, LPWSTR token);
};

# endif // DICTIONARY_CLASS_HEADER
