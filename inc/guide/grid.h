#ifndef T_GRID_H
#define T_GRID_H
//-------------------------------------------------------------------
/**
	@class TGrid
	@brief This class allows us to create backgrounds for every
	single control that gui is containing.

	The most powerful feature of the class is that skin creators
	will not be constrained when designing the look of their
	controls, because of the smart way a grid is created. A control
	could contains multiple grids to reflect their different states.
	For example, a button could be pressed, highlighted, disabled etc.
	A grid is made by rows, and every row is created from columns.

	@see <code>TGridRow</code>
	@see <code>TGridColumn</code>
	@author Razvan Predescu (2004)
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TGrid
#include "guide/ndefdllclass.h"

#ifndef T_GRIDROW_H
#include "guide/gridrow.h"
#endif

typedef stl::list<TGridRow*> TGridRowsList;

//-------------------------------------------------------------------
class N_PUBLIC TGrid : public TObject
{
	int Width;
	int Height;
	TString Name;
	TGridRowsList Rows;

public:
	TGrid();
	virtual ~TGrid();
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	void SetName(const char* AName);
	TString GetName(void) const { return Name; }

	void SetWidth(int Value);
	int GetWidth(void) const { return Width; }
	void SetHeight(int Value);
	int GetHeight(void) const { return Height; }

	/// Get a row from Index position 
	TGridRow* GetRow(int Index);
	/// Get rows list
	TGridRowsList* GetRows(void) { return &Rows; }
	/// Insert a row at specified position
	void InsertRow(int Index, TGridRow* Item);
	/// Append a row
	void AppendRow(TGridRow* Item);
	/// Remove a row by reference
	void RemoveRow(TGridRow* Item);
	/// Remove a row by index
	void RemoveRow(int Index);
	/// Returns the row's index
	int	IndexOf(TGridRow* Item);
	/// Returns the number of rows
	int	Count(void) const;
	/// Remove all the rows
	void Clear(void);

	/// Paint the grid
	void Paint(TCanvas* Canvas);
	/// Realign the rows
	void RealignRows(void);

private:
	TGridRow* GetLastAlignedRow(TAlignRow Value);
};

//-------------------------------------------------------------------
#endif
