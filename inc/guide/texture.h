#ifndef T_TEXTURE_H
#define T_TEXTURE_H

//-------------------------------------------------------------------
//  CLASS
//  TTexture 
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TTexture
#include "guide/ndefdllclass.h"

#ifndef T_OBJECT_H
#include "guide/object.h"
#endif

#ifndef T_GRAPHICS_H
#include "guide/graphics.h"
#endif

#ifndef T_PICTURE_H
#include "guide/picture.h"
#endif

#include <string>

//-------------------------------------------------------------------

typedef stl::string TString;

//-------------------------------------------------------------------
class N_PUBLIC TTexture : public TObject
{
	TPicture* Picture;
	unsigned int TexId;
	unsigned int Format;	

public:
	TTexture(void);
	virtual ~TTexture(void);
	virtual void Assign(TObject* Object);
	
	int GetWidth(void) const;
	int GetHeight(void) const;

	unsigned int GetTexId(void) const { return TexId; }	
	unsigned int GetFormat(void) const { return Format; }
	TPicture* GetPicture(void) const { return Picture; }
	
	bool SetSubImage(TPicture* APicture, int XOffset, int YOffset);
	void SetSubImage(int Width, int Height, int XOffset, int YOffset, unsigned char* Data);
	
	bool Load(TPicture* APicture);
	bool Load(const TString& Filename);
	bool Load(const char* Filename);
	bool LoadNoUpload(const char* Filename);
	void CreateEmpty(int Width, int Height, int Bpp, TColor Color);
	
protected:
	void Bind(void);
};

//-------------------------------------------------------------------
#endif

