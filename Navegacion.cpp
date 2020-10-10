#include "Navegacion.h"






//***************************************************
//*********** CONSTRUCTOR ***************************
//***************************************************
Navegacion::Navegacion(){


        v1 = 0.0;
        v2 = 0.0;
        v3 = 0.0;
        v4 = 0.0;
        v5 = 0.0;
        velocidad = 0.0;

}


//***************************************************
//*********** DESTRUCTOR ****************************
//***************************************************
Navegacion::~Navegacion()
{

}


//***************************************************
//*********** GET VELOCIDAD *************************
//***************************************************
 float Navegacion::getVelocidad(){
        return this->velocidad;
 }

//***************************************************
//*********** SET VELOCIDAD *************************
//***************************************************
 void Navegacion::setVelocidad(float vel){
        this->velocidad = vel;
 }



//*****************************************************
//************** DISTANCIA CALIBRADA *******************
//*****************************************************

float Navegacion::distanciaCalibrada(int x){

        float y = 0.0;

        y = (0.000188*x*x) - (0.21995*x) + (69.143297);

        return y;

}


//*****************************************************
//************** CALCULAR VELOCIDAD PROMEDIO **********
//*****************************************************

float Navegacion::calcularVelocidadPromedio(float vel){

if(vel != 0.0){
        v5 = v4;
        v4 = v3;
        v3 = v2;
        v2 = v1;
        v1 = vel;

        //Que no exista un decremento o aumento de velocidad mayor al 30 %
        if((abs((int)(v2-v1))<(v2*0.3))){
                this->setVelocidad(((v1+v2+v3+v4+v5)/5));

        }
}
 return this->getVelocidad();
}


//*****************************************************
//************** CALCULAR VELOCIDAD *******************
//*****************************************************

float Navegacion::calcularVelocidad(float tiempo,float maxEspacio){

float vel = 0.0;

vel = maxEspacio/tiempo;
vel = (vel/1000.0)*(3600.0);

vel = calcularVelocidadPromedio(vel);
return vel;

}
