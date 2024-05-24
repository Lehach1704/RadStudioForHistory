//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include "sqlite3.h"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
typedef struct
 {
	 ULONGLONG Id;
	 UnicodeString Url;
	 UnicodeString Title;
	 ULONGLONG Last_visit_time;
 } NodeStruct;
 //---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *WayDB;
	TVirtualStringTree *StructureDB;
	TButton *OpenDB;
	TButton *DelRecDB;
	TButton *ClearDB;
	TLabel *InfoLabel;
	TOpenDialog *OpenDBDialog;
	void __fastcall OpenDBClick(TObject *Sender);
	void __fastcall StructureDBAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall StructureDBGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall ClearDBClick(TObject *Sender);
	void __fastcall DelRecDBClick(TObject *Sender);


private:
	sqlite3 *Database;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	NodeStruct *ÑNodeData;
    PVirtualNode CNode;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
#endif
