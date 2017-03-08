#ifndef T_TGA_H
#define T_TGA_H
//-------------------------------------------------------------------
//  CLASS
//  TTga 
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TTga
#include "guide/ndefdllclass.h"

#ifndef T_PICTURE_H
#include "guide/picture.h"
#endif


//-------------------------------------------------------------------
class N_PUBLIC TTga : public TPicture  
{
	struct TTgaHeader
	{
		unsigned char id_length;
		unsigned char colour_map_type;
		unsigned char image_type;

		// colourmap spec.  5 bytes
		short int     colour_map_first_entry;  // Ignore
		short int     colour_map_length;       // Usually 256
		unsigned char colour_map_entry_size;   // Usually 24-bit

		// image spec.  10 bytes
		short int     x_origin;  // Ignore
		short int     y_origin;  // Ignore
		short int     width;
		short int     height;
		unsigned char pixel_depth;       // Usually 24 or 32
		unsigned char image_descriptor;  // Ignore

		// Added for 'compeletness' :)
		int   components;
		int   bytes;
	};

private:
	TTgaHeader Header;

public:
	TTga();
	virtual ~TTga();
	
	bool LoadFromFile(const char* Filename);
	bool WriteToFile(const char* Filename);

private:
	void GetImageHeader(FILE* file);
	void GetImageData(FILE* file);
	void GetPackets(FILE* file);
	void PutPacketTuples(unsigned char *temp_colour, int &current_byte);
	void GetAPacket(int &current_byte, FILE* file);

};

//-------------------------------------------------------------------
#endif

