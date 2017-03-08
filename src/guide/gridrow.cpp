#define N_IMPLEMENTS TGridRow
//-------------------------------------------------------------------
//  gridrow.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/grid.h"
#include "guide/gridrow.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/tga.h"
#include "guide/canvas.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TGridRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGridRow::TGridRow(TGrid* AGrid) 
{
	Grid = AGrid;
	Align = ralNone;
	Rect.left = 0;
}

//-------------------------------------------------------------------
//  ~TGridRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGridRow::~TGridRow()
{
	Clear();
}

//-------------------------------------------------------------------
//  SetLeft()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::SetLeft(int Value)
{
	if(Rect.left != Value)
		Rect.left = Value;
}

//-------------------------------------------------------------------
//  SetTop()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::SetTop(int Value)
{
	if(Rect.top != Value)
		Rect.top = Value;
}

//-------------------------------------------------------------------
//  SetHeight()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::SetHeight(int Value)
{
	if(Rect.bottom != Value)
	{
		Rect.bottom = Value;
		
		// Adjust the height of all the cells
		TGridCellsList::iterator iter;
		for(iter = Cells.begin(); iter != Cells.end(); iter++)
		{
			TGridCell* Cell = (TGridCell*)(*iter);
			Cell->SetHeight(Value);
		}
	}
}

//-------------------------------------------------------------------
//  SetWidth()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::SetWidth(int Value)
{
	if(Rect.right != Value)
	{
		Rect.right = Value;
		RealignCells();	
	}
}

//-------------------------------------------------------------------
//  SetAlign()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::SetAlign(TAlignRow Value)
{
	if(Value != Align)
	{
		Align = Value;
		Grid->RealignRows();
	}
}

//-------------------------------------------------------------------
//  RealignCells()
//  19-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::RealignCells(void)
{	
	int LeftOffset = 0;
	int RightOffset = this->Rect.right;

	TGridCellsList::iterator iter;
	for(iter = Cells.begin(); iter != Cells.end(); iter++)
	{
		TGridCell* Cell = (TGridCell*)(*iter);
		if(Cell->GetAlign() == calLeft)
		{
		    Cell->SetLeft(LeftOffset);
		    LeftOffset += Cell->GetWidth();
        }
        else if(Cell->GetAlign() == calRight)
		{
		    Cell->SetLeft(RightOffset - Cell->GetWidth());
		    RightOffset -= Cell->GetWidth();
        }
	}
	
	// Align client cells
	TGridCell* LeftCell = GetLastAlignedCell(calLeft);
	TGridCell* RightCell = GetLastAlignedCell(calRight);
	for(iter = Cells.begin(); iter != Cells.end(); iter++)
	{
		TGridCell* Cell = (TGridCell*)(*iter);
		
		if(Cell->GetAlign() == calClient)
		{
		    if(LeftCell != NULL)
		        Cell->SetLeft(LeftCell->GetLeft() + LeftCell->GetWidth());
			else
			    Cell->SetLeft(0);

            if(RightCell != NULL)
			    Cell->SetWidth(RightCell->GetLeft() - Cell->GetLeft());	
		    else
			    Cell->SetWidth(this->Rect.right - Cell->GetLeft());	
        }
	}
}

//-------------------------------------------------------------------
//  GetLastAlignedCell()
//  19-Aug-2004   rzv   created
//-------------------------------------------------------------------
TGridCell* TGridRow::GetLastAlignedCell(TAlignCell Value)
{
	TGridCell* LastAlignedCell = NULL;
    
	TGridCellsList::iterator iter;
	for(iter = Cells.begin(); iter != Cells.end(); iter++)
	{
		TGridCell* Cell = (TGridCell*)(*iter);
		
		if(Cell->GetAlign() == Value)
            LastAlignedCell = Cell;
	}	

	return LastAlignedCell;
}

//-------------------------------------------------------------------
/**
	@param Index Index of the cell that will be returned.
	@return A pointer to a grid cell or NULL if no cell was 
	found. 

	12-May-2004   rzv   created
*/
//-------------------------------------------------------------------
TGridCell* TGridRow::GetCell(int Index)
{
	TGridCell* Item = NULL;

	if(Index >= 0 && Index < Count())
	{
		TGridCellsList::iterator Where = Cells.begin();
		for(int i = 0; i < Index; i++) 
			Where++;

		Item = (TGridCell*)(*Where);
	}

	return Item;
}

//-------------------------------------------------------------------
//  InsertCell()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::InsertCell(int Index, TGridCell* Item)
{
	if(Item != NULL)
	{
		TGridCellsList::iterator Where = Cells.begin();
		for(int i = 0; i < Index; i++) 
			Where++;

		if(Index < 0)
			Cells.push_front(Item);	
		else if(Index >= Count())
			Cells.push_back(Item);
		else
			Cells.insert(Where, Item);
	}
}

