#ifndef T_BITBTN_H
#define T_BITBTN_H
//-------------------------------------------------------------------
/**
	@class TBitBtn
	@brief Base class for bitmapped buttons.
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TBitBtn
#include "guide/ndefdllclass.h"

#ifndef T_CUSTOMBUTTON_H
#include "guide/custombutton.h"
#endif

#ifndef T_TEXTURE_H
#include "guide/texture.h"
#endif

//-------------------------------------------------------------------
enum TButtonLayout { blGlyphCenter = 0, blGlyphLeft, blGlyphRight, blGlyphTop, blGlyphBottom};

class N_PUBLIC TBitBtn : public TCustomButton
{	
	TButtonLayout Layout;
	int Margin;
	int Spacing;

protected:
	TTexture* Glyph[5];
	TTexture* CurrentGlyph;
	float GlyphX;
	float GlyphY;

public:
	TBitBtn();
	virtual ~TBitBtn();
	virtual void Create(TComponent* AOwner, TRect Rect);
	virtual void ParseSkin(TiXmlElement* XmlElement);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);

	void SetLayout(TButtonLayout Value);
	TButtonLayout GetLayout(void) const { return Layout; }
	void SetSpacing(int Value);
	int GetSpacing(void) const { return Spacing; }
	void SetMargin(int Value);
	int GetMargin(void) const { return Margin; }
		
	void SetPicture(TPicture* Picture, int NumGlyphs);
	void LoadPicture(const char* Filename, int NumGlyphs);
	void LoadPicture(const TString& Filename, int NumGlyphs);

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnCaptureChanged(void);
	virtual void OnTextChanged(void);
	virtual void OnSize(int AWidth, int AHeight);

private:
	void UpdateLayout(void);
};

//-------------------------------------------------------------------
#endif 

