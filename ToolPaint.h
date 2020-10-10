#ifndef TOOLPAINT_H
#define TOOLPAINT_H
#include <ExtCtrls.hpp> //Para usar TImage en utilidades
#include "Matriz.h"
#include "TListaEtiquetas.h"
#include <Grids.hpp>

//---------------------------------------------------------------------------

/********************* TOOL PAINT **********************************/
/* Clase que implementa métodos para pintar sobre una imagen bitmap*/
/*******************************************************************/

class ToolPaint
{
        public:

                ToolPaint();
                ~ToolPaint();

                void PintarOpticalFlow(TImage *img,TMatriz *mat);
                void PintarVector(TImage *img, int x1,int y1,int x2,int y2);
                void PintarRectangulo(TImage *img, int x1,int y1,int x2,int y2);
                void PintarCruz(TImage *img, int x1,int y1);
   
                void PintarVelocidadAnalogica(TImage *img, float vel);
                void PintarVelocidadDigital(TLabel *velocimetroDigital, float vel);
                void PintarCalibre(TImage *img);
                void PintarVectorDireccion(TImage *img, int x1,int y1,int x2);
  
                void PintarPunto(TImage *img, int x1,int y1);
                void PintarDeph(TImage *img, TMatriz *mat,TMemo *Consola);
                void PintarVentanaDeph(TImage *img, TMatriz *mat,TMemo *Consola);

                void PintarEtiquetas(TImage *img, TListaEtiquetas *listaEtiquetas,TMemo *Consola,TStringGrid *TObjetos,int idImagen);

private:
        int tiempoMaximo;
};
#endif
