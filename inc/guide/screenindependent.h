#ifndef T_SCREENINDEPENDENT_H
#define T_SCREENINDEPENDENT_H
//-------------------------------------------------------------------
/**
	@class TScreenIndependent
	@brief Derived from <code>TScreen</code>, this class implements an 
	independent way to run the gui. 
	
	It is responsible to open and close the display (rendering context) 
	so the gui will be able to run stand alone, opposed from 
	<code>TScreenEmbeded</code> which is capable to run the only inside 
	already prepared rendering contexts.
	
	For a description of its methods see the base class TScreen.
	@see <code>TScreen</code>
	@see <code>TScreenEmbeded</code>

	@author Razvan Predescu
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScreenIndependent
#include "guide/ndefdllclass.h"

#ifndef T_SCREEN_H
#include "guide/screen.h"
#endif

//-------------------------------------------------------------------

class N_PUBLIC TScreenIndependent : public TScreen
{
public:
	TScreenIndependent();
	virtual ~TScreenIndependent();	
	bool Create(const TRect& Rect, int Bpp, bool Full, const char* SkinFile);
	virtual void Close(void);
	virtual void Run(void);
	virtual void Render(void);
	virtual void Idle(void);

protected:
	virtual bool OpenDisplay(bool IsFullscreen);
	virtual void CloseDisplay(void);
};

//-------------------------------------------------------------------
#endif

