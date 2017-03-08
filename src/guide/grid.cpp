#define N_IMPLEMENTS TGrid
//-------------------------------------------------------------------
//  grid.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/grid.h"
#include "guide/canvas.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TGrid()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGrid::TGrid() 
{
	Width = 0;
	Height = 0;
}

//-------------------------------------------------------------------
//  ~TGrid()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGrid::~TGrid()
{	
	Clear();
}

//-------------------------------------------------------------------
//  SetName()
//  23-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::SetName(const char* AName)
{
	Name.assign(AName);
}

//-------------------------------------------------------------------
//  SetWidth()
//  18-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::SetWidth(int Value)
{
	if(Width != Value)
	{
		Width = Value;

		TGridRowsList::iterator iter;
		for(iter = Rows.begin(); iter != Rows.end(); iter++)
		{
			TGridRow* Row = (TGridRow*)(*iter);
			Row->SetWidth(Value);
		}	
	}
}

//-------------------------------------------------------------------
//  SetHeight()
//  18-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::SetHeight(int Value)
{
	if(Height != Value)
	{
		Height = Value;
		RealignRows();
	}
}

//-------------------------------------------------------------------
//  RealignRows()
//  19-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::RealignRows(void)
{	
	int TopOffset = 0;
	int BottomOffset = GetHeight();
		
	// Aligntop and bottom rows
	TGridRowsList::iterator iter;
	for(iter = Rows.begin(); iter != Rows.end(); iter++)
	{
		TGridRow* Row = (TGridRow*)(*iter);
		if(Row->GetAlign() == ralTop)
		{
		    Row->SetTop(TopOffset);
            TopOffset += Row->GetHeight();   
        }
        else if(Row->GetAlign() == ralBottom)
		{
		    Row->SetTop(BottomOffset - Row->GetHeight());
		    BottomOffset -= Row->GetHeight();
        }
        
	}
	
	// Align client rows
	TGridRow* TopRow = GetLastAlignedRow(ralTop);
	TGridRow* BottomRow = GetLastAlignedRow(ralBottom);
	for(iter = Rows.begin(); iter != Rows.end(); iter++)
	{
		TGridRow* Row = (TGridRow*)(*iter);
		
		if(Row->GetAlign() == ralClient)
		{
		    if(TopRow != NULL)
		        Row->SetTop(TopRow->GetTop() + TopRow->GetHeight());
			else
			    Row->SetTop(0);

            if(BottomRow != NULL)
			    Row->SetHeight(BottomRow->GetTop() - Row->GetTop());
		    else
			    Row->SetHeight(this->Height - Row->GetTop());
       
        } 
	}	
}

//-------------------------------------------------------------------
//  GetLastAlignedRow()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
TGridRow* TGrid::GetLastAlignedRow(TAlignRow Value)
{
    TGridRow* LastAlignedRow = NULL;
    
	TGridRowsList::iterator iter;
	for(iter = Rows.begin(); iter != Rows.end(); iter++)
	{
		TGridRow* Row = (TGridRow*)(*iter);
		
		if(Row->GetAlign() == Value)
            LastAlignedRow = Row;
	}	

	return LastAlignedRow;
}

//-------------------------------------------------------------------
//  GetRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGridRow* TGrid::GetRow(int Index)
{
	TGridRow* Item = NULL;

	if(Index >= 0 && Index < Count())
	{
		TGridRowsList::iterator Where = Rows.begin();
		for(int i = 0; i < Index; i++) 
			Where++;

		Item = (TGridRow*)(*Where);
	}

	return Item;
}

//-------------------------------------------------------------------
//  InsertRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::InsertRow(int Index, TGridRow* Item)
{
	if(Item != NULL)
	{
		TGridRowsList::iterator Where = Rows.begin();
		for(int i = 0; i < Index; i++) 
			Where++;

		if(Index < 0)
			Rows.push_front(Item);	
		else if(Index >= Count())
			Rows.push_back(Item);
		else
			Rows.insert(Where, Item);
	}
}

