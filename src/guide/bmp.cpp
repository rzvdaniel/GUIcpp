#define N_IMPLEMENTS TBmp
//-------------------------------------------------------------------
//  bmp.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// Original code by: Mark Bernard
// e-mail: mark.bernard@rogers.com
//-------------------------------------------------------------------
#include <stdio.h>
#include "guide/bmp.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TBmp()
//  04-Aug-2003   rzv   created
//-------------------------------------------------------------------
TBmp::TBmp()
{
	Colours = NULL;
	Loaded = false;
}

//-------------------------------------------------------------------
//  ~TBmp()
//  04-Aug-2003   rzv   created
//-------------------------------------------------------------------
TBmp::~TBmp()
{
	if(Colours != NULL)
        delete[] Colours;
}

//-------------------------------------------------------------------
//  LoadFromFile()
//  Mark Bernard  created
//  04-Aug-2003   rzv   modified
//-------------------------------------------------------------------
bool TBmp::LoadFromFile(const char* Filename)
{	
	FILE* in;             // file stream for reading
    char* TempData;       // temp storage for image data
    int NumColours;       // total available colours

    // bitmap is not loaded yet
    Loaded = false;

    // make sure memory is not lost
    if(Colours != NULL)
        delete[] Colours;
    
    if(Data != NULL)
        delete[] Data;

	// open the file for reading in binary mode
    in = fopen(Filename,"rb");

    // if the file does not exist return false
    if(!in) {
		t_printf("File not found: %s\n", Filename);
        return false;
    }

	// read in the entire BITMAPFILEHEADER
    fread(&Bmfh, sizeof(BitmapFileHeader), 1, in);
    
	// check for the magic number that says this is a bitmap
    if(Bmfh.bfType != BITMAP_MAGIC_NUMBER) {
        t_printf("File is not in DIB format\n");
        fclose(in);
        return false;
    }

    //read in the entire BITMAPINFOHEADER
    fread(&Bmih, sizeof(BitmapInfoHeader), 1, in);

	// save the width, height and bits per pixel for external use
    Width = Bmih.biWidth;
    Height = Bmih.biHeight;
    Bitdepth = Bmih.biBitCount;

    // calculate the size of the image data with padding
    DataSize = (Width * Height * (unsigned int)(Bmih.biBitCount/8.0));

	// calculate the number of available colours
    NumColours = 1 << Bmih.biBitCount;

    // if the bitmap is not 8 bits per pixel or more return false
    if(Bitdepth < 8) {
        t_printf("File is not 8 or 24 bits per pixel\n");
        fclose(in);
        return false;
    }

    // load the palette for 8 bits per pixel
    if(Bitdepth == 8) {
    	Colours = new RGBQuad[NumColours];
    	fread(Colours,sizeof(RGBQuad), NumColours, in);
    }

    // set up the temporary buffer for the image data
    TempData = new char[DataSize];

	// exit if there is not enough memory
    if(TempData == NULL) {
        t_printf("Not enough memory to allocate a temporary buffer\n");
        fclose(in);
        return false;
    }

    // read in the entire image
    fread(TempData, sizeof(char), DataSize, in);

    // close the file now that we have all the info
    fclose(in);

    // calculate the witdh of the final image in bytes
    ByteWidth = PadWidth = (int)((float)Width*(float)Bitdepth/8.0);

    // adjust the width for padding as necessary
    while(PadWidth % 4 != 0) {
        PadWidth++;
    }

	// change format from GBR to RGB
    if(Bitdepth == 8)
    	Loaded = Convert8(TempData);
    else if(Bitdepth == 24)
    	Loaded = Convert24(TempData);

    // clean up memory
    delete[] TempData;

	return true;
}

//-------------------------------------------------------------------
//  WriteToFile()
//  04-Aug-2003   rzv   created
//-------------------------------------------------------------------
bool TBmp::WriteToFile(const char* Filename)
{
	return true;
}

//-------------------------------------------------------------------
//  Convert24()
//  Mark Bernard  created
//  04-Aug-2003   rzv   modified
//-------------------------------------------------------------------
bool TBmp::Convert24(char* TempData) 
{
	int offset, diff;

	diff = Width * Height * RGB_BYTE_SIZE;

    // allocate the buffer for the final image data
    Data = new unsigned char[diff];

    // exit if there is not enough memory
    if(Data == NULL) 
	{
        t_printf("Not enough memory to allocate an image buffer\n");
        delete[] Data;
        return false;
    }

    if(Height > 0) 
	{
        offset = PadWidth - ByteWidth;

        // count backwards so you start at the front of the image
        for(unsigned int i=0; i<DataSize; i+=3) 
		{
            // jump over the padding at the start of a new line
            if((i+1) % PadWidth == 0) {
                i += offset;
            }
            //transfer the data
            *(Data+i+2) = *(TempData+i);
            *(Data+i+1) = *(TempData+i+1);
            *(Data+i)   = *(TempData+i+2);
        }
    }
    // image parser for a forward image
    else 
	{
        offset = PadWidth - ByteWidth;
        int j = DataSize - 3;
        // count backwards so you start at the front of the image
		// here you can start from the back of the file or the front,
		// after the header  The only problem is that some programs
		// will pad not only the data, but also the file size to
		// be divisible by 4 bytes.
        for(unsigned int i=0; i<DataSize; i+=3) {
            //jump over the padding at the start of a new line
            if((i+1) % PadWidth == 0) {
                i += offset;
            }
            //transfer the data
            *(Data+j+2) = *(TempData+i);
            *(Data+j+1) = *(TempData+i+1);
            *(Data+j)   = *(TempData+i+2);
            j -= 3;
        }
    }

    return true;
}

//-------------------------------------------------------------------
//  Convert24()
//  Mark Bernard  created
//  04-Aug-2003   rzv   modified
//-------------------------------------------------------------------
bool TBmp::Convert8(char* TempData) 
{
	int offset, diff;

	diff = Width * Height * RGB_BYTE_SIZE;
    
	// allocate the buffer for the final image data
    Data = new unsigned char[diff];

    // exit if there is not enough memory
    if(Data == NULL) {
        t_printf("Not enough memory to allocate an image buffer\n");
        delete[] Data;
        return false;
    }

    if(Height > 0) 
	{
        offset = PadWidth - ByteWidth;
        int j=0;

        // count backwards so you start at the front of the image
        for(unsigned int i=0; i<DataSize * RGB_BYTE_SIZE; i+=3) 
		{
            // jump over the padding at the start of a new line
            if((i+1) % PadWidth == 0) {
                i += offset;
            }
            // transfer the data
            *(Data+i)	= Colours[*(TempData+j)].rgbRed;
            *(Data+i+1)	= Colours[*(TempData+j)].rgbGreen;
            *(Data+i+2)	= Colours[*(TempData+j)].rgbBlue;
            j++;
        }
    }
    // image parser for a forward image
    else {
        offset = PadWidth - ByteWidth;
        int j = DataSize - 1;

        // count backwards so you start at the front of the image
        for(unsigned int i=0; i<DataSize * RGB_BYTE_SIZE; i+=3) 
		{
            // jump over the padding at the start of a new line
            if((i+1) % PadWidth == 0) {
                i += offset;
            }
            // transfer the data
            *(Data+i)	= Colours[*(TempData+j)].rgbRed;
            *(Data+i+1)	= Colours[*(TempData+j)].rgbGreen;
            *(Data+i+2)	= Colours[*(TempData+j)].rgbBlue;
            j--;
        }
    }

    return true;
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

