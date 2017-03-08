#define N_IMPLEMENTS TPicture
//-------------------------------------------------------------------
//  picture.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/picture.h"
#include "guide/debug.h"
#include <memory.h>

//-------------------------------------------------------------------
//  TPicture()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
TPicture::TPicture()
{
	Width		= 0;
	Height		= 0;
	Bitdepth	= 0;
	Data		= NULL;
}

//-------------------------------------------------------------------
//  ~TPicture()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
TPicture::~TPicture()
{
	if(Data != NULL)
		delete[] Data;
}

//-------------------------------------------------------------------
//  MakePicture()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TPicture::MakePicture(unsigned int WidthSrc, unsigned int HeightSrc, 
		unsigned int BitdepthSrc, unsigned char* DataSrc)
{
	if(BitdepthSrc != 32 && BitdepthSrc != 24 && BitdepthSrc != 8)
		return false;

	if(!DataSrc) {
		t_warn("TPicture::MakePicture(): No valuable source data to process!");
		return false;
	}

	Width		= WidthSrc;
	Height		= HeightSrc;
	Bitdepth	= BitdepthSrc;

	Data = new unsigned char[WidthSrc * HeightSrc * BitdepthSrc / 8];
	memcpy(Data, DataSrc, WidthSrc * HeightSrc * BitdepthSrc / 8);

	return true;
}

//-------------------------------------------------------------------
//  LoadFromFile()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TPicture::LoadFromFile(const char* Filename)
{
	t_error("Pure virtual function called.");
	return false;
}

//-------------------------------------------------------------------
//  WriteToFile()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TPicture::WriteToFile(const char* Filename)
{
	t_error("Pure virtual function called.");
	return false;
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


