//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TImagen.h"
#include "OpticalFlow.h"
#include "Navegacion.h"
#include "Secuenciador.h"
#include "ToolPaint.h"
#include "Etiquetado.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

// Clase SECUENCIADOR, crea un hilo de ejecucion para realizar el bucle
// de analisis del sistema AMIVSI. Realiza la creacion de objetos necesarias
// para la consecucion de los tres objetivos principales. Analisis del
// Optical Flow, analisis de la velocidad de movimiento, analisis de la
// profundidad y etiquetado de objetos.
//---------------------------------------------------------------------------

__fastcall Secuenciador::Secuenciador(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall Secuenciador::Execute()
{
int i=1;

AnsiString dirFoto="img\\1.bmp", dirFoto_1="img\\1.bmp";

if(FileExists(dirFoto)){

TImagen *imagen1=new TImagen();
TImagen *imagen2=new TImagen();


TDateTime tiempoInicio,tiempoFin;
float tiempoReal = 5.0;
float tiempoTotal = 0.0;
Word hour,minute,second,msecond;
AnsiString auxTime;
float tiempoVuelta = 0.0;



imagen2->Cargar(dirFoto);
OpticalFlow *opfl=new OpticalFlow(imagen2->_HDim, imagen2->_VDim);
Navegacion *navegador = new Navegacion();
Etiquetado *etiquetador = new Etiquetado();

ToolPaint *interfazAnalisis = new ToolPaint();


float velocidad = 0.0;
float velMedia = 0.0;
int count = 0;
interfazAnalisis->PintarVelocidadAnalogica(BitmapVelocimetro, velocidad);
interfazAnalisis->PintarVelocidadDigital(this->VelocimetroDigital,velocidad);

TMatriz *matrizOptical1 = new TMatriz(imagen2->_HDim,imagen2->_VDim,opfl->getDistanciaPuntos());



TImage *result=new TImage(Image1);
result->Picture->Bitmap->PixelFormat = pf24bit;

Image1->Picture->Bitmap=result->Picture->Bitmap;



// INICIALIZO OPCIONES DE REPRESENTACION

pintarDepth = false;
pintarOpfl = false;



// SE INICIA EL BUCLE DE ANALISIS AMIVSI
while(FileExists(dirFoto)){
 count++;
// TOMAMOS EL TIEMPO AL INICIO DE UNA VUELTA
tiempoInicio = Now();
 
// CARGAMOS IMAGENES PARA ANALIZAR
imagen1->Copiar(imagen2->ImagenID);
imagen2->Cargar(dirFoto);
imagen2->Sobel();


result->Picture->LoadFromFile(dirFoto_1);
//result->Picture->LoadFromFile("img\\0.bmp");

result->Picture->Bitmap->PixelFormat = pf24bit;

// PREPARAMOS LA MATRIZ DONDE SE ALMACENA EL OPTICAL FLOW

matrizOptical1->reset();

// CALCULAMOS EL OPTICAL FLOW
opfl->calcularOpticalFlow(matrizOptical1,imagen1,imagen2);



// CALCULAMOS VELOCIDAD Y REFRESCAMOS EN EL INTERFACE
velocidad = navegador->calcularVelocidad(0.2,opfl->getMaxEspacio());
interfazAnalisis->PintarVelocidadAnalogica(BitmapVelocimetro, velocidad);
interfazAnalisis->PintarVelocidadDigital(VelocimetroDigital,velocidad);

velMedia = velMedia + velocidad;

// PRESENTAMOS INFORMACION EN LA CONSOLA DE ANALISIS
Consola->Text = "=> Analizando imagen: " + dirFoto + "\n" + "\t" + " Puntos analisis: "+ opfl->getNumPuntosAnalisis()+"\n"  ;
//Consola->Text = Consola->Text + (AnsiString)(i-1) + "=>" + opfl->getNumPuntosAnalisis()+ "Vel: "+ FormatFloat("0.00",velocidad) + "\n";

//interfazAnalisis->PintarCruz(result,imagen2->_HDim/2, imagen2->_VDim/2);


// PINTAMOS EL OPTICAL FLOW CALCULADO SOBRE LA IMAGEN ORIGINAL
if(this->pintarOpfl){

        // PINTAMOS EL CALIBRE DE DISTANCIAS
        //interfazAnalisis->PintarCalibre(result);

        interfazAnalisis->PintarOpticalFlow(result,matrizOptical1);
}



// PINTAMOS EL MEDIDOR DE DIRECCION
interfazAnalisis->PintarVectorDireccion(BitmapDireccion,BitmapDireccion->Width/2,BitmapDireccion->Height-5,opfl->getVectorVelocidadX());



// PINTAMOS LA PROFUNDIDAD
if(pintarDepth){

interfazAnalisis->PintarDeph(result,matrizOptical1,this->Consola);

}
interfazAnalisis->PintarVentanaDeph(ImgDepth,matrizOptical1,this->Consola);


// PROCESAMOS EL ETIQUETADO DE OBJETOS

if(etiquetador->hayObjetosEncontrados()){
        etiquetador->actualizarRegistroEtiquetas(i-1);
        interfazAnalisis->PintarEtiquetas(result,etiquetador->getListaAnterior(),Consola,TObjetos,i-1);
}

etiquetador->lecturaListaObjetos(i,matrizOptical1,Consola);
etiquetador->asignarEtiquetas(this->Consola);




// PINTAMOS LA IMAGEN QUE SE HA ANALIZADO
Image1->Picture->Bitmap=result->Picture->Bitmap;





dirFoto_1 = dirFoto;
i=i+1;
dirFoto="img\\"+(AnsiString) i + ".bmp";



tiempoReal = tiempoReal + 0.2;

// TOMAMOS EL TIEMPO AL FINAL DE UNA VUELTA
tiempoFin = Now();

DecodeTime(tiempoFin-tiempoInicio,hour,minute,second,msecond);

// Convierto el tiempo a float
 auxTime = (AnsiString)second;
 tiempoVuelta = (float)auxTime.ToInt();
 auxTime = (AnsiString)msecond;
 tiempoVuelta = tiempoVuelta + ((float)auxTime.ToInt()/1000.0);

tiempoTotal = tiempoTotal + tiempoVuelta;

Consola->Text = Consola->Text +"TVuelta: "+(AnsiString)tiempoVuelta+"TReal: "+(AnsiString)tiempoReal +" TTotal: " + (AnsiString)tiempoTotal;



// RESTICCIONES DE TIEMPO
if(!etiquetador->hayObjetosEncontrados()){
if(tiempoTotal>tiempoReal){

if (FileExists(dirFoto)){

tiempoReal = tiempoReal + 0.2;
dirFoto_1 = dirFoto;
imagen1->Cargar(dirFoto);
imagen1->Sobel();
i=i+1;
dirFoto="img\\"+(AnsiString) i + ".bmp";

}



}
}



}

velMedia = velMedia / count;

Consola->Text = Consola->Text + "VELOCIDAD MEDIA :" + (AnsiString)velMedia;

// SE ELIMINAN LOS OBJETOS CREADOS
delete result;
delete etiquetador;
delete opfl;
delete navegador;
delete interfazAnalisis;


delete matrizOptical1;

delete imagen1;

delete imagen2;

}

}


//---------------------------------------------------------------------------
