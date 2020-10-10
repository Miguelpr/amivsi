#ifndef ETIQUETADO_H
#define ETIQUETADO_H
#include <iostream>

#include <iostream.h> //Para lectura de fichero
#include <fstream.h>

#include "Matriz.h"
#include "TListaEtiquetas.h"

/********************* ETIQUETADO **************************/
/* Clase que utilza el calculo del optical flow calcular   */
/* posiciones futuras de los objetos en la siguiente imagen*/

class Etiquetado {
   public:

   struct RECTANGULO{int x1,y1,x2,y2;};




    Etiquetado();
    ~Etiquetado();


    bool hayObjetosEncontrados();
 


    TListaEtiquetas* getListaAnterior();
    

    




   void crearZonaObjeto(int x1,int y1,int x2,int y2);

   void estimarPuntoFuturo(TMatriz *matrizOptical,int x1,int y1, int *x2, int *y2);

   bool estimarZonaFutura(TMatriz *matrizOptical);

   void lecturaListaObjetos(int imagenActual,TMatriz *matrizOptical,TMemo *Consola);

   void asignarEtiquetas(TMemo *Consola);

   void actualizarRegistroEtiquetas(int idImagen);



    
   private:

   TListaEtiquetas *listaAnterior, *listaNueva;

   bool hayObjetos;
   
   int ultimaEtiqueta;


   RECTANGULO zonaInicial;
   RECTANGULO zonaFinal;

    
};


#endif
