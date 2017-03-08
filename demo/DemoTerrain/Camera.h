#ifndef C_CAMERA_H
#define C_CAMERA_H

//-------------------------------------------------------------------
//  CLASS
//  Camera
//
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------

// These are used for the motion
#define FORWARD 1
#define ROTATE 2
#define LOOKUP 3

//-------------------------------------------------------------------
class CCamera 
{
public:
	float xpos, ypos, zpos;
	float lookx, looky, lookz;
	float speed;
	float height;

public:
	CCamera();
    virtual ~CCamera();
	
	void SetSpeed(float s) { speed = s; }
	float GetSpeed(void) const { return speed; }

	void UpdateDirection(float x, float z);
	void Move(int type, float amount);	
	

};

//-------------------------------------------------------------------
#endif 
