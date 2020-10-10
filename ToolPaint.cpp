#include "ToolPaint.h"


//---------------------------------------------------------------------------


/********************* TOOL PAINT **********************************/
/* Clase que implementa m�todos para pintar sobre una imagen bitmap*/
/*******************************************************************/



//***************************************************
//*********** CONSTRUCTOR ***************************
//***************************************************

ToolPaint::ToolPaint(){
        tiempoMaximo = 25;
}

//***************************************************
//*********** DESTRUCTOR ****************************
//***************************************************
ToolPaint::~ToolPaint()
{

}

//***************************************************
//*********** PINTAR OPTICAL FLOW *******************
//***************************************************
void ToolPaint::PintarOpticalFlow(TImage *img, TMatriz *mat){


  for(int i=0;i<mat->getDimX();i++)
  {
  for(int j=0;j<mat->getDimY();j++)
        {

                if(mat->hayVector(i,j)){

                                //PintarPunto(img,i*mat->getDistanciaPuntos(),j*mat->getDistanciaPuntos());
                                PintarVector(img,i*mat->getDistanciaPuntos(),j*mat->getDistanciaPuntos(),mat->getX(i,j),mat->getY(i,j));
                        }

                }

        }


}

//***************************************************
//*********** PINTAR VECTOR *************************
//***************************************************
void ToolPaint::PintarVector(TImage *img, int x1,int y1,int x2,int y2)
{
img->Canvas->Pen->Color=clRed;
img->Canvas->Pen->Width=3;
img->Canvas->MoveTo(x1,y1);
img->Canvas->LineTo(x1,y1);
img->Canvas->Pen->Width=1;
img->Canvas->LineTo(x2,y2);
}

//***************************************************
//*********** PINTAR RECTANGULO *********************
//***************************************************

void ToolPaint::PintarRectangulo(TImage *img, int x1,int y1,int x2,int y2)
{
img->Canvas->Pen->Color=clWhite;
img->Canvas->Pen->Width=1;
img->Canvas->MoveTo(x1,y1);
img->Canvas->LineTo(x2,y1);
img->Canvas->LineTo(x2,y2);
img->Canvas->LineTo(x1,y2);
img->Canvas->LineTo(x1,y1);

}


//***************************************************
//*********** PINTAR CRUZ ***************************
//***************************************************
void ToolPaint::PintarCruz(TImage *img, int x1,int y1)
{
img->Canvas->Pen->Color=clRed;
img->Canvas->Pen->Width=3;
img->Canvas->MoveTo(x1-15,y1);
img->Canvas->LineTo(x1+15,y1);
img->Canvas->MoveTo(x1,y1-15);
img->Canvas->LineTo(x1,y1+15);

}




//***************************************************
//*********** PINTAR PUNTO ***************************
//***************************************************
void ToolPaint:: PintarPunto(TImage *img, int x1,int y1) {

img->Canvas->Pen->Color=clWhite;
img->Canvas->Pen->Width=3;
img->Canvas->MoveTo(x1,y1);
img->Canvas->LineTo(x1+1,y1+1);
}

//***************************************************
//*********** PINTAR VELOCIDAD ANALOGICA ************
//***************************************************
void ToolPaint::PintarVelocidadAnalogica(TImage *img, float vel)
{

img->Picture->LoadFromFile("velocimetro.bmp");
img->Canvas->Pen->Color=(TColor)0x000066FF;
img->Canvas->Pen->Width=3;
img->Canvas->MoveTo(144,144);
if (vel<2.5)
img->Canvas->LineTo(74,197);
else if (vel<5)
img->Canvas->LineTo(72,194);
else if (vel<7.5)
img->Canvas->LineTo(70,190);
else if (vel<10)
img->Canvas->LineTo(68,187);
else if (vel<12.5)
img->Canvas->LineTo(64,182);
else if (vel<15)
img->Canvas->LineTo(63,174);
else if (vel<17.5)
img->Canvas->LineTo(60,167);
else if (vel<20)
img->Canvas->LineTo(59,160);
else if (vel<22.5)
img->Canvas->LineTo(59,151);
else if (vel<25)
img->Canvas->LineTo(58,144);
else if (vel<27.5)
img->Canvas->LineTo(59,136);
else if (vel<30)
img->Canvas->LineTo(60,128);
else if (vel<32.5)
img->Canvas->LineTo(62,120);
else if (vel<35)
img->Canvas->LineTo(65,112);
else if (vel<37.5)
img->Canvas->LineTo(67,106);
else if (vel<40)
img->Canvas->LineTo(71,99);
else if (vel<42.5)
img->Canvas->LineTo(75,93);
else if (vel<45)
img->Canvas->LineTo(81,86);
else if (vel<47.5)
img->Canvas->LineTo(86,88);
else if (vel<50)
img->Canvas->LineTo(92,76);
else if (vel<52.5)
img->Canvas->LineTo(97,72);
else if (vel<55)
img->Canvas->LineTo(105,67);
else if (vel<57.5)
img->Canvas->LineTo(112,64);
else if (vel<60)
img->Canvas->LineTo(120,61);
else if (vel<62.5)
img->Canvas->LineTo(127,59);

}


