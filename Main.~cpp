//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "Main.h"
#include "Secuenciador.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{

 TablaObjetos->Cells[0][0] = "Etiqueta";
 TablaObjetos->Cells[1][0] = "Pos. Actual";
 TablaObjetos->Cells[2][0] = "Pos. Futura";
 TablaObjetos->Cells[3][0] = "Id. Imagen";


 TablaObjetos->ColWidths[0] = 70;
 TablaObjetos->ColWidths[1] = 128;
 TablaObjetos->ColWidths[2] = 128;
 TablaObjetos->ColWidths[3] = 80;




reproduciendo=true;
miSecuenciador= new Secuenciador(false);
miSecuenciador->BitmapVelocimetro=Image2;
miSecuenciador->Image1=Image1;
miSecuenciador->Consola = Consola;
miSecuenciador->BitmapDireccion = Image3;

miSecuenciador->VelocimetroDigital = Label3;
miSecuenciador->TObjetos = TablaObjetos;
miSecuenciador->ImgDepth = ImgDepth;


}
//----------------------------------------------------------------------------

/*
void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
if (Key==' '){
;
if (reproduciendo){
        this->miSecuenciador->Suspend();
        reproduciendo = false;
}else{
        this->miSecuenciador->Resume();
        reproduciendo = true;

}
}
if (Key=='o'){
  if(miSecuenciador->pintarOpfl) {
                miSecuenciador->pintarOpfl = false;
        }else{
                miSecuenciador->pintarOpfl = true;
        }
 }

if (Key=='p'){
   if(miSecuenciador->pintarDepth) {
                miSecuenciador->pintarDepth = false;
        }else{
                miSecuenciador->pintarDepth = true;
        }
        }
}
//---------------------------------------------------------------------------
*/




