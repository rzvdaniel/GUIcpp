//-------------------------------------------------------------------
//  CTerrain.cpp
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  Original code by:
//  Nicholas Anderson
//  email: ceenda@cee.hw.ac.uk
//  web  : http://www.ceenda.freeserve.co.uk/
//-------------------------------------------------------------------
#ifdef WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Terrain.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  CTerrain()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
CTerrain::CTerrain()
{
}

//-------------------------------------------------------------------
//  ~CTerrain()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
CTerrain::~CTerrain()
{
}

//-------------------------------------------------------------------
//  CreateFractal()
//  Uses fractal midpoint displacement to calculate a new landscape.
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void CTerrain::CreateFractal(void)
{
	int bsize, csize;
	int x, z, i;
	int r = 256; 
	float gradient, shadow = 0.5, n;

	for(x=0;x<=MAP;x++)
		for(z=0;z<=MAP;z++)
			y[INDEX(x,z)] = 0L;

	bsize = MAP;

	for(i=0; i<8; i++) {

		for(x=0;x<MAP;x+=bsize) {
			for(z=0;z<MAP;z+=bsize) {
		     	y[INDEX(x,z)] += (rand()%(r+1)-r/2);
			}
		}

		if(i>4)
			r=r/2;
		
		csize = bsize/2;
		if(csize>0) {
			for(x=0; x<MAP; x+=bsize) {
				for(z=0; z<MAP; z+=bsize) {
					if( x < MAP)
						y[INDEX(x+csize,z)] = (y[INDEX(x+bsize,z)]+y[INDEX(x,z)])/2;
					if( z < MAP)
						y[INDEX(x,z+csize)] = (y[INDEX(x,z+bsize)]+y[INDEX(x,z)])/2;
					if ( x < MAP && z < MAP )
						y[INDEX(x+csize,z+csize)] = ( y[INDEX(x,z)] + y[INDEX(x+bsize,z)] + y[INDEX(x,z+bsize)] + y[INDEX(x+bsize,z+bsize)]) / 4;
				}
			}
		}
		bsize = csize;
	}

	for(x=0; x<MAP; x++) {
		for(z=0; z<MAP; z++) {
			y[INDEX(x,z)] = y[INDEX(x,z)] + y[INDEX(x+1,z)] + y[INDEX(x+1,z+1)] + y[INDEX(x,z+1)];
			y[INDEX(x,z)] /= 4.0;
		}
	}
	
	for(x=MAP; x>0; x--) {
		for(z=0; z<MAP; z++) {
			y[INDEX(x,z)] = y[INDEX(x,z)] + y[INDEX(x-1,z)] + y[INDEX(x-1,z+1)] + y[INDEX(x,z+1)];
			y[INDEX(x,z)] /= 4.0;
		}
	}
	
	for(x=0; x<MAP; x++) {
		for(z=0; z<MAP; z++) {
			if(y[INDEX(x,z)]>8) {
				n = y[INDEX(x,z)];
				y[INDEX(x,z)] *= n;
				y[INDEX(x,z)] /= 256.0;
			}
		}
	}

	for(x=0; x<=MAP; x++) {
		for(z=0; z<=MAP; z++) {
			
			gradient = ((float) (y[INDEX(x,z)]-y[INDEX(x+1,z)])) / 100.0;
            if(y[INDEX(x,z)]>64) {
				if((y[INDEX(x,z)]-y[INDEX(x,z+1)])<8 && (y[INDEX(x,z)]-y[INDEX(x,z+1)])>-8 && (y[INDEX(x,z)]-y[INDEX(x+1,z)])<8 && (y[INDEX(x,z)]-y[INDEX(x+1,z)])>-8) {
					c[INDEX(x,z)].g = gradient + 0.75;
					c[INDEX(x,z)].r = c[INDEX(x,z)].g;
					c[INDEX(x,z)].b = c[INDEX(x,z)].g;
				}
				else {
					c[INDEX(x,z)].r = gradient + 0.75;
					c[INDEX(x,z)].g = c[INDEX(x,z)].r*0.8;
					c[INDEX(x,z)].b = c[INDEX(x,z)].r*0.5;
				}
            }
            else if(y[INDEX(x,z)]>0){
				c[INDEX(x,z)].g = gradient + 0.75;
				c[INDEX(x,z)].r = c[INDEX(x,z)].g * 0.6;
				c[INDEX(x,z)].b = 0.0;
            }
            else {
				c[INDEX(x,z)].r = gradient + 1.0;
				c[INDEX(x,z)].g = c[INDEX(x,z)].r * 0.75;
				c[INDEX(x,z)].b = c[INDEX(x,z)].r * 0.5;
            }
		}
	}

	for(x=0; x<=MAP; x++) {
		for(z=0; z<=MAP; z++) {
			if(y[INDEX(x,z)]<0)
				y[INDEX(x,z)] /= 4.0;
		}
	}

}

