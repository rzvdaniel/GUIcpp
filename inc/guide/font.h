#ifndef T_FONT_H
#define T_FONT_H
//-------------------------------------------------------------------
//  CLASS
//  TFont
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TFont
#include "guide/ndefdllclass.h"
 
#ifndef T_TYPEDEF_H
#include "typedef.h"
#endif

#ifndef T_OBJECT_H
#include "guide/object.h"
#endif

#ifndef T_GRAPHICS_H
#include "guide/graphics.h"
#endif

#ifndef T_STRINGCI_H
#include "string.h"
#endif

//-------------------------------------------------------------------
/**
	@class TFont
	@brief Font class.
*/
//-------------------------------------------------------------------
class TFont
{
public:
	TFont();
    virtual ~TFont();

	size_t GetSize(void) const;

	bool Load(const char* Name, int ASize);
 
	// The line height is constant
	size_t GetTextHeight(void) const;
	size_t GetHeight(void) const;

	// Knowing the width of a character or a string can be useful if you
	// want your UI to look good at all.
	size_t GetCharacterWidth(unsigned char c) const;
	size_t GetTextWidth(const TString& String) const;
	size_t GetTextWidth(const char* String) const;
	// Draw a string at a given position.
	void Text(float X, float Y, const TString& String);
	void Text(float X, float Y, const char* String);
  
private:
	// Information about a glyph. Tex_y2 can be calculated from tex_y1
	// and _tex_line_height (see below). Advance is the width of the
	// glyph in screen space.
	struct Glyph
	{
		float tex_x1, tex_y1, tex_x2;
		size_t advance;
	};
	// An array to store the glyphs.
	Glyph* _glyphs;
	// A table to quickly get the glyph belonging to a character.
	Glyph* _table[256];
	// The line height, in screen space and in texture space, and the
	// OpenGL id of the font texture.
	size_t _line_height, _texture;
	float _tex_line_height;
};

//-------------------------------------------------------------------
#endif 

