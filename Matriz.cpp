#include "Matriz.h"






//***************************************************
//*********** CONSTRUCTOR ***************************
//***************************************************
TMatriz::TMatriz(int x, int y, int dPuntos){
        distanciaPuntos=dPuntos;
        dimX=x/distanciaPuntos;
        dimY=y/distanciaPuntos;




        pixels = new PUNTO[dimX*dimY];

        matriz = new PUNTO *[dimX];
        matriz[0] = pixels;
        int i;
        for (i=1;i<dimX;i++){
                matriz[i] = matriz[i-1]+dimY;
        }

        this->reset();
        

}




//***************************************************
//*********** DESTRUCTOR ****************************
//***************************************************
TMatriz::~TMatriz()
{

        delete []matriz[0];
        delete []matriz;

}


//***************************************************
//**** METODOS DE LECTURA Y ESCRITURA ATRIBUTOS******
//***************************************************
int TMatriz::getDimX(){
        return dimX;
}

int TMatriz::getDimY(){
        return dimY;
}

int TMatriz::getDistanciaPuntos(){
        return distanciaPuntos;
}
int TMatriz::getX(int posX, int posY){

        return matriz[posX][posY].x;

}

int TMatriz::getY(int posX, int posY){


        return matriz[posX][posY].y;

}

void TMatriz::setPunto(int posX, int posY,int valorX,int valorY){


        matriz[posX][posY].x = valorX;
        matriz[posX][posY].y = valorY;
}


//***************************************************
//**** RESETEAR MATRIZ*******************************
//***************************************************
void TMatriz::reset(){

       

        memset(pixels, 0, dimX*dimY*sizeof(PUNTO));
}

//***************************************************
//**** COPIAR MATRIZ*******************************
//***************************************************
void TMatriz::copiar(TMatriz *m){
        dimX = m->getDimX();
        dimY = m->getDimY();
        matriz = m->matriz;
        pixels = m->pixels;


}





//***************************************************
//*************** HAY VECTOR*************************
//***************************************************
bool TMatriz::hayVector(int x, int y){

       if ((getX(x,y)>0)||(getY(x,y)>0)){
                return true;

       }else {
                return false;
       }

}
