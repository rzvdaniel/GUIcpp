#ifndef T_GRIDROW_H
#define T_GRIDROW_H
//-------------------------------------------------------------------
/**
	@class TGridRow

    @brief Rows are cell containers that can be aligned within grids. 
	
	Rows are useful when renderig control's grids. As part of the
	skining component, rows plays an important role in the way a control
	looks. They always have the width of their parent grid, but their height 
	is variable, depending by <b>TAlignRow</b> property. When a 
	grid is resizing in height, the child rows will be aligned at the 
	top, bottom or client area of the grid.

    @remarks Only the client aligned rows can be resized in height,
	the top and bottom aligned will keep their height fixed.

	(C) 2004 R.Predescu
*/
#undef N_DEFINES
#define N_DEFINES TGridRow
#include "guide/ndefdllclass.h"

#ifndef T_GRIDCELL_H
#include "guide/gridcell.h"
#endif

#include <list>

typedef stl::list<TGridCell*> TGridCellsList;

enum TAlignRow { ralNone, ralTop, ralBottom, ralClient };

//-------------------------------------------------------------------
class TGrid;
class N_PUBLIC TGridRow : public TObject
{	
	/// The bounds of the row
	TRect Rect;
	/// Parent grid
	TGrid* Grid;	
	/// Alignment of the row within the parent grid
	TAlignRow Align;
	/// List of the cells this row contains
	TGridCellsList Cells;

public:
	TGridRow(TGrid* AGrid);
	virtual ~TGridRow();
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	TGrid* GetGrid(void) const { return Grid; }
   
	/// Get the cell with the specified index
	TGridCell* GetCell(int Index);
    /// Get the cells list
	TGridCellsList* GetCells(void) { return &Cells; }
	
	/// Set the alignment of this cell within its parent grid
	void SetAlign(TAlignRow Value);
	/// Get the alignment of this cell within its parent grid
	TAlignRow GetAlign(void) const { return Align; }

	TRect GetRect(void) const { return Rect; }
	void SetLeft(int Value);
	int GetLeft(void) const { return Rect.left; }
	void SetTop(int Value);
	int GetTop(void) const { return Rect.top; }
	void SetWidth(int Value);
	int GetWidth(void) const { return Rect.right; }
	void SetHeight(int Value);
	int GetHeight(void) const { return Rect.bottom; }

	/// Insert a cell at specified position
	void InsertCell(int Index, TGridCell* Item);
	/// Append a cell
	void AppendCell(TGridCell* Item);
	/// Remove a cell by reference
	void RemoveCell(TGridCell* Item);
	/// Remove a cell by index
	void RemoveCell(int Index);
	/// Returns the cell's index
	int IndexOf(TGridCell* Item);
	/// Returns the number of cells
	int Count(void) const;
	/// Remove all the cells
	void Clear(void);	
	
	void Paint(TCanvas* Canvas);
	void RealignCells(void);

private:
	TGridCell* GetLastAlignedCell(TAlignCell Value);
};



//-------------------------------------------------------------------
#endif
