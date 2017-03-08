#define N_IMPLEMENTS TSkin
//-------------------------------------------------------------------
//  skin.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/skin.h"
#include "guide/vcl.h"
#include "guide/tga.h"
#include "guide/debug.h"

#include <stdexcept>

//-------------------------------------------------------------------
//  TSkin()
//  27-Sep-2003   rzv   created
//-------------------------------------------------------------------
TSkin::TSkin()
{
	Button = NULL;
	Form = NULL;
	CaptionBar = NULL;
	CheckBtn = NULL;
	RadioBtn = NULL;
	BitBtn = NULL;
	Edit = NULL;
	ListBox = NULL;
	ComboBoxButton = NULL;
	ComboListBox = NULL;
	ComboBox = NULL;
	MainMenu = NULL;
	MainMenuItem = NULL;
	PopupMenu = NULL;
	PopupMenuItem = NULL;
	ScrollButtonMinHorz = NULL;
	ScrollButtonMaxHorz = NULL;
	ScrollButtonMinVert = NULL;
	ScrollButtonMaxVert = NULL;	
	ScrollThumbHorz = NULL;
	ScrollThumbVert = NULL;
	ScrollBar = NULL;

	DefaultFont = NULL;
	DefaultMouseCursor = NULL;
	Shadow = NULL;
}

//-------------------------------------------------------------------
//  ~TSkin()
//  27-Sep-2003   rzv   created
//-------------------------------------------------------------------
TSkin::~TSkin()
{
    if(Button != NULL)
	    delete Button;
    if(Form != NULL)
	    delete Form;
    if(CaptionBar != NULL)
	    delete CaptionBar;
    if(CheckBtn != NULL)
	    delete CheckBtn;
    if(RadioBtn != NULL)
	    delete RadioBtn;
    if(BitBtn != NULL)
	    delete BitBtn;
    if(Edit != NULL)
	    delete Edit;
    if(ListBox != NULL)
	    delete ListBox;
    if(ComboBoxButton != NULL)
	    delete ComboBoxButton;
    if(ComboListBox != NULL)
	    delete ComboListBox;
    if(ComboBox != NULL)
	    delete ComboBox;
    if(MainMenu != NULL)
	    delete MainMenu;
    if(MainMenuItem != NULL)
	    delete MainMenuItem;
    if(PopupMenu != NULL)
	    delete PopupMenu;
    if(PopupMenuItem != NULL)
	    delete PopupMenuItem;
    if(ScrollButtonMinHorz != NULL)
	    delete ScrollButtonMinHorz;
    if(ScrollButtonMaxHorz != NULL)
	    delete ScrollButtonMaxHorz;
    if(ScrollButtonMinVert != NULL)
	    delete ScrollButtonMinVert;
    if(ScrollButtonMaxVert != NULL)
	    delete ScrollButtonMaxVert;
    if(ScrollThumbHorz != NULL)
	    delete ScrollThumbHorz;
    if(ScrollThumbVert != NULL)
	    delete ScrollThumbVert;
    if(ScrollBar != NULL)
	    delete ScrollBar;

	if(Shadow != NULL)
		delete Shadow;

	DestroyTextures();
	DestroyIcons();
	DestroyFonts();
	DestroyMouseCursors();
}
//-------------------------------------------------------------------
/**
	@brief Return size in pixels for the specified set of icons.
	@param Kind Type of icons to retrieve the size for.
	@return Size of the specified type of icons.
*/
unsigned int TSkin::GetIconSize(TIconKind Kind)
{
	if(IconsSize.count(Kind))
		return IconsSize[Kind];

	return 0;
}

