#ifndef T_PICTURE_H
#define T_PICTURE_H
//-------------------------------------------------------------------
//  CLASS
//  TPicture 
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TPicture
#include "guide/ndefdllclass.h"

//-------------------------------------------------------------------

class N_PUBLIC TPicture  
{
protected:
	unsigned int Width;
	unsigned int Height;
	unsigned int Bitdepth;
	unsigned char* Data;

public:
	TPicture();
	virtual ~TPicture();
	
	bool MakePicture(unsigned int WidthSrc, unsigned int HeightSrc, 
		unsigned int BitdepthSrc, unsigned char* DataSrc);

	unsigned int GetWidth(void) const { return Width; }
	unsigned int GetHeight(void) const { return Height; }
	unsigned int GetBitdepth(void) const { return Bitdepth; }
	unsigned char* GetData(void) const { return Data; }
		
	virtual bool LoadFromFile(const char* Filename);
	virtual bool WriteToFile(const char* Filename);	
};

//-------------------------------------------------------------------
#endif 

