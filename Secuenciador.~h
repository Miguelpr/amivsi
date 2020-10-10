//---------------------------------------------------------------------------

#ifndef SecuenciadorH
#define SecuenciadorH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Secuenciador : public TThread
{            
private:
protected:
        void __fastcall Execute();
public:
        __fastcall Secuenciador(bool CreateSuspended);
        TImage *Image1;
        TImage *ImgDepth;
        TImage *BitmapDireccion;
        TImage *BitmapVelocimetro;
        TLabel *VelocimetroDigital;
        TMemo *Consola;
        TStringGrid *TObjetos;
        bool pintarDepth;
        bool pintarOpfl;
};
//---------------------------------------------------------------------------
#endif