//-------------------------------------------------------------------
//  AppendCell()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::AppendCell(TGridCell* Item)
{
	if(Item != NULL)
		Cells.push_back(Item);
}

//-------------------------------------------------------------------
//  RemoveCell()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::RemoveCell(TGridCell* Item)
{
	if(Item != NULL) 
	{			
		Cells.remove(Item);
		delete Item;
	}
}


//-------------------------------------------------------------------
//  RemoveCell()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::RemoveCell(int Index)
{
	if(Index >= 0 && Index < Count())
	{
		TGridCellsList::iterator Where = Cells.begin();
		for(int i = 0; i < Index; i++) 
			Where++;
			
		TGridCell* Cell = (TGridCell*)(*Where);
		Cells.erase(Where);
		delete Cell;
	}
}

//-------------------------------------------------------------------
//  IndexOf()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
int	TGridRow::IndexOf(TGridCell* Item)
{
	if(Item != NULL && Count() != 0)
	{
		int i;
		TGridCellsList::iterator iter;
		for(i = 0,iter = Cells.begin(); iter != Cells.end(); iter++,i++)
		{
			TGridCell* Cell = (TGridCell*)(*iter);
			
			// FIXME! This is not a good way to verify the equality!
			if(Cell == Item)
				return i;
		}
	}

	return -1;
}

//-------------------------------------------------------------------
//  Count()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
int	TGridRow::Count(void) const
{
	return Cells.size();
}

//-------------------------------------------------------------------
//  Clear()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::Clear(void)
{
	TGridCell* Item = NULL;
	while(Count()) 
	{
		Item = Cells.back(); 	
		RemoveCell(Item);
	} 
}

//-------------------------------------------------------------------
//  Paint()
//  17-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::Paint(TCanvas* Canvas) 
{
	TGridCellsList::iterator iter;
	for(iter = Cells.begin(); iter != Cells.end(); iter++)
	{		
		TGridCell* Cell = (TGridCell*)(*iter);
		Cell->Paint(Canvas);
	}
	
	// Debug only
	//Canvas->Pen->SetColor(clRed);
	//Canvas->DrawRect(GetLeft(), GetTop(), GetWidth(), GetHeight(), 1);
}

//-------------------------------------------------------------------
//  Assign()
//  20-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::Assign(TObject* Object)
{
	TGridRow* Row = (TGridRow*)Object;
	Rect = Row->GetRect();
    Align = Row->GetAlign();
    	
	TGridCellsList::iterator iter;
	for(iter = Row->GetCells()->begin(); iter != Row->GetCells()->end(); iter++)
	{		
		TGridCell* Cell = (TGridCell*)(*iter);

		TGridCell* NewCell = new TGridCell(this);
		NewCell->Assign(Cell);
		Cells.push_back(NewCell);
	}	
}

//-------------------------------------------------------------------
void TGridRow::ApplySkin(TObject* Object)
{
	TGridRow* Row = (TGridRow*)Object;
	Rect = Row->GetRect();
	Align = Row->GetAlign();

	TGridCellsList::iterator iter;
	for(iter = Row->GetCells()->begin(); iter != Row->GetCells()->end(); iter++)
	{		
		TGridCell* Cell = (TGridCell*)(*iter);

		TGridCell* NewCell = new TGridCell(this);
		NewCell->ApplySkin(Cell);
		Cells.push_back(NewCell);
	}	
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TGridRow::ParseSkin(TiXmlElement* XmlElement)
{
	TiXmlElement* Element;
	const char *value = NULL;
	
	// Read the Height attribute, before the Align attribute.
	// When setting the alignment of the row, we should know its height
	value = XmlElement->Attribute("Height");
	if(value != NULL)
	{
		sscanf(value, "%d", &Rect.bottom);
		value = NULL;
	}

	// Read the Align attribute
	value = XmlElement->Attribute("Align");
	if(value != NULL)
	{
		if(!strcmp(value, "top"))
			Align = ralTop;
		else if(!strcmp(value, "bottom"))
			Align = ralBottom;
		else if(!strcmp(value, "client"))
			Align = ralClient;

		value = NULL;
	}

	int LeftCellOffset = 0;

	// Read cells
	for(Element = XmlElement->FirstChildElement("TCell");
		Element;
		Element = Element->NextSiblingElement("TCell"))
	{
		// Create, parse, append and adjust bounds for the new cell
		TGridCell* Cell = new TGridCell(this);
		Cell->ParseSkin(Element);
		AppendCell(Cell);

		Cell->SetBounds(LeftCellOffset, 0, Cell->GetWidth(), GetHeight());
		LeftCellOffset += Cell->GetWidth();
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

