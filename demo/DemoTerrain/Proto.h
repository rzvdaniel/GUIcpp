#ifndef C_PROTO_H
#define C_PROTO_H

//-------------------------------------------------------------------
//  CLASS
//  Proto
//
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------

#ifndef C_CAMERA_H
#include "Camera.h"
#endif

#ifndef C_TERRAIN_H
#include "Terrain.h"
#endif

//-------------------------------------------------------------------
class CProto
{
	/// Camera
	CCamera* Camera;
	/// Terrain
	CTerrain* Terrain;
	
public:
	CProto();
    virtual ~CProto();

	void Init(void);
	void Render(int DisplayWidth, int DisplayHeight);

	CTerrain* GetTerrain(void) const { return Terrain; }
	CCamera* GetCamera(void) const { return Camera; }
};

//-------------------------------------------------------------------
#endif 
