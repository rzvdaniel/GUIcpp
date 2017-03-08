#ifndef T_BMP_H
#define T_BMP_H
//-------------------------------------------------------------------
//  CLASS
//  TBmp
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TBmp
#include "guide/ndefdllclass.h"

#ifndef T_PICTURE_H
#include "guide/picture.h"
#endif

//-------------------------------------------------------------------

const short BITMAP_MAGIC_NUMBER	= 19778;
const int	RGB_BYTE_SIZE		= 3;

//-------------------------------------------------------------------

class N_PUBLIC TBmp : public TPicture  
{
	#pragma pack(push,bitmap_data,1)
		typedef struct tagRGBQuad {
		char rgbBlue;
		char rgbGreen;
		char rgbRed;
		char rgbReserved;
	} RGBQuad;

	typedef struct tagBitmapFileHeader {
		unsigned short bfType;
		unsigned int bfSize;
		unsigned short bfReserved1;
		unsigned short bfReserved2;
		unsigned int bfOffBits;
	} BitmapFileHeader;

	typedef struct tagBitmapInfoHeader {
		unsigned int biSize;
		int biWidth;
		int biHeight;
		unsigned short biPlanes;
		unsigned short biBitCount;
		unsigned int biCompression;
		unsigned int biSizeImage;
		int biXPelsPerMeter;
		int biYPelsPerMeter;
		unsigned int biClrUsed;
		unsigned int biClrImportant;
	} BitmapInfoHeader;

	#pragma pack(pop,bitmap_data)

private:
	/// colour palette
	RGBQuad* Colours;
	/// bitmap file header
	BitmapFileHeader Bmfh;
	/// bitmap info header
    BitmapInfoHeader Bmih;

	/// the width in bytes of the image
    int ByteWidth; 
	/// the width in bytes of the added image
    int PadWidth;  
	/// size of the data in the file
    unsigned int DataSize;  
	
	bool Loaded;

public:
	TBmp();
	virtual ~TBmp();
	
	bool LoadFromFile(const char* Filename);
	bool WriteToFile(const char* Filename);    

private:
	/// convert to 24bit RGB bottom up data    
	bool Convert24(char*);	
	/// convert to 24bit RGB bottom up data
    bool Convert8(char*);		
};

//-------------------------------------------------------------------
#endif

