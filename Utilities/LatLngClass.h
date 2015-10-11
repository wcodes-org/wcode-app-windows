# ifndef LAT_LANG_HEADER
# define LAT_LANG_HEADER

# include <Windows.h>

struct LatLngS
{
	USHORT deg;
	USHORT min;
	USHORT sec;
	BOOL bPl;
};

class LatLngClass
{
private:
	LatLngS lat;
	LatLngS lng;
	VOID Print(LPSTR lnBlob);
public:
	VOID Encode(LPBYTE arLatLng, UINT& lBD, UINT& lbT, LPSTR lnBlob, UINT len);
	VOID Decode(LPSTR lnBlob, LPBYTE arLatLng, UINT n, UINT lbT);
};

VOID Load(LPSTR * arBlob, LPSTR lnBlob, UINT len);

# endif // LAT_LANG_HEADER
