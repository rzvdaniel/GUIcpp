#ifndef T_IMAGE_H
#define T_IMAGE_H
//-------------------------------------------------------------------
//  CLASS
//  TImage
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TImage
#include "guide/ndefdllclass.h"

#ifndef T_CONTROL_H
#include "guide/control.h"
#endif

enum TImageDisplay { idNormal, idCentered, idTile, idStretched };

//-------------------------------------------------------------------
class TTexture;
class N_PUBLIC TImage : public TControl 
{
	bool AutoSize;
	TImageDisplay Display;

protected:
	TTexture* Texture;

public:
	TImage();
	virtual ~TImage();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void LoadPicture(const char* Filename); 
	void LoadPicture(TString Filename); 

	void SetDisplay(TImageDisplay Value) { Display = Value; }
	TImageDisplay GetDisplay(void) const { return Display; }

	void SetAutoSize(bool Value);
	bool GetAutoSize(void) const { return AutoSize; }

protected:
	// Events
	virtual void OnPaint(void);
};

//-------------------------------------------------------------------
#endif 

