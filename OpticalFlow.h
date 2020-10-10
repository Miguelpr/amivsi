#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H
#include <iostream.h> //Para lectura de fichero
#include <fstream.h>

#include<graphics.hpp>
#include <ExtCtrls.hpp> //Para usar TImage en utilidades
#include "TImagen.h"
#include "Matriz.h"

#include <mil.h>


/********************* OPTICAL FLOW ********************/
/* Clase que utiliza las MIL e implementa un algoritmo para el cálculo
 * del Optical FLow
 */

class OpticalFlow
{
  public:


        OpticalFlow(int sizeX, int sizeY);
        ~OpticalFlow();
        
        void BuscarPatron(MIL_ID ImagenID1,MIL_ID ImagenID2, int posX, int posY, int *x2, int *y2);

        void calcularVentanaBusqueda(int offX, int offY);

        void calcularPosicionBusqueda(int posX, int posY,int *origenVentanaX, int *origenVentanaY);

        int getDistanciaPuntos();

        int getVectorVelocidadX();
        int getVectorVelocidadY();

        int getNumVectores();

        int getNumPuntosAnalisis();



        void setUmbral(int u);
        void setUmbralVelocidad(int uv);

        int getUmbral();
        int getUmbralVelocidad();

        float getMaxEspacio();

        int intensidadMedia(byte **matriz, int offX, int offY, int sizeX, int sizeY);

        void calcularOpticalFlow(TMatriz *matrizOptical,TImagen *img1, TImagen *img2);
        void calcularDistancia(int h1,int h2,float foco, float velocidad, float tiempo, float &h, float &d);


        void alturaMaxima(TMatriz *matriz1, int &h1, int &h2, int &x1, int &y1, int &x2, int &y2);

        void filtroVectoresLineales(TMatriz *matrizResultado, TMatriz *matriz1,TMatriz *matriz2);
        void lecturaFicheroConfiguracion();

       
        int XDim;
        int YDim;



  private:

        int sizePatronX;
        int sizePatronY;
        int sizeBusquedaX,sizeBusquedaY;
        int sizeBusquedaXMax,sizeBusquedaXMin;
        int sizeBusquedaYMax,sizeBusquedaYMin;

        int distanciaPuntos;
        float coeficienteVentanaMax;
        float coeficienteVentanaMin;
        float coeficientePatron;
        float porcentajeValido;
        int vectorVelocidadX;
        int vectorVelocidadY;
        int numPuntosAnalisis;
        int numVectores;
        int umbral;
        int umbralVelocidad;




        float maxEspacio;
  




        
};


#endif
