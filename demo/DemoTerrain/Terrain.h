#ifndef C_TERRAIN_H
#define C_TERRAIN_H

//-------------------------------------------------------------------
//  CLASS
//  CTerrain
//
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------


// The map size.
#define MAP 256 
// Used to index a 2D coordinate in a 1D array.
#define INDEX(x, y) (((x)&255) + (((y)&255) << 8)) 
// A point (10, 2) on the map is (320, 64) in the world coordinates, i.e. (10*32, 64*32).
#define COMP 32 
// A simple colour
typedef struct COLOUR {
	float r, g, b;
} COLOUR;

//-------------------------------------------------------------------
class CTerrain
{
	/// This is the holding space for the landscape. 
	float y[MAP*MAP];
	/// This is the holding space for the landscape colors. 
	COLOUR c[MAP*MAP];
	/// Temporaries
	int position_x, position_z;
	int min_x, min_z, max_x, max_z;

public:  
    CTerrain();
    virtual ~CTerrain();

	void CreateFractal(void);
	void Render(float lookx, float lookz, float xpos, float zpos);	
	float GetHeight(float positionx, float positiony);
};

//-------------------------------------------------------------------
#endif 