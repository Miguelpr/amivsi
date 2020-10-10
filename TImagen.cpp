//---------------------------------------------------------------------------


#pragma hdrstop

#include "TImagen.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//Graphics::TBitmap *bitmap;
//***************************************************
//*********** CONSTRUCTOR ***************************
TImagen::TImagen():TBaseMIL()
{
 ImagenID=M_NULL;
}
void TImagen::Cargar(AnsiString PathFileName)
{
    if (ImagenID!=M_NULL)
    MbufFree(ImagenID);




    MbufImport(PathFileName.c_str(),M_DEFAULT,M_RESTORE,SistemaMIL,&ImagenID);
    _HDim=MbufInquire(ImagenID,M_SIZE_X,M_NULL);
    _VDim=MbufInquire(ImagenID,M_SIZE_Y,M_NULL);


    _NBands=MbufInquire(ImagenID,M_SIZE_BAND,M_NULL);
    if (_NBands==3)
    convertir(ImagenID);





}

void TImagen::convertir(MIL_ID img){

MbufAlloc2d(SistemaMIL,MbufInquire(img,M_SIZE_X,M_NULL),MbufInquire(img,M_SIZE_Y,M_NULL),8+M_UNSIGNED,M_IMAGE+M_DISP+M_PROC,&ImagenID);
MimConvert(img, ImagenID, M_RGB_TO_L);
MbufFree(img);
_NBands=1;
}
//***************************************************
//*********** DESTRUCTOR ****************************
TImagen::~TImagen()
{

if (ImagenID!=M_NULL)
MbufFree(ImagenID);





}


//***************************************************
//****************** SOBEL *************************
//Realiza una Convolucion Prewit a la TImagen
void TImagen::Sobel()
{

MimConvolve(ImagenID, ImagenID, M_EDGE_DETECT); //SOBEL

}




//***************************************************
//*********** CONSTRUCTOR desde MIL *****************
void TImagen::Copiar(MIL_ID img) //crea TImagen desde MIL, copia contenido
{
 if (ImagenID!=M_NULL)
    MbufFree(ImagenID);

  _HDim=MbufInquire(img,M_SIZE_X,M_NULL);
  _VDim=MbufInquire(img,M_SIZE_Y,M_NULL);
  
  _NBands=1;

   MbufAlloc2d(SistemaMIL,MbufInquire(img,M_SIZE_X,M_NULL),MbufInquire(img,M_SIZE_Y,M_NULL),8+M_UNSIGNED,M_IMAGE+M_DISP+M_PROC,&ImagenID);


   MbufCopy(img,ImagenID);

}
//***************************************************
//****************** GETBITMAP ************************
//Convierte la imagen a un objeto TBitmap
Graphics::TBitmap * TImagen::GetBitmap()
{
 Graphics::TBitmap *bitmap;
 if(_NBands==1) //blanco y negro
 { byte *pixels=new byte[_HDim*_VDim+2];
   MbufGet(ImagenID,(void *)pixels);
   bitmap=_Raw2GreyBitmap(pixels,_HDim,_VDim);
   delete [] pixels;
 }
 else //color
 {
  byte *pixels_R=new byte[_HDim*_VDim+2];
  byte *pixels_G=new byte[_HDim*_VDim+2];
  byte *pixels_B=new byte[_HDim*_VDim+2];
  MbufGetColor(ImagenID,M_SINGLE_BAND,M_RED,(void *)pixels_R);
  MbufGetColor(ImagenID,M_SINGLE_BAND,M_GREEN,(void *)pixels_G);
  MbufGetColor(ImagenID,M_SINGLE_BAND,M_BLUE,(void *)pixels_B);
  bitmap=_Raw2ColorBitmap(pixels_R,pixels_G,pixels_B,_HDim,_VDim);
  delete [] pixels_R;
  delete [] pixels_G;
  delete [] pixels_B;
 }
 return bitmap;
}

//********************************************************
//********************** Raw2GreyBitmap ******************
//Recibe un array con los pixels de la imagen, y su dimensiones
//Devuelve referencia a un objeto TBitmap. Liberar despues.
Graphics::TBitmap * TImagen::_Raw2GreyBitmap(byte *pixels, int ancho, int alto)
{
 int i;
 int aux_int, ancho4;
 Graphics::TBitmap * bitmap = new Graphics::TBitmap();
 TStringStream* array_bmp=new TStringStream("");
//Se crea el bitmap sobre el TStringStream,
//luego se carga sobre el TBitmap
//1.- Crear cabecera (54 bytes)
 array_bmp->Position=0;
 aux_int=19778; //codigo de tipo de bitmap
  array_bmp->Write((void *)&aux_int,2);
 if((ancho%4)==0)ancho4=ancho;
  else ancho4=ancho+4-ancho%4; //ancho es multiplo de 4
   aux_int=54+1024+alto*ancho4;//tamanyo total en bytes
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //debe haber ahora 4 bytes a 0 -reservados-
  array_bmp->Write((void *)&aux_int,4);
 aux_int=54+1024; //offset hasta llegar a valores pixels
  array_bmp->Write((void *)&aux_int,4);
 aux_int=40;  //cabecera bitmap estandar windows
  array_bmp->Write((void *)&aux_int,4);
 aux_int=ancho; //ancho del bitmap
  array_bmp->Write((void *)&aux_int,4);
 aux_int=alto;   //alto del bitmap
  array_bmp->Write((void *)&aux_int,4);
 aux_int=1; //numero de planos
  array_bmp->Write((void *)&aux_int,2);
 aux_int=8; //bits por pixel
  array_bmp->Write((void *)&aux_int,2);
 aux_int=0; //codigo de compresion, 0=sin ella
  array_bmp->Write((void *)&aux_int,4);
 aux_int=alto*ancho4; //tamanyo del bitmap
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //resolucion horizontal,ppi
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //resolucion vertical, ppi
  array_bmp->Write((void *)&aux_int,4);
 aux_int=256; //num colores en paleta
  array_bmp->Write((void *)&aux_int,4);
 aux_int=256; //num colores importantes
  array_bmp->Write((void *)&aux_int,4);
//2.- Crear la paleta de 256 colores, 4 bytes por color
//en grises, cada color tiene la misma cantidad de r,g,b
//un byte por componente mas un 0 para ajuste a lotes de 4 bytes
 for(i=0;i<256;i++)
  {

   aux_int=i*65793; array_bmp->Write((void *)&aux_int,4);
  }
//3.- Copiar el mapa de bits
//en primer lugar va la ultima fila, y asi hasta poner la fila 0 la ultima
//cada una con ceros al final hasta ser multiplo de 4 -ancho4-
 aux_int=0;
 for(i=alto-1; i>=0;i--)
 {
  array_bmp->Write((void *)&(pixels[ancho*i]),ancho); //copiar fila
  array_bmp->Write((void *)&aux_int,ancho4-ancho); //relleno de ceros
 }
//volcar del stream al bitmap
 array_bmp->Position=0;
 bitmap->LoadFromStream(array_bmp);

 delete array_bmp;
 return bitmap;
}


