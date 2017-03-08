#ifndef T_SHADOW_H
#define T_SHADOW_H
//-------------------------------------------------------------------
//  CLASS
//  TShadow
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TShadow
#include "guide/ndefdllclass.h"

//-------------------------------------------------------------------
class TSkin;
class TControl;
class TTexture;
class N_PUBLIC TShadow
{
    TTexture* TextureLeft[3];
    TTexture* TextureTop[3];
    TTexture* TextureRight[3];
    TTexture* TextureBottom[3];
     	 
public:
	TShadow(TSkin* Skin);
	virtual ~TShadow();

	void Render(TControl* Control);	
};

//-------------------------------------------------------------------
#endif 