//-------------------------------------------------------------------
//  AppendRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::AppendRow(TGridRow* Item)
{
	if(Item != NULL)
		Rows.push_back(Item);
}

//-------------------------------------------------------------------
//  RemoveRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::RemoveRow(TGridRow* Item)
{
	if(Item != NULL) 
	{			
		Rows.remove(Item);
		delete Item;
	}
}


//-------------------------------------------------------------------
//  RemoveRow()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::RemoveRow(int Index)
{
	if(Index >= 0 && Index < Count())
	{
		TGridRowsList::iterator Where = Rows.begin();
		for(int i = 0; i < Index; i++) 
			Where++;
			
		TGridRow* Row = (TGridRow*)(*Where);
		Rows.erase(Where);
		delete Row;
	}
}


//-------------------------------------------------------------------
//  IndexOf()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
int	TGrid::IndexOf(TGridRow* Item)
{
	if(Item != NULL && Count() != 0)
	{
		int i;
		TGridRowsList::iterator iter;
		for(i = 0,iter = Rows.begin(); iter != Rows.end(); iter++,i++)
		{
			TGridRow* Row = (TGridRow*)(*iter);
			
			// This is not a good way to verify the equality!
			if(Row == Item)
				return i;
		}
	}

	return -1;
}

//-------------------------------------------------------------------
//  Count()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
int	TGrid::Count(void) const
{
	return Rows.size();
}

//-------------------------------------------------------------------
//  Clear()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::Clear(void)
{
	TGridRow* Item = NULL;
	while(Count()) 
	{
		Item = Rows.back(); 	
		RemoveRow(Item);
	} 
}

//-------------------------------------------------------------------
//  Paint()
//  17-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::Paint(TCanvas* Canvas) 
{   
	TGridRowsList::iterator iter;
	for(iter = Rows.begin(); iter != Rows.end(); iter++)
	{		
		TGridRow* Row = (TGridRow*)(*iter);
		Row->Paint(Canvas);
	}
}

//-------------------------------------------------------------------
//  Assign()
//  20-May-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::Assign(TObject* Object)
{
	TGrid* Grid = (TGrid*)Object;

	TGridRowsList::iterator iter;
	for(iter = Grid->GetRows()->begin(); iter != Grid->GetRows()->end(); iter++)
	{		
		TGridRow* Row = (TGridRow*)(*iter);
		TGridRow* NewRow = new TGridRow(this);
		NewRow->Assign(Row);
		Rows.push_back(NewRow);
	}	
	
	SetWidth(Grid->GetWidth());
	SetHeight(Grid->GetHeight());
	SetName(Grid->GetName().c_str());
}

//-------------------------------------------------------------------
void TGrid::ApplySkin(TObject* Object)
{
	TGrid* Grid = (TGrid*)Object;

	TGridRowsList::iterator iter;
	for(iter = Grid->GetRows()->begin(); iter != Grid->GetRows()->end(); iter++)
	{		
		TGridRow* Row = (TGridRow*)(*iter);
		TGridRow* NewRow = new TGridRow(this);
		NewRow->ApplySkin(Row);
		Rows.push_back(NewRow);
	}	

	SetWidth(Grid->GetWidth());
	SetHeight(Grid->GetHeight());
	SetName(Grid->GetName().c_str());
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TGrid::ParseSkin(TiXmlElement* XmlElement)
{
	TiXmlElement* Element;
	const char *value = NULL;

	// Read the Name attribute
	value = XmlElement->Attribute("Name");
	if(value != NULL)
	{
		Name.assign(value);
	}

	// Read rows
	for(Element = XmlElement->FirstChildElement();
		Element;
		Element = Element->NextSiblingElement())
	{
		// Create, parse and append a new row
		TGridRow* Row = new TGridRow(this);
		Row->ParseSkin(Element);
		AppendRow(Row);
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