//********************** Raw2ColorBitmap ******************
//Recibe tres arrays con los pixels de la imagen, y su dimensiones
//Devuelve referencia a un objeto TBitmap. Liberar despues.
Graphics::TBitmap * TImagen::_Raw2ColorBitmap(byte *pixelsR, byte *pixelsG, byte *pixelsB,int ancho, int alto)
{
 int i,j,aux_int,ancho4;
 Graphics::TBitmap * bitmap = new Graphics::TBitmap();
 TStringStream* array_bmp=new TStringStream("");
//Se crea el bitmap sobre el TStringStream,
//luego se carga sobre el TBitmap
//1.- Crear cabecera (54 bytes)
 array_bmp->Position=0;
 aux_int=19778; //codigo de tipo de btimap
  array_bmp->Write((void *)&aux_int,2);
 if(((3*ancho)%4)==0)ancho4=3*ancho;
  else ancho4=3*ancho+4-(3*ancho)%4; //ancho es multiplo de 4
   aux_int=54+alto*ancho4;//tamanyo total en bytes
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //debe haber ahora 4 bytes a 0 -reservados-
  array_bmp->Write((void *)&aux_int,4);
 aux_int=54; //offset hasta llegar a valores pixels
  array_bmp->Write((void *)&aux_int,4);
 aux_int=40;  //cabecera bitmap estandar windows
  array_bmp->Write((void *)&aux_int,4);
 aux_int=ancho; //ancho del bitmap
  array_bmp->Write((void *)&aux_int,4);
 aux_int=alto;   //alto del bitmap
  array_bmp->Write((void *)&aux_int,4);
 aux_int=1; //numero de planos
  array_bmp->Write((void *)&aux_int,2);
 aux_int=24; //bits por pixel
  array_bmp->Write((void *)&aux_int,2);
 aux_int=0; //codigo de compresion, 0=sin ella
  array_bmp->Write((void *)&aux_int,4);
 aux_int=alto*ancho4; //tamanyo del bitmap
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //resolucion horizontal,ppi
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //resolucion vertical, ppi
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //num colores en paleta
  array_bmp->Write((void *)&aux_int,4);
 aux_int=0; //num colores importantes
  array_bmp->Write((void *)&aux_int,4);
//2.- A 24 bit por pixel caso no se especifica paleta de color
//3.- Copiar el mapa de bits
//en primer lugar va la ultima fila, y asi hasta poner la fila 0 la ultima
//cada una con ceros al final hasta ser multiplo de 4 -ancho4-
 aux_int=0;
 for(i=alto-1; i>=0;i--)
 {
  for(j=0;j<ancho;j++)
  { array_bmp->Write((void *)&(pixelsB[ancho*i+j]),1); //copiar pixel
    array_bmp->Write((void *)&(pixelsG[ancho*i+j]),1); //copiar pixel
    array_bmp->Write((void *)&(pixelsR[ancho*i+j]),1); //copiar pixel
  }
  array_bmp->Write((void *)&aux_int,ancho4-3*ancho); //relleno de ceros
 }
//volcar del stream al bitmap
 array_bmp->Position=0;
 bitmap->LoadFromStream(array_bmp);
 delete array_bmp;
 return bitmap;
}
//******************************************************
//************* TImagen2Raw ****************************
//Saca de la TImagen una matriz 2d con los valores de los pixels en bruto
//Liberar despues la fila 0 y luego la total
byte ** TImagen::TImagen2RawBN()
{
 byte **matriz, *pixels;
 int X, Y, i;
  X=_HDim; Y=_VDim;
 pixels=new byte[X*Y];
 if(_NBands==1)
  MbufGet(ImagenID,(void *)pixels);
  else
  MbufGetColor(ImagenID, M_SINGLE_BAND, M_ALL_BAND,(void *)pixels);
 matriz=new byte *[Y];
 matriz[0]=pixels;
 for(i=1;i<Y;i++)
  matriz[i]=matriz[i-1]+X*sizeof(byte);
 return matriz;
}
