# include <Windows.h>

# define ENCODE					0
# define DECODE					1

# define NIBBLE_BITS			4
# define BYTE_BITS				8

# define MAX_DATA_LEN			2000

# define GROUP_RAW				0
# define GROUP_TEXT				1
# define GROUP_NUMBER			2
# define GROUP_OBJECT			3

# define TYPE_BINARY			0
# define TYPE_OCTAL				1
# define TYPE_DECIMAL			2
# define TYPE_HEX				3
# define TYPE_BASE32			4
# define TYPE_BASE64			5
# define TYPE_FILE				6

# define TYPE_ASCII				0
# define TYPE_ANSI				1
# define TYPE_UNICODE			2

# define TYPE_LATLONG			0

# define BIN_BLOCK_BIT_SIZE		1
# define OCT_BLOCK_BIT_SIZE		3
# define HEX_BLOCK_BIT_SIZE		NIBBLE_BITS
# define BASE_32_BLOCK_BIT_SIZE	5
# define BASE_64_BLOCK_BIT_SIZE	6
# define FILE_BLOCK_BIT_SIZE	BYTE_BITS

# define ASCII_BLOCK_BIT_SIZE	7
# define ANSI_BLOCK_BIT_SIZE	BYTE_BITS
# define UNICODE_BLOCK_BIT_SIZE	BYTE_BITS*2

# define LATLNG_BLOCK_BIT_SIZE	16

VOID OutMode();

UINT GetBlockSize(UINT modeGroup, UINT typeGroup);
VOID SetModeVars(UINT modeGroup);
