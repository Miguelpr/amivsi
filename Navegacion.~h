#ifndef NAVEGACION_H
#define NAVEGACION_H

#include "Matriz.h"




/********************* NAVEGACION ********************/
/* Clase que utilza el calculo del optical flow para extraer*/
/* informacion de movimiento*/

class Navegacion
{
  public:


        Navegacion();
        ~Navegacion();

        float distanciaCalibrada(int x);
        float calcularVelocidadPromedio(float vel);
        float calcularVelocidad(float tiempo,float maxEspacio);
        float getVelocidad();
        void setVelocidad(float vel);

  private:
    
        float v1,v2,v3,v4,v5,velocidad;


        
};


#endif