#ifndef T_SKIN_H
#define T_SKIN_H
//-------------------------------------------------------------------
/**
	@class TSkin
	@brief Class that manages skins for the application.

	This class stores the layout of every visual control. When a 
	control is created at runtime, it interogates skin manager about
	how it should look. TSkin class is also responsible to keep the 
	track of other visual resources as textures, mouse cursors, fonts etc.

	@author Razvan Predescu
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TSkin
#include "guide/ndefdllclass.h"

#ifndef T_TEXTURE_H
#include "guide/texture.h"
#endif

#ifndef T_FONT_H
#include "guide/font.h"
#endif

#ifndef T_MOUSECURSOR_H
#include "guide/mousecursor.h"
#endif

#ifndef T_SHADOW_H
#include "guide/shadow.h"
#endif

#ifndef TINYXML_INCLUDED 
#include "tinyxml.h"
#endif

#ifndef T_STRINGCI_H
#include "string.h"
#endif

#include <map>

enum TIconKind { iconSmall, iconMedium, iconLarge };

//-------------------------------------------------------------------

typedef stl::map<TString, TTexture*> TTexturesList;
typedef stl::map<TString, TTexture*> TIconsListSmall;
typedef stl::map<TString, TTexture*> TIconsListMedium;
typedef stl::map<TString, TTexture*> TIconsListLarge;
typedef stl::map<TIconKind, unsigned int> TIconsSize;

typedef stl::map<TString, TFont*> TFontsList;
typedef stl::map<TString, TMouseCursor*> TMouseCursorsList;

//-------------------------------------------------------------------
class TButton;
class TForm;
class TCaptionBar;
class TCheckBtn;
class TRadioBtn;
class TBitBtn;
class TEdit;
class TScrollButton;
class TScrollThumb;
class TScrollBar;
class TListBox;
class TComboBoxButton;
class TComboListBox;
class TComboBox;
class TMainMenu;
class TMainMenuItem;
class TPopupMenu;
class TPopupMenuItem;
class N_PUBLIC TSkin
{
    TiXmlDocument XmlSkin; 
    TiXmlDocument XmlResources; 

	TTexturesList Textures;	
	TIconsListSmall IconsSmall;
	TIconsListMedium IconsMedium;
	TIconsListLarge IconsLarge;
	TIconsSize IconsSize;

	TMouseCursorsList MouseCursors;
	TFontsList Fonts;
	
	TMouseCursor* DefaultMouseCursor;
	TFont* DefaultFont;

	TShadow* Shadow;

public:
	TButton* Button;
	TForm* Form;
	TCaptionBar* CaptionBar;
	TCheckBtn* CheckBtn;
	TRadioBtn* RadioBtn;
	TBitBtn* BitBtn;
	TEdit* Edit;
	TScrollButton* ScrollButtonMinHorz;
	TScrollButton* ScrollButtonMaxHorz;
	TScrollButton* ScrollButtonMinVert;
	TScrollButton* ScrollButtonMaxVert;
	TScrollThumb* ScrollThumbHorz;
	TScrollThumb* ScrollThumbVert;
	TScrollBar* ScrollBar;
	TListBox* ListBox;
	TComboBoxButton* ComboBoxButton;
	TComboListBox* ComboListBox;
	TComboBox* ComboBox;
	TMainMenu* MainMenu;
	TMainMenuItem* MainMenuItem;
	TPopupMenu* PopupMenu;
	TPopupMenuItem* PopupMenuItem;

public:
	TSkin();
	virtual ~TSkin();
	
	void LoadSkinXML(const char* Filename);
	bool LoadResXML(const char* Filename);
	bool Load(const char* Filename);
	
	const char* GetTexturesPath(void);	
	const char* GetFontsPath(void);
	const char* GetCursorsPath(void);
	const char* GetIconsPath(TIconKind Kind);
	
	TTexture* GetTexture(TString Name);
	TShadow* GetShadow(void) const { return Shadow; } 
	TTexture* GetIcon(TString Name, TIconKind Kind);
	void SetIconSize(TIconKind Kind, unsigned int Value) { IconsSize[Kind] = Value; }
	unsigned int GetIconSize(TIconKind Kind);

	TFont* GetFont(const char* Name, int Size);
	TFont* GetDefaultFont(void) const { return DefaultFont; }
	
	TMouseCursor* GetMouseCursor(const char* Name);
	TMouseCursor* GetDefaultMouseCursor(void) const { return DefaultMouseCursor; }

private:
	TString GetFullCursorName(const char* Filename);
	TString GetFullFontName(const char* Filename);
	TString GetFullTextureName(const char* Filename);
	TString GetFullIconName(const char* Filename, TIconKind Kind);

	bool LoadTexture(const char* Filename, int NumGlyphs = 1);
	bool LoadTextures(TiXmlElement* XmlElement);
	void DestroyTextures(void);	

	bool LoadIconTexture(const char* Filename, TIconKind Kind);
	bool LoadIcons(TiXmlElement* XmlElement, TIconKind Kind);
	void DestroyIcons(void);	

	bool LoadFont(const char* Name, int Size = 14);
	bool LoadFonts(TiXmlElement* XmlElement);
	void DestroyFonts(void);
	
	bool LoadMouseCursor(const char* Filename, TPoint HotSpot);
	bool LoadMouseCursors(TiXmlElement* XmlElement);
	void DestroyMouseCursors(void);
};

//-------------------------------------------------------------------
#endif 

