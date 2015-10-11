# ifndef CODES_HEADER
# define CODES_HEADER

# include <Windows.h>

# define BYTE_BITS		8

# define BASE2_BITS		2
# define BASE8_BITS		3
# define BASE16_BITS	4
# define BASE32_BITS	5
# define BASE64_BITS	6

# define TYPE_BINARY			0
# define TYPE_OCTAL				1
# define TYPE_DECIMAL			2
# define TYPE_HEX				3
# define TYPE_BASE32			4
# define TYPE_BASE64			5

static const char BASE2_TABLE [] = "01";
static const char BASE8_TABLE [] = "01234567";
static const char BASE10_TABLE [] = "0123456789";
static const char BASE16_TABLE [] = "0123456789ABCDEF";
static const char BASE32_TABLE [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
static const char BASE64_TABLE [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

UINT RationalizeA(UINT type, LPSTR sCode, UINT lCode);

# endif // CODES_HEADER