//-------------------------------------------------------------------
//  GetTexture()
//  24-May-2004   rzv   created
//-------------------------------------------------------------------
TTexture* TSkin::GetTexture(TString Name)
{  
	// Trivial
	//return Textures[Name];

	// Version 0
	if(Textures.count(Name))
		return Textures[Name];

	return NULL;
  
	/*
    // Version 1
    TTexturesList::iterator iter = Textures.find(Name);
    if(iter != Textures.end())
		 return iter->second;
   
    t_printf("Texture not found: %s\n", Name.c_str());
    return NULL;
    */

	/* 
	// Version 2
    TTexturesList::iterator iter = Textures.find(Name);
    if(iter != Textures.end())
		 return Textures[Name];
   
    t_printf("Texture not found: %s\n", Name.c_str());
    return NULL;
	*/
}

//-------------------------------------------------------------------
/**
	@brief Release memory allocated for textures.
*/
//-------------------------------------------------------------------
void TSkin::DestroyTextures(void)
{
	TTexturesList::iterator iter; 
	for(iter = Textures.begin(); iter != Textures.end(); iter++) 
		delete (*iter).second;
     
	Textures.clear();
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the specified icon from the resources.
*/
//-------------------------------------------------------------------
TTexture* TSkin::GetIcon(TString Name, TIconKind Kind = iconSmall)
{  
	switch(Kind)
	{
		case iconSmall:
			if(IconsSmall.count(Name))
				return IconsSmall[Name];
			break;
		case iconMedium:
			if(IconsMedium.count(Name))
				return IconsMedium[Name];
			break;
		case iconLarge:
			if(IconsLarge.count(Name))
				return IconsLarge[Name];
			break;
	}

	return NULL;
}

//-------------------------------------------------------------------
/**
	@brief Release memory allocated for icons.
*/
//-------------------------------------------------------------------
void TSkin::DestroyIcons(void)
{
	TIconsListSmall::iterator iter; 
	for(iter = IconsSmall.begin(); iter != IconsSmall.end(); iter++) 
		delete (*iter).second;

	for(iter = IconsMedium.begin(); iter != IconsMedium.end(); iter++) 
		delete (*iter).second;

	for(iter = IconsLarge.begin(); iter != IconsLarge.end(); iter++) 
		delete (*iter).second;

	IconsSmall.clear();
	IconsMedium.clear();
	IconsLarge.clear();
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the path where textures are stored.	
*/
//-------------------------------------------------------------------
const char* TSkin::GetTexturesPath(void)
{
	TiXmlElement* Element = XmlSkin.FirstChildElement("TSkin");
	return Element->Attribute("TexturesPath");
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the path where fonts are stored.	
*/
//-------------------------------------------------------------------
const char* TSkin::GetFontsPath(void)
{
	TiXmlElement* Element = XmlSkin.FirstChildElement("TSkin");
	return Element->Attribute("FontsPath");
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the path where mouse cursors are stored.	
*/
//-------------------------------------------------------------------
const char* TSkin::GetCursorsPath(void)
{
	TiXmlElement* Element = XmlSkin.FirstChildElement("TSkin");
	return Element->Attribute("CursorsPath");
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the path where file icons are stored.	
*/
//-------------------------------------------------------------------
const char* TSkin::GetIconsPath(TIconKind Kind = iconSmall)
{
	TiXmlElement* Element = XmlSkin.FirstChildElement("TSkin");
	
	switch(Kind)
	{
		case iconSmall:
			return Element->Attribute("SmallIconsPath");
			break;
		case iconMedium:
			return Element->Attribute("MediumIconsPath");
			break;
		case iconLarge:
			return Element->Attribute("LargeIconsPath");
			break;
	}

	return NULL;
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the full path to the specified texture.	
*/
//-------------------------------------------------------------------
TString TSkin::GetFullTextureName(const char* Filename)
{
	const char* TexturesPath = GetTexturesPath();
	t_assert(TexturesPath);

	TString FullName(TexturesPath);
	FullName.append(Filename);
	return FullName;
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the full path to the specified icon.	
*/
//-------------------------------------------------------------------
TString TSkin::GetFullIconName(const char* Filename, TIconKind Kind = iconSmall)
{
	const char* IconsPath = GetIconsPath(Kind);
	t_assert(IconsPath);

	TString FullName(IconsPath);
	FullName.append(Filename);
	return FullName;
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the full path to the specified font.	
*/
//-------------------------------------------------------------------
TString TSkin::GetFullFontName(const char* Filename)
{
	const char* FontsPath = GetFontsPath();
	t_assert(FontsPath);

	TString FullName(FontsPath);
	FullName.append(Filename);
	return FullName;
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the full path to the specified cursor.	
*/
//-------------------------------------------------------------------
TString TSkin::GetFullCursorName(const char* Filename)
{
	const char* CursorsPath = GetCursorsPath();
	t_assert(CursorsPath);

	TString FullName(CursorsPath);
	FullName.append(Filename);
	return FullName;
}

/**
	Load textures from a specified graphic file. Usually, an image 
	contains several glyphs (such as states for a standard button) 
	that will be generated here and stored into the textures list.

	@param Filename		Name of the graphic file we need to load
						glyphs from.
	@param NumGlyphs	Number of glyphs this image file is containing.
	@return				<code>true</code>, if glyphs were successfull 
						generated, <code>false</code> if not.
*/
bool TSkin::LoadTexture(const char* Filename, int NumGlyphs)
{
	TTexture* Texture = new TTexture;  
	if(!Texture->LoadNoUpload(GetFullTextureName(Filename).c_str()))
	{
		delete Texture;
		return false;
	}

	TPicture* Picture = Texture->GetPicture();
	
	// Store the picture info for later use
	unsigned char* ImageData = Picture->GetData(); 
	unsigned int ImageWidth = Picture->GetWidth();
	unsigned int ImageHeight = Picture->GetHeight();
	unsigned int BitDepth = Picture->GetBitdepth();
	unsigned int Chanels = BitDepth / 8;

	// The width and height of one glyph
	unsigned int GlyphWidth = ImageWidth / NumGlyphs;
	unsigned int GlyphHeight = ImageHeight;

	// For every glyph
	for(int n=0; n<NumGlyphs; n++)
	{
		// Alloc memory to store the glyph's data
		unsigned char* GlyphData = new unsigned char[GlyphWidth * GlyphHeight * Chanels];

		// Use the picture's data to set the glyph's data
		for(unsigned int i=0; i<ImageHeight; i++)
		{
			for(unsigned int j=0; j<GlyphWidth * Chanels; j++)
			{
				GlyphData[i * GlyphWidth * Chanels + j] = 
					ImageData[i * ImageWidth * Chanels + n * GlyphWidth * Chanels + j];
			}
		}

		// Create the glyph
		TPicture* Glyph = new TPicture;
		Glyph->MakePicture(GlyphWidth, GlyphHeight, BitDepth, GlyphData);

		// Create a new texture based on glyph
		TTexture* NewTexture = new TTexture;
		NewTexture->Load(Glyph);
		
		// Create a new texture name
		TString Name;
		Name.assign(Filename);
		int Pos = Name.find(".");
		Name.assign(Name.substr(0, Pos));

		char buf[128];
		sprintf( buf, "%d", n );
		Name.append(buf);
		
		// Fill the map with the new entry
		Textures[Name] = NewTexture;

		delete Glyph;
		delete[] GlyphData;		
	}
    
	delete Texture;

	return true;
}

//-------------------------------------------------------------------
//  LoadTextures()
//  24-May-2004   rzv   created
//-------------------------------------------------------------------
bool TSkin::LoadTextures(TiXmlElement* XmlElement)
{
	TiXmlElement* Element;
	const char* ValueName;
	const char* ValueNum;

	// Read textures
	for(Element = XmlElement->FirstChildElement("Texture");
		Element;
		Element = Element->NextSiblingElement("Texture"))
	{
		ValueName = Element->Attribute("Name");
		ValueNum = Element->Attribute("Num");

		LoadTexture(ValueName, atoi(ValueNum));
	}

	return true;
}

/**
	Load icon from a specified graphic file.

	@param Filename		Name of the graphic file we need to load
	glyphs from.
	@return				<code>true</code>, if icon were successfull generated, <code>false</code> if not.
*/
bool TSkin::LoadIconTexture(const char* Filename, TIconKind Kind)
{
	TTexture* Texture = new TTexture;
	if(!Texture->Load(GetFullIconName(Filename, Kind).c_str()))
	{
		delete Texture;
		return false;
	}

	// Create a new icon name
	TString Name;
	Name.assign(Filename);
	int Pos = Name.find(".");
	Name.assign(Name.substr(0, Pos));

	// Fill the map with the new entry
	switch(Kind)
	{
		case iconSmall:
			IconsSmall[Name] = Texture;
			break;
		case iconMedium:
			IconsMedium[Name] = Texture;
			break;
		case iconLarge:
			IconsLarge[Name] = Texture;
			break;
	}

	return true;
}

//-------------------------------------------------------------------
/**
	@brief Load icons from resources.	
*/
//-------------------------------------------------------------------
bool TSkin::LoadIcons(TiXmlElement* XmlElement, TIconKind Kind)
{
	TiXmlElement* Element;
	const char* ValueName;

	// Read icons
	for(Element = XmlElement->FirstChildElement("Icon");
		Element;
		Element = Element->NextSiblingElement("Icon"))
	{
		ValueName = Element->Attribute("Name");
		LoadIconTexture(ValueName, Kind);
	}

	return true;
}

//-------------------------------------------------------------------
//  LoadMouseCursors()
//  03-June-2004   rzv   created
//-------------------------------------------------------------------
bool TSkin::LoadFonts(TiXmlElement* XmlElement)
{
	TiXmlElement* Element;
	const char* ValueName;
	const char* ValueSize;

	// Read textures
	for(Element = XmlElement->FirstChildElement("Font");
		Element;
		Element = Element->NextSiblingElement("Font"))
	{
		ValueName = Element->Attribute("Name");
		ValueSize = Element->Attribute("Size");

		LoadFont(ValueName, atoi(ValueSize));
	}

	return true;
}

//-------------------------------------------------------------------
//  LoadFont()
//  20-June-2003   rzv   created
//-------------------------------------------------------------------
bool TSkin::LoadFont(const char* Name, int Size)
{
	char buf[256];
    sprintf(buf, "%s%i", Name, Size);
    TString FontKey = TString(buf);

	// Try to see if the font isn't already loaded
	TFontsList::iterator iter = Fonts.find(FontKey);
    if(iter != Fonts.end())
		return true;
	
	TFont* NewFont = new TFont;   
	try 
	{
		NewFont->Load(GetFullFontName(Name).c_str(), Size);
	}
	catch(stl::exception& error)
	{
		t_printf("Error: %s\n", error.what()); 
		delete NewFont;
		return false;
	}
        
    Fonts[FontKey] = NewFont;

	return true;
}

//-------------------------------------------------------------------
//  GetFont()
//  20-June-2004   rzv   created
//-------------------------------------------------------------------
TFont* TSkin::GetFont(const char* Name, int Size)
{
	 char buf[256];
     sprintf(buf, "%s%i", Name, Size);
     TString FontKey = TString(buf);
            
     TFontsList::iterator iter = Fonts.find(FontKey);
     if(iter != Fonts.end())
		 return iter->second;
         
     t_printf("Font not found: %s Size: %d\nReturn default font.\n", Name, Size);
	 return DefaultFont;  
}

//-------------------------------------------------------------------
//  DestroyFonts()
//  03-July-2004   rzv   created
//-------------------------------------------------------------------
void TSkin::DestroyFonts(void)
{	
	TFontsList::iterator iter; 
	for(iter = Fonts.begin(); iter != Fonts.end(); iter++)   
		 delete (*iter).second;
     
	Fonts.clear();
}

//-------------------------------------------------------------------
//  GetMouseCursor()
//  22-March-2004   rzv   created
//-------------------------------------------------------------------
TMouseCursor* TSkin::GetMouseCursor(const char* Name)
{
     TString MouseCursorKey;
	 MouseCursorKey.assign(Name);
            
     TMouseCursorsList::iterator iter = MouseCursors.find(MouseCursorKey);
     if(iter != MouseCursors.end())
		 return iter->second;
   
     t_printf("Mouse cursor not found: %s\n", Name);
     return NULL;
}

//-------------------------------------------------------------------
//  LoadMouseCursor()
//  20-June-2004   rzv   created
//-------------------------------------------------------------------
bool TSkin::LoadMouseCursor(const char* Name, TPoint HotSpot)
{
    TString MouseCursorKey;
	MouseCursorKey.assign(Name);

	// Try to see if the mouse cursor isn't already loaded
	TMouseCursorsList::iterator iter = MouseCursors.find(MouseCursorKey);
    if(iter != MouseCursors.end())
		return true;
	
	TMouseCursor* NewMouseCursor = new TMouseCursor;   
	NewMouseCursor->Create(GetFullCursorName(Name).c_str(), HotSpot);
        
    MouseCursors[MouseCursorKey] = NewMouseCursor;

	return true;
}

//-------------------------------------------------------------------
//  LoadMouseCursors()
//  03-June-2004   rzv   created
//-------------------------------------------------------------------
bool TSkin::LoadMouseCursors(TiXmlElement* XmlElement)
{
	TPoint HotSpot;
	TiXmlElement* Element;
	const char* ValueName;
	const char* ValueHotSpot;

	// Read textures
	for(Element = XmlElement->FirstChildElement("Cursor");
		Element;
		Element = Element->NextSiblingElement("Cursor"))
	{
		ValueName = Element->Attribute("Name");
		ValueHotSpot = Element->Attribute("HotSpot");
		
		sscanf(ValueHotSpot, "%d,%d", &HotSpot.x, &HotSpot.y);

		LoadMouseCursor(ValueName, HotSpot);
	}

	return true;
}

//-------------------------------------------------------------------
//  DestroyMouseCursors()
//  22-March-2004   rzv   created
//-------------------------------------------------------------------
void TSkin::DestroyMouseCursors(void)
{	
	TMouseCursorsList::iterator iter; 
	for(iter = MouseCursors.begin(); iter != MouseCursors.end(); iter++)   
		 delete (*iter).second;
     
	 MouseCursors.clear();
}

//-------------------------------------------------------------------
/**
	@brief Load resources specified from the XML file. Resources
	could be textures, fonts, cursors.
*/
//-------------------------------------------------------------------
bool TSkin::LoadResXML(const char* Filename)
{
	if(!XmlResources.LoadFile(Filename))
	{
		t_printf( "Could not load resources file %s. Error='%s'. Exiting.\n", Filename, XmlSkin.ErrorDesc() );
		return false;
	}
	
	TiXmlElement* Element = NULL;
	int TempValue;

	// Get the "Textures" element
	Element = XmlResources.FirstChildElement("Textures");
	if(Element)
		LoadTextures(Element);

	// Get the "IconsSmall" element
	Element = XmlResources.FirstChildElement("IconsSmall");
	if(Element)
	{
		LoadIcons(Element, iconSmall);
		sscanf(Element->Attribute("Size"), "%d", &TempValue);
		SetIconSize(iconSmall, TempValue);
	}

	// Get the "IconsMedium" element
	Element = XmlResources.FirstChildElement("IconsMedium");
	if(Element)
	{
		LoadIcons(Element, iconMedium);
		sscanf(Element->Attribute("Size"), "%d", &TempValue);
		SetIconSize(iconMedium, TempValue);
	}

	// Get the "IconsLarge" element
	Element = XmlResources.FirstChildElement("IconsLarge");
	if(Element)
	{
		LoadIcons(Element, iconLarge);
		sscanf(Element->Attribute("Size"), "%d", &TempValue);
		SetIconSize(iconLarge, TempValue);
	}

	// Get the "Fonts" element
	Element = XmlResources.FirstChildElement("Fonts");
	if(Element)
		LoadFonts(Element);

	// Get the "Cursors" element
	Element = XmlResources.FirstChildElement("Cursors");
	if(Element)
		LoadMouseCursors(Element);
	
	return true;
}
//-------------------------------------------------------------------
/**
	@brief Load properties for each visual control defined by the graphic 
	interface. 
	
	Beware that only properties are loaded and no kind of control 
	initialization is made because Create() function  is not called. This 
	means that no child objects for the controls are instantiated this time. 
	For example, we could have a name of  the mouse cursor, but not 
	TMouseCursor object that each control contains. Later, at the control
	initialization phase, you can only relay for these properties and
	not expect that child of skin controls below are valid.
*/
//-------------------------------------------------------------------
void TSkin::LoadSkinXML(const char* Filename)
{	
	if(!XmlSkin.LoadFile(Filename))
		throw stl::runtime_error("Skin file could not be loaded.");

	TiXmlNode* XmlNode = NULL;
	TiXmlElement* XmlElement = NULL;

	// Get the "Skin" element
	XmlNode = XmlSkin.FirstChild("TSkin");
	XmlElement = XmlNode->ToElement();
	if(!XmlElement)
		throw stl::runtime_error("Skin - XML not valid (missing <TSkin> tag).");

	// Load various resources (textures, fonts, cursors ...)
	if(!LoadResXML(XmlElement->Attribute("Resources")))
		throw stl::runtime_error("Skin - Resources xml is not valid.");

	TiXmlElement* Element = NULL;

	// Set default mouse cursor
	Element = XmlNode->FirstChildElement("DefaultCursor");
	if(Element)
	{
		DefaultMouseCursor = GetMouseCursor(Element->Attribute("Name"));
		if(!DefaultMouseCursor)
			throw stl::runtime_error("Skin - Default mouse cursor should be valid.");
	}
	else
		t_printf("Warning: Missing default cursor.\n");

	// Set default font
	Element = XmlNode->FirstChildElement("DefaultFont");
	if(Element)
	{
		DefaultFont = GetFont(Element->Attribute("Name"), atoi(Element->Attribute("Size")));
		if(!DefaultFont)
			throw stl::runtime_error("Skin - Default font should be valid.");
	}
	else
		t_printf("Warning: Missing default font.\n");

	Button = new TButton;
	Form = new TForm;
	CaptionBar = new TCaptionBar;
	CheckBtn = new TCheckBtn;
	RadioBtn = new TRadioBtn;
	BitBtn = new TBitBtn;
	Edit = new TEdit;
	ListBox = new TListBox;
	ComboBoxButton = new TComboBoxButton;
	ComboListBox = new TComboListBox;
	ComboBox = new TComboBox;
	MainMenu = new TMainMenu;
	MainMenuItem = new TMainMenuItem;
	PopupMenu = new TPopupMenu;
	PopupMenuItem = new TPopupMenuItem;
	ScrollButtonMinHorz = new TScrollButton;
	ScrollButtonMaxHorz = new TScrollButton;
	ScrollButtonMinVert = new TScrollButton;
	ScrollButtonMaxVert = new TScrollButton;
	ScrollThumbHorz = new TScrollThumbHorz;
	ScrollThumbVert = new TScrollThumbVert;
	ScrollBar = new TScrollBar;

	// Read button 
	Element = XmlNode->FirstChildElement("TButton");
	if(Element)
		Button->ParseSkin(Element);

	// Read form
	Element = XmlNode->FirstChildElement("TForm");
	if(Element)
		Form->ParseSkin(Element);

	// Read caption bar 
	Element = XmlNode->FirstChildElement("TCaptionBar");
	if(Element)
		CaptionBar->ParseSkin(Element);

	// Read check button 
	Element = XmlNode->FirstChildElement("TCheckBtn");
	if(Element)
		CheckBtn->ParseSkin(Element);

	// Read radio button 
	Element = XmlNode->FirstChildElement("TRadioBtn");
	if(Element)
		RadioBtn->ParseSkin(Element);	

	// Read bitmap button 
	Element = XmlNode->FirstChildElement("TBitBtn");
	if(Element)
		BitBtn->ParseSkin(Element);

	// Read edit control
	Element = XmlNode->FirstChildElement("TEdit");
	if(Element)
		Edit->ParseSkin(Element);

	// Read ScrollButtonMinHorz
	Element = XmlNode->FirstChildElement("TScrollButtonMinHorz");
	if(Element)
		ScrollButtonMinHorz->ParseSkin(Element);

	// Read ScrollButtonMaxHorz
	Element = XmlNode->FirstChildElement("TScrollButtonMaxHorz");
	if(Element)
		ScrollButtonMaxHorz->ParseSkin(Element);	

	// Read ScrollButtonMinVert
	Element = XmlNode->FirstChildElement("TScrollButtonMinVert");
	if(Element)
		ScrollButtonMinVert->ParseSkin(Element);	

	// Read ScrollButtonMaxVert
	Element = XmlNode->FirstChildElement("TScrollButtonMaxVert");
	if(Element)
		ScrollButtonMaxVert->ParseSkin(Element);	

	// Read scroll thumb horizontal
	Element = XmlNode->FirstChildElement("TScrollThumbHorz");
	if(Element)
		ScrollThumbHorz->ParseSkin(Element);	

	// Read scroll thumb vertical
	Element = XmlNode->FirstChildElement("TScrollThumbVert");
	if(Element)
		ScrollThumbVert->ParseSkin(Element);		

	// Read scroll bar
	Element = XmlNode->FirstChildElement("TScrollBar");
	if(Element)
		ScrollBar->ParseSkin(Element);	

	// Read list box
	Element = XmlNode->FirstChildElement("TListBox");
	if(Element)
		ListBox->ParseSkin(Element);	

	// Read combo box button
	Element = XmlNode->FirstChildElement("TComboBoxButton");
	if(Element)
		ComboBoxButton->ParseSkin(Element);	

	// Read combo list box
	Element = XmlNode->FirstChildElement("TComboListBox");
	if(Element)
		ComboListBox->ParseSkin(Element);		

	// Read combo box
	Element = XmlNode->FirstChildElement("TComboBox");
	if(Element)
		ComboBox->ParseSkin(Element);	

	// Read main menu
	Element = XmlNode->FirstChildElement("TMainMenu");
	if(Element)
		MainMenu->ParseSkin(Element);		

	// Read main menu item
	Element = XmlNode->FirstChildElement("TMainMenuItem");
	if(Element)
		MainMenuItem->ParseSkin(Element);	
	
	// Read pop up menu
	Element = XmlNode->FirstChildElement("TPopupMenu");
	if(Element)
		PopupMenu->ParseSkin(Element);	

	// Read pop up menu item
	Element = XmlNode->FirstChildElement("TPopupMenuItem");
	if(Element)
		PopupMenuItem->ParseSkin(Element);		
}

//-------------------------------------------------------------------
//  Load()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
bool TSkin::Load(const char* Filename)
{
	try 
	{
		LoadSkinXML(Filename);
	}
	catch(stl::exception& error)
	{
		t_printf("Error: %s\n", error.what());
		return false;
	}

	// Create the shadow object, after the skin has initialized, because
	// shadow needs textures to be loaded before it can be created
	Shadow = new TShadow(this);

	return true;
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


