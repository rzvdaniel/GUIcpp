//-------------------------------------------------------------------
//  CCamera.cpp
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Terrain.h"
#include "Camera.h"

//-------------------------------------------------------------------
//  CCamera()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
CCamera::CCamera()
{
	xpos = 4096.0;
	ypos = 1000.0;
	zpos = 4096.0;
	lookx = 0.0;
	looky = 0.0; 
	lookz = 1.0;
	speed = 0;
	height = 16.0;
}

//-------------------------------------------------------------------
//  ~CCamera()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
CCamera::~CCamera()
{
}

//-------------------------------------------------------------------
//  UpdateDirection()
//  14-March-2004   E    created
//-------------------------------------------------------------------
void CCamera::UpdateDirection(float x, float z)
{
	Move(ROTATE, x);
	Move(LOOKUP, z);
}

//-------------------------------------------------------------------
//  Move()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void CCamera::Move(int type, float amount)
{
	float a;
	switch(type)
	{
		case FORWARD:
			xpos += lookx * amount;
			zpos += lookz * amount;
			break;
		case ROTATE:
			lookx = lookx*cos(amount) + lookz*sin(amount);
			lookz = lookz*cos(amount) - lookx*sin(amount);
			/* lookx^2 + lookz^2 != 1 for some reason. Fix. */
			a = 1/sqrt(lookx*lookx + lookz*lookz);
			lookx *= a;
			lookz *= a;
			break;
		case LOOKUP:
			looky += amount;
			break;
	}

	if(xpos<0) 
		xpos += MAP * COMP;
	else if(xpos>MAP * COMP) 
		xpos -= MAP * COMP;
	if(zpos<0) 
		zpos += MAP * COMP;
	else if(zpos>MAP * COMP) 
		zpos -= MAP * COMP;
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------
