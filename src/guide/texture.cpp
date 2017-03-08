#define N_IMPLEMENTS TTexture
//-------------------------------------------------------------------
//  texture.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/texture.h"
#include "guide/osincludes.h"
#include "guide/tga.h"
#include "guide/bmp.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TTexture()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
TTexture::TTexture(void)
{
	Picture = NULL;
	TexId = 0;
	Format = GL_RGB;
}

//-------------------------------------------------------------------
//  ~TTexture()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
TTexture::~TTexture(void)
{
	if(Picture != NULL)
		delete Picture;
}

//-------------------------------------------------------------------
//  Assign()
//  23-May-2004   rzv   created
//-------------------------------------------------------------------
void TTexture::Assign(TObject* Object)
{
	TTexture* ATexture = (TTexture*)Object;
	if(!ATexture)
		return;

	Load(ATexture->GetPicture());
}

//-------------------------------------------------------------------
//  GetWidth()
//  26-May-2004   rzv   created
//-------------------------------------------------------------------
int TTexture::GetWidth(void) const 
{ 
	if(Picture != NULL) 
		return Picture->GetWidth();

	return 0;
}

//-------------------------------------------------------------------
//  GetHeight()
//  26-May-2004   rzv   created
//-------------------------------------------------------------------
int TTexture::GetHeight(void) const 
{ 
	if(Picture != NULL) 
		return Picture->GetHeight(); 

	return 0;
}


//-------------------------------------------------------------------
//  LoadNoUpload()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TTexture::LoadNoUpload(const char* Filename) 
{
	if(Picture != NULL)
	{
		delete Picture;
		Picture = NULL;
	}

	TFileServer* FileServer = TScreen::Singleton->GetFileServer();

	if(FileServer->CheckExtension(Filename,"tga"))
		Picture = new TTga;
	else if(FileServer->CheckExtension(Filename,"bmp"))
		Picture = new TBmp;
	else
	{
		t_printf("Unsupported file extension for %s. Not loaded!\n", Filename);
		return false;
	}

	if(!Picture->LoadFromFile(Filename)) 
	{
		t_printf("File %s not loaded!\n", Filename);

		delete Picture;
		Picture = NULL;
		return false;
	}

	switch(Picture->GetBitdepth())
	{
		case 8:
			Format = GL_ALPHA;
			break;
		case 24:
			Format = GL_RGB;
			break;
		case 32:
			Format = GL_RGBA;
			break;
	}		

	return true;
}

//-------------------------------------------------------------------
//  Load()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TTexture::Load(const char* Filename) 
{		
	if(!LoadNoUpload(Filename))
		return false;

	Bind();

	return true;
}

//-------------------------------------------------------------------
//  Load()
//  28-Sep-2003   rzv   created
//-------------------------------------------------------------------
bool TTexture::Load(const TString& Filename) 
{		
	if(!Load(Filename.c_str()))
		return false;

	return true;
}

//-------------------------------------------------------------------
//  Load()
//  13-Jan-2003   rzv   created
//-------------------------------------------------------------------
bool TTexture::Load(TPicture* APicture)
{
	if(!APicture || APicture->GetData() == NULL)
		return false;
	
	if(Picture != NULL)
	{
		delete Picture;
		Picture = NULL;
	}

	Picture = new TPicture;
	Picture->MakePicture(APicture->GetWidth(), APicture->GetHeight(), APicture->GetBitdepth(), APicture->GetData());

	switch(Picture->GetBitdepth())
	{
		case 8:
			Format = GL_ALPHA;
			break;
		case 24:
			Format = GL_RGB;
			break;
		case 32:
			Format = GL_RGBA;
			break;
	}

	Bind();

	return true;
}

//-------------------------------------------------------------------
//  CreateEmpty()
//  05-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TTexture::CreateEmpty(int Width, int Height, int Bpp, TColor Color)
{	
	int Red = GetRed(Color);
	int Green = GetGreen(Color);
	int Blue = GetBlue(Color);

	unsigned char* Data = new unsigned char[Width*Height*Bpp/8];

	for(int i=0;i<Width*Height*Bpp/8;i+=3)
	{
		Data[i] = Red;
		Data[i+1] = Green;
		Data[i+2] = Blue;
	}

	if(Picture != NULL)
	{
		delete Picture;
		Picture = NULL;
	}

	Picture = new TPicture;
	Picture->MakePicture(Width, Height, Bpp, Data);

	// We do not need data anymore
	delete[] Data;

	switch(Bpp)
	{
		case 8:
			Format = GL_ALPHA;
			break;
		case 24:
			Format = GL_RGB;
			break;
		case 32:
			Format = GL_RGBA;
			break;
	}

	Bind();
}

//-------------------------------------------------------------------
//  SetSubImage()
//  05-Nov-2003   rzv   created
//-------------------------------------------------------------------
bool TTexture::SetSubImage(TPicture* APicture, int XOffset, int YOffset)
{
	if(!APicture)
		return false;

	glBindTexture(GL_TEXTURE_2D, TexId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, XOffset, YOffset, APicture->GetWidth(), APicture->GetHeight(), (GLenum)Format, GL_UNSIGNED_BYTE, APicture->GetData());
	
	return true;
}

//-------------------------------------------------------------------
//  SetSubImage()
//  23-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TTexture::SetSubImage(int Width, int Height, int XOffset, int YOffset, unsigned char* Data)
{
	glBindTexture(GL_TEXTURE_2D, TexId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, XOffset, YOffset, Width, Height, (GLenum)Format, GL_UNSIGNED_BYTE, Data);
}

//-------------------------------------------------------------------
//  Bind()
//  13-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TTexture::Bind(void)
{
	t_assert(Picture != NULL);
	t_assert(Picture->GetData() != NULL);

	glGenTextures(1, &TexId);
	glBindTexture(GL_TEXTURE_2D, TexId);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, Format, Picture->GetWidth(), Picture->GetHeight(), 0, Format, GL_UNSIGNED_BYTE, Picture->GetData());
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

