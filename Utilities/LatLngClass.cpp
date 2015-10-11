# include "LatLngClass.h"

# include "PackUnpack.h"
# include "Utilities.h"

# define N_BLOB_ELEMENTS		8
# define BLOB_ELEMENT_MAX_SIZE	8

# define MAX_BLOB_LEN			200
# define MAX_UNIT_LEN			50

# define DECIMAL				10

//	if(lat.deg == N_LAT_DEG)
//	if(lng.deg == N_LNG_DEG)

# define N_LAT_DEG				90
# define N_MIN					60
# define N_SEC					60
# define N_POL					2

# define NORTH					'N'
# define SOUTH					'S'
# define EAST					'E'
# define WEST					'W'

# define SYM_DEG				"°"
# define SYM_MIN				"'"
# define SYM_SEC				"\""
# define SPACE					" "

const UINT64 A = (UINT64) N_MIN*N_SEC*N_POL * N_LAT_DEG*N_MIN*N_SEC*N_POL;
const UINT64 B = (UINT64) N_SEC*N_POL * N_LAT_DEG*N_MIN*N_SEC*N_POL;
const UINT64 C = (UINT64) N_POL * N_LAT_DEG*N_MIN*N_SEC*N_POL;
const UINT64 D = (UINT64) N_LAT_DEG*N_MIN*N_SEC*N_POL;
const UINT64 E = (UINT64) N_MIN*N_SEC*N_POL;
const UINT64 F = (UINT64) N_SEC*N_POL;
const UINT64 G = (UINT64) N_POL;

VOID LatLngClass::Encode(LPBYTE arLatLng, UINT& lBD, UINT& lbT, LPSTR lnBlob, UINT len)
{
	LPSTR * arBlob = new LPSTR[N_BLOB_ELEMENTS];
	Load(arBlob, lnBlob, len);
	lat.deg = atoi(arBlob[0]);
	lat.min = atoi(arBlob[1]);
	lat.sec = atoi(arBlob[2]);
	lat.bPl = arBlob[3][0]==NORTH? TRUE : FALSE;	// else: SOUTH
	lng.deg = atoi(arBlob[4]);
	lng.min = atoi(arBlob[5]);
	lng.sec = atoi(arBlob[6]);
	lng.bPl = arBlob[7][0]== EAST? TRUE : FALSE;	// else:  WEST

	UINT64 latLng = lng.deg * A + \
					lng.min * B + \
					lng.sec * C + \
					lng.bPl * D + \
					lat.deg * E + \
					lat.min * F + \
					lat.sec * G + \
					lat.bPl;

	Pack(arLatLng, lBD, lbT, GetBitSize(latLng), (LPBYTE)&latLng);
}

VOID LatLngClass::Decode(LPSTR lnBlob, LPBYTE arLatLng, UINT n, UINT lbT)
{
	UINT64 latlng = 0;
	Unpack((LPBYTE)&latlng, arLatLng, n, lbT);
	lng.deg = (USHORT)(latlng/A);
	latlng %= A;
	lng.min = (USHORT)(latlng/B);
	latlng %= B;
	lng.sec = (USHORT)(latlng/C);
	latlng %= C;
	lng.bPl = (BOOL)(latlng/D);
	latlng %= D;
	lat.deg = (USHORT)(latlng/E);
	latlng %= E;
	lat.min = (USHORT)(latlng/F);
	latlng %= F;
	lat.sec = (USHORT)(latlng/G);
	latlng %= G;
	lat.bPl = (BOOL)(latlng);
	Print(lnBlob);
}

VOID Load(LPSTR * arBlob, LPSTR lnBlob, UINT len)
{
	UINT i = 0;
	for(UINT j = 0; j < N_BLOB_ELEMENTS; j++)
	{
		arBlob[j] = new CHAR[BLOB_ELEMENT_MAX_SIZE];
		UINT k = 0;
		do
		{
			arBlob[j][k] = lnBlob[i];
			k++;
			i++;
		} while (lnBlob[i]!='\n' && k < BLOB_ELEMENT_MAX_SIZE && i < len);
		arBlob[j][k] = NULL;
		i++;
	}
}

VOID LatLngClass::Print(LPSTR lnBlob)
{
	LPSTR tmp = new CHAR[MAX_UNIT_LEN];
	_itoa_s(lat.deg, lnBlob, MAX_UNIT_LEN, DECIMAL);
	strcat_s(lnBlob, MAX_BLOB_LEN, SYM_DEG);

	_itoa_s(lat.min, tmp, MAX_UNIT_LEN, DECIMAL);
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);
	strcat_s(lnBlob, MAX_BLOB_LEN, SYM_MIN);

	_itoa_s(lat.sec, tmp, MAX_UNIT_LEN, DECIMAL);
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);
	strcat_s(lnBlob, MAX_BLOB_LEN, SYM_SEC);

	if(lat.bPl)
		tmp[0] = NORTH;
	else
		tmp[0] = SOUTH;
	tmp[1] = NULL;
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);

	strcat_s(lnBlob, MAX_BLOB_LEN, SPACE);

	_itoa_s(lng.deg, tmp, MAX_UNIT_LEN, DECIMAL);
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);
	strcat_s(lnBlob, MAX_BLOB_LEN, SYM_DEG);

	_itoa_s(lng.min, tmp, MAX_UNIT_LEN, DECIMAL);
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);
	strcat_s(lnBlob, MAX_BLOB_LEN, SYM_MIN);

	_itoa_s(lng.sec, tmp, MAX_UNIT_LEN, DECIMAL);
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);
	strcat_s(lnBlob, MAX_BLOB_LEN, SYM_SEC);

	if(lng.bPl)
		tmp[0] = EAST;
	else
		tmp[0] = WEST;
	tmp[1] = NULL;
	strcat_s(lnBlob, MAX_BLOB_LEN, tmp);
}
