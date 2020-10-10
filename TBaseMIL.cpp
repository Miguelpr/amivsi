//---------------------------------------------------------------------------


#pragma hdrstop

#include "TBaseMIL.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//**************************************************
//************* metodos de la clase TBaseMIL
//**************************************************
MIL_ID TBaseMIL::AplicacionMIL=M_NULL;
MIL_ID TBaseMIL::SistemaMIL=M_NULL;
MIL_ID TBaseMIL::Pantalla=M_NULL;
MIL_ID TBaseMIL::DigitalizadorMIL=M_NULL;
bool TBaseMIL::YaInicializado=false;
long TBaseMIL::num_hijos=0;

//***************************************************
//*********** CONSTRUCTOR ***************************
TBaseMIL::TBaseMIL()
{
 num_hijos++;
 if(YaInicializado==false) //inicializar
 {
  MappAlloc(M_DEFAULT,&AplicacionMIL);

  MsysAlloc(M_SYSTEM_VGA,M_DEV0,M_COMPLETE,&SistemaMIL);
  if(SistemaMIL==M_NULL)
        {
         MappFree(AplicacionMIL);

        }

  MdispAlloc(SistemaMIL,M_DEV0,M_DISPLAY_SETUP,M_DEFAULT,&Pantalla);
  if(Pantalla==M_NULL)
      { MdigFree(DigitalizadorMIL); MsysFree(SistemaMIL); MappFree(AplicacionMIL);

      }
  MdispControl(Pantalla, M_WINDOW_INITIAL_POSITION_X, 110);
  MdispControl(Pantalla, M_WINDOW_INITIAL_POSITION_Y, 10);
  MdispControl(Pantalla, M_WINDOW_MENU_BAR, M_DISABLE);
  MdispControl(Pantalla, M_WINDOW_MOVE, M_DISABLE);
  MdispControl(Pantalla, M_WINDOW_TITLE_BAR, M_DISABLE);
  YaInicializado=true;
 }

}

//***************************************************
//*********** DESTRUCTOR ***************************
TBaseMIL::~TBaseMIL()
{
num_hijos--;
if(num_hijos==0)
  {
   MdispFree(Pantalla); Pantalla=M_NULL;

   MsysFree(SistemaMIL); SistemaMIL=M_NULL;
   MappFree(AplicacionMIL); AplicacionMIL=M_NULL;
   YaInicializado=false;

  }

}

