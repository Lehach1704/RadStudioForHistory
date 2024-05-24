//---------------------------------------------------------------------------
#include <iostream>
#include <vcl.h>

using namespace std;

#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
		StructureDB->NodeDataSize = sizeof(NodeStruct);
}
//---------------------------------------------------------------------------
void FillStringTree(TVirtualStringTree *stringTree, sqlite3 *Database)
{
	stringTree->BeginUpdate();

	stringTree->Clear(); // очистка таблицы

	sqlite3_stmt *pStatement;
	int execResult = sqlite3_prepare_v2(Database,
										"SELECT urls.id, urls.url, urls.title, urls.last_visit_time FROM urls",
										-1,&pStatement,NULL); //запрос БД

	while(true)  // Реализация считывания строк из БД в VirtualStringTree
	{

		int stepResult = sqlite3_step(pStatement);
		if (stepResult != SQLITE_ROW)
		{
			break;
		}

		PVirtualNode entryNode = stringTree->AddChild(stringTree->RootNode);

		NodeStruct *nodeData = (NodeStruct*)stringTree->GetNodeData(entryNode);

		nodeData->Id = sqlite3_column_int(pStatement, 0);
		nodeData->Url = L"URL: " + UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 1));
		nodeData->Title =L"Title: " +UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 2));
		nodeData->Last_visit_time = sqlite3_column_int(pStatement, 3);
	}
	sqlite3_finalize(pStatement);

	stringTree->EndUpdate();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenDBClick(TObject *Sender)
{
	wstring fileName;

	if (OpenDBDialog->Execute()) // открытие БД
	{
		fileName = OpenDBDialog->FileName.c_str();
		sqlite3_open16(fileName.c_str(), &Database);
		WayDB->Text = fileName.c_str();      // вывод пути расположения файла
	}

	FillStringTree(StructureDB, Database);  // переход к функции заполнения VirtualStringTree
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StructureDBAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node)
{
	// вывод дополнительной информации
	if(!Node) return;
	СNodeData = (NodeStruct*)Sender->GetNodeData(Node);
	InfoLabel->Caption = СNodeData->Title + "\nПоследнее посещение: " + СNodeData->Last_visit_time;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StructureDBGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	// функция для вывода основной информации
	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column)
	{
		case 0: CellText = nodeData->Id; break;
		case 1: CellText = nodeData->Url; break;
	}
}
//---------------------------------------------------------------------------
void clearDB(sqlite3 *Database, TVirtualStringTree *stringTree)
{
	stringTree->BeginUpdate();
	stringTree->Clear();
	stringTree->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearDBClick(TObject *Sender)
{
	clearDB(Database, StructureDB);
}
//---------------------------------------------------------------------------
void deleteRec(sqlite3 *Database, NodeStruct *NodeData)
{
	sqlite3_stmt *fordel; //создание указателя на запрос

	string reqest = "DELETE FROM urls WHERE (id = " +to_string(NodeData->Id) +");";
	sqlite3_prepare_v2(Database,reqest.c_str(),-1,&fordel,NULL);
	sqlite3_step(fordel);  // выполнение запроса
	sqlite3_finalize(fordel); // удаление указателя на запрос

}
//---------------------------------------------------------------------------
void __fastcall TForm1::DelRecDBClick(TObject *Sender)
{
	StructureDB->DeleteNode(CNode); // удаление узла
	deleteRec(Database, СNodeData); // функция для удаления из БД
}
//---------------------------------------------------------------------------

