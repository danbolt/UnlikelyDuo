//
//	pcx.h - header file / freeware
//
//	David Henry - tfc_duke@hotmail.com
//


#ifndef		__PCX_H_
#define		__PCX_H_





// --------------------------------------------
// PCXHEADER - pcx header structure.
// --------------------------------------------



typedef struct tagPCXHEADER
{
	unsigned char	manufacturer;		// manufacturer
	unsigned char	version;			// version
	unsigned char	encoding;			// encoding type
	unsigned char	bitsPerPixel;		// number of bits per pixel

	unsigned short	x, y;				// ...
	unsigned short	width, height;		// dimensions
	unsigned short	horzRes, vertRes;	// horisontal and vertical screen resolutions

	unsigned char	*palette;			// color palette
	unsigned char	reserved;			// reserved
	unsigned char	numColorPlanes;		// number of planes

	unsigned short	bytesPerScanLine;	// byte per line
	unsigned short	paletteType;		// palette type
	unsigned short	horzSize, vertSize;	// ...

	unsigned char	padding[54];		// ...

} PCXHEADER, *PPCXHEADER;

#pragma pack(4)



// prototype
int LoadFilePCX( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert );



#endif // __PCX_H_
