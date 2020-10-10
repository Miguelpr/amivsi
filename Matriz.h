#ifndef TMATRIZ_H
#define TMATRIZ_H
#include <ExtCtrls.hpp> 

/********************* MATRIZ ********************/
/* Clase que utiliza las MIL e implementa un algoritmo para el cálculo
 * del Optical FLow
 */
 
class TMatriz{
  public:


  
        TMatriz(int x, int y, int dPuntos);

        ~TMatriz();




        int getDimX();
        int getDimY();
        int getDistanciaPuntos();



        void copiar(TMatriz *m);
       

        bool hayVector(int x, int y);




        void reset();

        int getX(int posX, int posY);

        int getY(int posX, int posY);

        void setPunto(int posX, int posY,int valorX,int valorY);





   private:
        struct PUNTO{unsigned short int x,y;};
        PUNTO ** matriz, *pixels;
        int dimX;
        int dimY;
        int distanciaPuntos;



};




#endif