//-------------------------------------------------------------------
//  GetHeight()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
float CTerrain::GetHeight(float positionx, float positiony) 
{
	float x0, x1, lx, lz, x, z, midpoint;
	int fx, fz;

	x = positionx/COMP;
	z = positiony/COMP;
	fx = (int)(x);
	fz = (int)(z);
	lx = x - fx;
	lz = z - fz;

	x0 = y[INDEX(fx,fz)] + (y[INDEX(fx,fz+1)] - y[INDEX(fx,fz)])*lz;
	x1 = y[INDEX(fx+1,fz)] + (y[INDEX(fx+1,fz+1)] - y[INDEX(fx+1,fz)])*lz;
	midpoint = x0 + (x1 - x0)*lx;

	return midpoint;
}

//-------------------------------------------------------------------
//  Render()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void CTerrain::Render(float lookx, float lookz, float xpos, float zpos)
{
	// Change the real world coordinates to 256x256 map coordinates.
	position_x = xpos/COMP;
	position_z = zpos/COMP;

	// The following does some clipping to make sure we aren't drawing more than we should.
	if(lookx>-0.707 && lookx<0.707 && lookz<0) {
		min_x = 16;
		min_z = 16;
		max_x = 16;
		max_z = 2;
	}
	else if(lookx<0 && lookz<0.707 && lookz>-0.707) {
		min_x = 16;
		min_z = 16;
		max_x = 2;
		max_z = 16;
	}
	else if(lookx>0 && lookz<0.707 && lookz>-0.707) {
		min_x = 2;
		min_z = 16;
		max_x = 16;
		max_z = 16;
	}
	else {
		min_x = 16;
		min_z = 2;
		max_x = 16;
		max_z = 16;
	}
	
	int x, z;
	float x1, x2, z1, z2;
	for(x=position_x-min_x; x<position_x+max_x; x++) {
		for(z=position_z-min_z; z<position_z+max_z; z++) {

			// Change from map coordinates to real world coordinates.
			x1 = x*COMP;
			x2 = x*COMP + COMP;
			z1 = z*COMP;
			z2 = z*COMP + COMP;

			glBegin(GL_TRIANGLES);
			glColor3f(c[INDEX(x,z)].r, c[INDEX(x,z)].g, c[INDEX(x,z)].b);
			glVertex3f(x1, y[INDEX(x,z)], z1);
			glColor3f(c[INDEX(x+1,z)].r, c[INDEX(x+1,z)].g, c[INDEX(x+1,z)].b);
			glVertex3f(x2, y[INDEX(x+1,z)], z1);
			glColor3f(c[INDEX(x,z+1)].r, c[INDEX(x,z+1)].g, c[INDEX(x,z+1)].b);
			glVertex3f(x1, y[INDEX(x,z+1)], z2);

			glColor3f(c[INDEX(x+1,z+1)].r, c[INDEX(x+1,z+1)].g, c[INDEX(x+1,z+1)].b);
			glVertex3f(x2, y[INDEX(x+1,z+1)], z2);
			glColor3f(c[INDEX(x,z+1)].r, c[INDEX(x,z+1)].g, c[INDEX(x,z+1)].b);
			glVertex3f(x1, y[INDEX(x,z+1)], z2);
			glColor3f(c[INDEX(x+1,z)].r, c[INDEX(x+1,z)].g, c[INDEX(x+1,z)].b);
			glVertex3f(x2, y[INDEX(x+1,z)], z1);	
			glEnd();
		}
	} 
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------