//***************************************************
//*********** PINTAR VELOCIDAD DIGITAL **************
//***************************************************
void ToolPaint::PintarVelocidadDigital(TLabel *velocimetroDigital, float vel){

 velocimetroDigital->Caption = FormatFloat("0.00",vel) + "Km/h";
}


//***************************************************
//*********** PINTAR VECTOR DIRECCION ***************
//***************************************************
void ToolPaint::PintarVectorDireccion(TImage *img, int x1,int y1,int x2)
{
img->Picture->LoadFromFile("direccion.bmp");
float valX = abs(x2);
float valY = abs(x2);

valX = (valX*valX*(-0.007654))+(valX*1.5666666666)+80;
valY = (valY*valY*(-0.0002469135))+(valY*0.87777777777777)+1;

valY = valY+5;

if(x2<0){
        valX = 159-valX;

}
img->Canvas->Pen->Color=clRed;
img->Canvas->Pen->Width=3;
img->Canvas->MoveTo(x1,y1);
img->Canvas->LineTo(valX,valY);

}


//***************************************************
//*********** PINTAR CALIBRE ************************
//***************************************************
void ToolPaint::PintarCalibre(TImage *img){

img->Canvas->Pen->Color=clRed;
img->Canvas->Pen->Width=3;

// 12.5 m
img->Canvas->TextOutA(5,371,"12.5 m");
img->Canvas->MoveTo(0,391);
img->Canvas->LineTo(20,391);
img->Canvas->MoveTo(700,391);
img->Canvas->LineTo(720,391);

img->Canvas->Pen->Width=1;
img->Canvas->MoveTo(0,391);
img->Canvas->LineTo(720,391);
img->Canvas->Pen->Width=3;


// 10 m
img->Canvas->TextOutA(5,398,"10 m");
img->Canvas->MoveTo(0,418);
img->Canvas->LineTo(20,418);
img->Canvas->MoveTo(700,418);
img->Canvas->LineTo(720,418);

img->Canvas->Pen->Width=1;
img->Canvas->MoveTo(0,418);
img->Canvas->LineTo(720,418);
img->Canvas->Pen->Width=3;

// 7.5 m
img->Canvas->TextOutA(5,444,"7.5 m");
img->Canvas->MoveTo(0,464);
img->Canvas->LineTo(20,464);
img->Canvas->MoveTo(700,464);
img->Canvas->LineTo(720,464);

img->Canvas->Pen->Width=1;
img->Canvas->MoveTo(0,464);
img->Canvas->LineTo(720,464);
img->Canvas->Pen->Width=3;

// 5 m
img->Canvas->TextOutA(5,527,"5 m");
img->Canvas->MoveTo(0,547);
img->Canvas->LineTo(20,547);
img->Canvas->MoveTo(700,547);
img->Canvas->LineTo(720,547);

img->Canvas->Pen->Width=1;
img->Canvas->MoveTo(0,547);
img->Canvas->LineTo(720,547);
img->Canvas->Pen->Width=3;



}

//***************************************************
//*********** PINTAR PANTALLA PROFUNDIDAD ***********
//***************************************************
void ToolPaint::PintarVentanaDeph(TImage *img, TMatriz *mat,TMemo *Consola){


int d1=0,d2=0;
int cont = 0;
TColor color;
float derivada=0.0;
float tiempoParaContacto=0.0;
float incremento = (this->tiempoMaximo * 2.0 ) / 6.0;
float tiempoMax = 0.0;
int dPuntos=mat->getDistanciaPuntos();
int mitadDimY=mat->getDimY()*dPuntos/2;
TImage *result=new TImage(img);

result->Picture->Bitmap->LoadFromFile("imagenDepth.bmp");



 for(int i=0;i<mat->getDimX();i++){
 for(int j=0;j<mat->getDimY();j++){


                        if(mat->hayVector(i,j)){



                        d1=abs(mitadDimY-mat->getY(i,j));

                        d2=abs(mitadDimY-(j*dPuntos));

                        derivada=(float)(d1-d2)/0.2;

                        if (derivada>0 && d2>0){
                        cont++;
                        tiempoParaContacto= (d2/derivada);

                                tiempoMax = tiempoParaContacto + tiempoMax;


                        if ((tiempoParaContacto>0)&&(tiempoParaContacto<incremento)){
                                color = (TColor)0x0000FF;
                        }else if (tiempoParaContacto<incremento*2){
                                color = (TColor)0x0033CC;
                        }else if (tiempoParaContacto<incremento*3){
                                color = (TColor)0x006699;
                        }else if (tiempoParaContacto<incremento*4){
                                color = (TColor)0x009966;
                        }else if (tiempoParaContacto<incremento*5){
                                color = (TColor) 0x00CC33 ;
                        }else {
                                color = (TColor)0x00FF00;
                        }

                        result->Canvas->Pen->Color = color;
                        result->Canvas->Brush->Color = color;
                        result->Canvas->Rectangle(((i*dPuntos-(dPuntos/2)-1))*0.4,((j*dPuntos-(dPuntos/2)-1)*0.4),((i*dPuntos+(dPuntos/2)+1)*0.4),((j*dPuntos+(dPuntos/2)+1)*0.4));


                        }
                                }

                }
          }

   this->tiempoMaximo = tiempoMax / cont;
   img->Picture->Bitmap = result->Picture->Bitmap;


  delete result;
}


