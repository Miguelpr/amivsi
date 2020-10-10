//---------------------------------------------------------------------------

#ifndef TBaseMILH
#define TBaseMILH
//---------------------------------------------------------------------------

#include <mil.h>

/********************* TBaseMIL ********************/
/* Clase base para inicializar los recursos de las MIL
 * Las variables miembro son static para que las clases que
 * deriven de ella tengan acceso inmediato a estos recursos
 */
class TBaseMIL
{
  public:
        TBaseMIL();
        ~TBaseMIL();
        inline bool IsOK()const {return YaInicializado;}
  protected:
        static MIL_ID AplicacionMIL;
        static MIL_ID SistemaMIL;
        static MIL_ID Pantalla;
        static MIL_ID DigitalizadorMIL;
        static bool YaInicializado; //flag para inicializar solo una vez
        static long num_hijos; //numero de objetos invocados, controla fin
};
#endif
