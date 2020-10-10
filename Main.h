//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <sysutils.hpp>
#include <windows.hpp>
#include <messages.hpp>
#include <sysutils.hpp>
#include <classes.hpp>
#include <graphics.hpp>
#include <controls.hpp>
#include <forms.hpp>
#include <dialogs.hpp>
#include <stdctrls.hpp>
#include <buttons.hpp>
#include <extctrls.hpp>
#include <menus.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
#include <jpeg.hpp>
#include "Secuenciador.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
        TImage *Image1;
        TImage *Image2;
        TMemo *Consola;
        TImage *Image3;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label3;
        TStringGrid *TablaObjetos;
        TLabel *Label4;
        TImage *ImgDepth;
        TGroupBox *GroupBox2;
        //void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:        // private user declarations
public:         // public user declarations
	virtual __fastcall TMainForm(TComponent* Owner);
        Secuenciador *miSecuenciador;
        bool reproduciendo;
        
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
