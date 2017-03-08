#define N_IMPLEMENTS TTga
//-------------------------------------------------------------------
//  tga.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include <stdio.h>
#include <memory.h> 
#include "guide/tga.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TTga()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
TTga::TTga()
{
}

//-------------------------------------------------------------------
//  ~TTga()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
TTga::~TTga()
{
}

//-------------------------------------------------------------------
//  LoadFromFile()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TTga::LoadFromFile(const char* Filename)
{
	FILE* f;
	
	f = fopen(Filename, "r");
	if(!f) {
		t_printf("File not found: %s\n", Filename);
		return false;
	}

	GetImageHeader(f);
	GetImageData(f);

	fclose(f);
	
	if(Bitdepth != 24 && Bitdepth != 32)
		return false;
	
	if(!Data)
		return false;

	return true;
}

//-------------------------------------------------------------------
//  WriteToFile()
//  31-Aug-2002   rzv   created
//-------------------------------------------------------------------
bool TTga::WriteToFile(const char* Filename)
{
	remove(Filename);
	FILE* f = fopen(Filename, "w");
	
	// Write the header and dimensional Data first.
	fwrite("\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00",
		sizeof(char), 12, f);
	
	unsigned char dimensions[6];
	dimensions[0] = this->Width;
	dimensions[1] = this->Width / 256;
	dimensions[2] = this->Height;
	dimensions[3] = this->Height / 256;
	dimensions[4] = this->Bitdepth;
	dimensions[5] = 0;
	fwrite(&dimensions[0], sizeof(char), 6, f);

	if(!Data) {
		t_warn("TTga::WriteToFile(): No valuable Data to save!");
		return false;
	}

	// Swap red and blue bytes to form .tga BGR Data.
	for(unsigned int i=0; i<Width * Height * Bitdepth/8; i+=3) 
	{	
		unsigned char temp = Data[i];
		Data[i] = Data[i + 2];
		Data[i + 2] = temp;
	}
	
	fwrite(&Data[0], sizeof(char), Width * Height * Bitdepth/8, f);
	
	fclose(f);
	
	return true;
}

//-------------------------------------------------------------------
//  GetImageHeader()
//  08-Apr-2004   rzv   created
//-------------------------------------------------------------------
void TTga::GetImageHeader(FILE* file)
{
   /*   Stupid byte alignment means that we have to fread each field
        individually.  I tried splitting tgaHeader into 3 structures, no matter
        how you arrange them, colour_map_entry_size comes out as 2 bytes instead
        1 as it should be.  Grrr.  Gotta love optimising compilers - theres a pragma
        for Borland, but I dunno the number for MSVC or GCC :(
    */
	fread ( &Header.id_length,       ( sizeof (unsigned char )), 1, file );
	fread ( &Header.colour_map_type, ( sizeof (unsigned char )), 1, file );
	fread ( &Header.image_type,      ( sizeof (unsigned char )), 1, file );

	fread ( &Header.colour_map_first_entry, ( sizeof (short int )), 1, file );
	fread ( &Header.colour_map_length     , ( sizeof (short int )), 1, file );
	fread ( &Header.colour_map_entry_size , ( sizeof (unsigned char )), 1, file );

	fread ( &Header.x_origin , ( sizeof (short int )), 1, file );
	fread ( &Header.y_origin , ( sizeof (short int )), 1, file );
	fread ( &Header.width,     ( sizeof (short int )), 1, file );
	fread ( &Header.height,    ( sizeof (short int )), 1, file );

	fread ( &Header.pixel_depth,     ( sizeof (unsigned char )), 1, file );
	fread ( &Header.image_descriptor,( sizeof (unsigned char )), 1, file );

	// Set some stats
	Header.components = Header.pixel_depth / 8;
	Header.bytes      = Header.width * Header.height * Header.components;

	Width	 = Header.width;
	Height	 = Header.height;
	Bitdepth = Header.pixel_depth;
}

//-------------------------------------------------------------------
//  GetImageData()
//  08-Apr-2004   rzv   created
//-------------------------------------------------------------------
void TTga::GetImageData(FILE* file)
{
   Data = new unsigned char[Header.bytes];

   /* Easy unRLE image */
   if(Header.image_type == 1 || Header.image_type == 2 || Header.image_type == 3)
   {   
      fread(Data, sizeof (unsigned char), Header.bytes, file);

      /* Image is stored as BGR(A), make it RGB(A)     */   
	  unsigned char  temp;
      for(int i = 0; i < Header.bytes; i += Header.components)
      {
         temp = Data[i];
         Data[i] = Data[i + 2];
         Data[i + 2] = temp;
      }
   }
   
   /* RLE compressed image */
   if(Header.image_type == 9 || Header.image_type == 10)
      GetPackets(file);
}

//-------------------------------------------------------------------
//  GetPackets()
//  08-Apr-2004   rzv   created
//-------------------------------------------------------------------
void TTga::GetPackets(FILE* file)
{
  int current_byte = 0;

  while(current_byte < Header.bytes)
    GetAPacket(current_byte, file);
}

//-------------------------------------------------------------------
//  PutPacketTuples()
//  08-Apr-2004   rzv   created
//-------------------------------------------------------------------
void TTga::PutPacketTuples(unsigned char *temp_colour, int &current_byte)
{
   if(Header.components == 3)
   {
      Data[current_byte]   = temp_colour[2];
      Data[current_byte+1] = temp_colour[1];
      Data[current_byte+2] = temp_colour[0];
      current_byte += 3;
   }

   if(Header.components == 4 )    // Because its BGR(A) not (A)BGR :(
   {
      Data[current_byte]   = temp_colour[2];
      Data[current_byte+1] = temp_colour[1];
      Data[current_byte+2] = temp_colour[0];
      Data[current_byte+3] = temp_colour[3];
      current_byte += 4;
   }
}

//-------------------------------------------------------------------
//  GetAPacket()
//  08-Apr-2004   rzv   created
//-------------------------------------------------------------------
void TTga::GetAPacket(int &current_byte, FILE* file)
{   
	int            run_length;
	unsigned char  packet_header;
	unsigned char  temp_colour[4] = { 0x00, 0x00, 0x00, 0x00 };

	fread        ( &packet_header, ( sizeof ( unsigned char )), 1, file );
	run_length = ( packet_header&0x7F ) + 1;

   if ( packet_header&0x80 )  // RLE packet
   {
      fread(temp_colour, ( sizeof ( unsigned char )* Header.components ), 1, file );

      if(Header.components == 1 )  // Special optimised case :)
      {
         memset ( Data + current_byte, temp_colour[0], run_length);
         current_byte += run_length;
      } else
      for(int i = 0; i < run_length; i++)
         PutPacketTuples(temp_colour, current_byte);
   }

   if(!(packet_header&0x80))  // RAW packet
   {
      for(int i = 0; i < run_length; i++)
      {
         fread(temp_colour, (sizeof(unsigned char) * Header.components ), 1, file );

         if(Header.components == 1)
         {
            memset(Data + current_byte, temp_colour[0], run_length);
            current_byte += run_length;
         } else
            PutPacketTuples(temp_colour, current_byte);
      }
   }
} 

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

