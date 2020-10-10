#ifndef TLISTAETIQUETAS_H
#define TLISTAETIQUETAS_H
#include <iostream>
#include <Classes.hpp>


/********************* TListaEtiquetas **************************/
/* Clase que implementa el tipo de datos lista sobr un array*/
/* de dimension est�tica, y almacena las etiquetas **********/

class TListaEtiquetas {
   public:

   struct RECTANGULO{int x1,y1,x2,y2;};
   struct NODO{RECTANGULO inicial, final;AnsiString etiqueta;};

    
   

    TListaEtiquetas();
    TListaEtiquetas(NODO* obj,int num);
    ~TListaEtiquetas();

    void copiarLista(TListaEtiquetas *listaAux);



    int getX1Inicial(int idElemento);
    int getY1Inicial(int idElemento);
    int getX2Inicial(int idElemento);
    int getY2Inicial(int idElemento);

    int getX1Final(int idElemento);
    int getY1Final(int idElemento);
    int getX2Final(int idElemento);
    int getY2Final(int idElemento); 

    int getNumElem();
    void setNumElem(int num);

    void setEtiqueta (int idElemento,AnsiString etiqueta);
    AnsiString getEtiqueta(int idElemento);

    void insertar(int x1i,int y1i,int x2i,int y2i,int x1f,int y1f,int x2f,int y2f,AnsiString etiqueta);

    bool coincidePrediccion(int x1n,int y1n,int x2n,int y2n,int x1a,int y1a,int x2a,int y2a);




    
   private:

   NODO *objeto;
   int numElem;

    
};


#endif