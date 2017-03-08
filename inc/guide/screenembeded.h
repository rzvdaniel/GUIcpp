#ifndef T_SCREENEMBEDED_H
#define T_SCREENEMBEDED_H
//-------------------------------------------------------------------
/**
	@class TScreenEmbeded
	@brief Based on <code>TScreen</code>, this class is the common way
	to run the gui into an already existing 2D or 3D application.
	
	Opposed from <code>TScreenIndependent</code>, this class needs
	an already initialized rendering context. For example, it will not 
	clear usually buffers nor it will open or quit the application

	For a description of its methods see the base class TScreen.
	@see <code>TScreen</code>
	@see <code>TScreenIndependent</code>

	@author Razvan Predescu (2003)
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScreenEmbeded
#include "guide/ndefdllclass.h"

#ifndef T_SCREEN_H
#include "guide/screen.h"
#endif

//-------------------------------------------------------------------

class N_PUBLIC TScreenEmbeded : public TScreen
{
public:
	TScreenEmbeded();
	virtual ~TScreenEmbeded();	
	virtual bool Create(const TRect& Rect, const char* SkinFile);
	virtual void Render(void);
};

//-------------------------------------------------------------------
#endif

