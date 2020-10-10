//---------------------------------------------------------------------------

#ifndef TImagenH
#define TImagenH
#include <mil.h>
#include "TBaseMIL.h"
#include <ExtCtrls.hpp>
class TImagen:TBaseMIL
{
  public:
        MIL_ID ImagenID;
        int _HDim; //dimension horizontal en pixels
        int _VDim; //dimension vertical en pixels
        byte _NBands; //num bandas color, 1 o 3
        TImagen();
        void convertir(MIL_ID img);
        void Cargar(AnsiString PathFileName);
        ~TImagen();
        void Sobel();
        void Copiar(MIL_ID img);
        Graphics::TBitmap * GetBitmap();
        byte ** TImagen2RawBN();
  protected:
        Graphics::TBitmap * _Raw2GreyBitmap(byte *pixels, int ancho, int alto);
        Graphics::TBitmap * _Raw2ColorBitmap(byte *pixelsR,byte *pixelsG,byte *pixelsB,int ancho,int alto);

       

};
//---------------------------------------------------------------------------

#endif