//***************************************************
//*********** PINTAR DEPTH**************************
//***************************************************
void ToolPaint::PintarDeph(TImage *img, TMatriz *mat,TMemo *Consola){
int d1=0,d2=0;
int cont = 0;
TColor color;
float derivada=0.0;
float tiempoParaContacto=0.0;
float incremento = (this->tiempoMaximo * 2.0 ) / 6.0;
float tiempoMax = 0.0;
int dPuntos=mat->getDistanciaPuntos();
int mitadDimY=mat->getDimY()*dPuntos/2;




 for(int i=0;i<mat->getDimX();i++){
 for(int j=0;j<mat->getDimY();j++){


                        if(mat->hayVector(i,j)){



                        d1=abs(mitadDimY-mat->getY(i,j));

                        d2=abs(mitadDimY-(j*dPuntos));

                        derivada=(d1-d2)/0.2;

                        if (derivada>0 && d2>0){
                        cont++;
                        tiempoParaContacto= (d2/derivada);

                                tiempoMax = tiempoParaContacto + tiempoMax;
                        

                        if ((tiempoParaContacto>0)&&(tiempoParaContacto<incremento)){
                                color = (TColor)0x0000FF;
                        }else if (tiempoParaContacto<incremento*2){
                                color = (TColor)0x0033CC;
                        }else if (tiempoParaContacto<incremento*3){
                                color = (TColor)0x006699;
                        }else if (tiempoParaContacto<incremento*4){
                                color = (TColor)0x009966;
                        }else if (tiempoParaContacto<incremento*5){
                                color = (TColor) 0x00CC33 ;
                        }else {
                                color = (TColor)0x00FF00;
                        }

                        img->Canvas->Pen->Color = color;
                        img->Canvas->Brush->Color = color;
                        img->Canvas->Rectangle((i*dPuntos-(dPuntos/2)-1),(j*dPuntos-(dPuntos/2)-1),(i*dPuntos+(dPuntos/2)+1),(j*dPuntos+(dPuntos/2)+1));


                        }
                                }

                }
          }

   Consola->Text = Consola->Text + " Pto Prof: "+ (AnsiString)cont;

   this->tiempoMaximo = tiempoMax / cont;
   img->Canvas->Pen->Color = clWhite;
   img->Canvas->Brush->Color = clWhite;


}




//***************************************************
//*********** PINTAR ETIQUETA ***********************
//***************************************************

void ToolPaint::PintarEtiquetas(TImage *img, TListaEtiquetas *listaEtiquetas,TMemo *Consola,TStringGrid *TObjetos,int idImagen){
        int numElem = listaEtiquetas->getNumElem();
        //AVANZO LA TABLA TANTAS POSICIONES COMO VOY A INTRODUCIR
        for(int j=9;j>-1;j--){
                TObjetos->Cells[0][j+numElem] = TObjetos->Cells[0][j];
                TObjetos->Cells[1][j+numElem] = TObjetos->Cells[1][j];
                TObjetos->Cells[2][j+numElem] = TObjetos->Cells[2][j];
                TObjetos->Cells[3][j+numElem] = TObjetos->Cells[3][j];
        }

        for(int i=0;i<numElem;i++){
                PintarRectangulo(img,listaEtiquetas->getX1Inicial(i),listaEtiquetas->getY1Inicial(i),listaEtiquetas->getX2Inicial(i),listaEtiquetas->getY2Inicial(i));
                img->Canvas->TextOutA(listaEtiquetas->getX1Inicial(i),listaEtiquetas->getY1Inicial(i)-20,listaEtiquetas->getEtiqueta(i));
                TObjetos->Cells[0][i+1] = listaEtiquetas->getEtiqueta(i);
                TObjetos->Cells[1][i+1] = (AnsiString)"(" + listaEtiquetas->getX1Inicial(i) + "," + listaEtiquetas->getY1Inicial(i)+ ") - (" + listaEtiquetas->getX2Inicial(i)+ "," +listaEtiquetas->getY2Inicial(i)+")";
                TObjetos->Cells[2][i+1] = (AnsiString)"(" + listaEtiquetas->getX1Final(i) + "," + listaEtiquetas->getY1Final(i)+ ") - (" + listaEtiquetas->getX2Final(i)+ "," +listaEtiquetas->getY2Final(i)+")";
                TObjetos->Cells[3][i+1] = (AnsiString)idImagen + ".bmp";

        }
}


