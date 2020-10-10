#include "TListaEtiquetas.h"
#include <iostream>




//***************************************************
//*********** CONSTRUCTOR ***************************
//***************************************************
TListaEtiquetas::TListaEtiquetas() {

// CREO LAS LISTAS DE LOS ARRAYS

objeto = new NODO[15];
numElem = 0; 


}
//***************************************************
//*********** CONSTRUCTOR DE COPIA ******************
//***************************************************
TListaEtiquetas::TListaEtiquetas(NODO* obj,int num){

objeto = obj;
numElem = num;



}


//***************************************************
//*********** DESTRUCTOR ****************************
//***************************************************
TListaEtiquetas::~TListaEtiquetas()
{

        delete []objeto;
        

}
//***************************************************
//*********** COPIAR LISTA **************************
//***************************************************
void TListaEtiquetas::copiarLista(TListaEtiquetas *listaAux){

 for(int i=0;i<listaAux->getNumElem();i++){
        objeto[i].inicial.x1=listaAux->getX1Inicial(i);
        objeto[i].inicial.y1=listaAux->getY1Inicial(i);
        objeto[i].inicial.x2=listaAux->getX2Inicial(i);
        objeto[i].inicial.y2=listaAux->getY2Inicial(i);

        objeto[i].final.x1=listaAux->getX1Final(i);
        objeto[i].final.y1=listaAux->getY1Final(i);
        objeto[i].final.x2=listaAux->getX2Final(i);
        objeto[i].final.y2=listaAux->getY2Final(i);

        objeto[i].etiqueta = listaAux->getEtiqueta(i);

 }

 numElem = listaAux->numElem;
}



//***************************************************
//**** METODOS DE LECTURA Y ESCRITURA ATRIBUTOS******
//***************************************************



int TListaEtiquetas::getNumElem(){

        return numElem;

}

void TListaEtiquetas::setNumElem(int num){

        numElem = num;
}

int TListaEtiquetas::getX1Inicial(int idElemento){
 return objeto[idElemento].inicial.x1;
}

int TListaEtiquetas::getY1Inicial(int idElemento)
{
 return objeto[idElemento].inicial.y1;
}

int TListaEtiquetas::getX2Inicial(int idElemento){
 return objeto[idElemento].inicial.x2;
}

int TListaEtiquetas::getY2Inicial(int idElemento){
 return objeto[idElemento].inicial.y2;
}


int TListaEtiquetas::getX1Final(int idElemento){
 return objeto[idElemento].final.x1;
}

int TListaEtiquetas::getY1Final(int idElemento){
 return objeto[idElemento].final.y1;
}

int TListaEtiquetas::getX2Final(int idElemento){
 return objeto[idElemento].final.x2;
}

int TListaEtiquetas::getY2Final(int idElemento){
 return objeto[idElemento].final.y2;
}


//***************************************************
//*********** INSERTAR OBJETO ***********************
//***************************************************
void TListaEtiquetas::insertar(int x1i,int y1i,int x2i,int y2i,int x1f,int y1f,int x2f,int y2f,AnsiString etiqueta){

// Asigno la zona inicial
 objeto[numElem].inicial.x1 = x1i;
 objeto[numElem].inicial.y1 = y1i;
 objeto[numElem].inicial.x2 = x2i;
 objeto[numElem].inicial.y2 = y2i;

 // Asigno la zona final
 objeto[numElem].final.x1 = x1f;
 objeto[numElem].final.y1 = y1f;
 objeto[numElem].final.x2 = x2f;
 objeto[numElem].final.y2 = y2f;

 // Asigno la etiqueta
 objeto[numElem].etiqueta = etiqueta;

 numElem++;

}


//***************************************************
//*********** GET ETIQUETA **************************
//***************************************************
AnsiString TListaEtiquetas::getEtiqueta(int idElemento){

 return objeto[idElemento].etiqueta;
 
}



//***************************************************
//*********** MODIFICAR ETIQUETA ********************
//***************************************************
void TListaEtiquetas::setEtiqueta (int idElemento,AnsiString etiqueta){

 objeto[idElemento].etiqueta = etiqueta;

}


//***************************************************
//*********** COINCIDE PREDICCION *******************
//***************************************************
bool TListaEtiquetas::coincidePrediccion(int x1n,int y1n,int x2n,int y2n,int x1a,int y1a,int x2a,int y2a){

 bool resultado = false;

 if ((x1n>=x1a)&&(y1n>=y1a)&&(x2n<=x2a)&&(y2n<=y2a)){
        resultado = true;
 }


 return resultado;
}



