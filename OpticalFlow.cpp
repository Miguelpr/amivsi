#include "OpticalFlow.h"




//***************************************************
//*********** CONSTRUCTOR ***************************
//***************************************************
OpticalFlow::OpticalFlow(int sizeX, int sizeY)
{

    coeficienteVentanaMax = 0.16;
    coeficienteVentanaMin = 0.08;
    coeficientePatron = 0.05;

    // Establezco las dimensiones de las im�genes a analizar
    XDim = sizeX;
    YDim = sizeY;







    //Distancia entre puntos a calcular en la imagen
    distanciaPuntos = 9;
    porcentajeValido = 60.0;

    // Inicializo los umbrales utilizados
    umbral = 100;
    umbralVelocidad = 45;

    lecturaFicheroConfiguracion();

    // Establezco las dimensiones maximas y minimas de la ventana de busqueda
    sizeBusquedaXMax = XDim * coeficienteVentanaMax;
    sizeBusquedaXMin = XDim * coeficienteVentanaMin;
    sizeBusquedaYMax = YDim * coeficienteVentanaMax;
    sizeBusquedaYMin = YDim * coeficienteVentanaMin;

    // Establezco la dimension del patron de busqueda
    sizePatronX = XDim * coeficientePatron;
    sizePatronY = YDim * coeficientePatron;

    vectorVelocidadX = 0;
    vectorVelocidadY = 0;

    // Inicializo el numero de vectores y de puntos de an�lisis
    numVectores = 0;
    numPuntosAnalisis = 0;




    maxEspacio = 0.0;


}


//***************************************************
//*********** DESTRUCTOR ****************************
//***************************************************
OpticalFlow::~OpticalFlow()
{

}


//***************************************************
//**** METODOS DE LECTURA Y ESCRITURA ATRIBUTOS******
//***************************************************


// ** DISTANCIA PUNTOS ***
int OpticalFlow::getDistanciaPuntos(){
        return distanciaPuntos;
}

// ** VECTOR VELOCIDAD ***
int OpticalFlow::getVectorVelocidadX(){
        return vectorVelocidadX;
}

int OpticalFlow::getVectorVelocidadY(){
        return vectorVelocidadY;
}

// ** NUMERO DE VECTORES ***
int OpticalFlow::getNumVectores(){
        return numVectores;
}

// ** NUMERO DE PUNTOS DE ANALISIS ***
int OpticalFlow::getNumPuntosAnalisis(){
        return numPuntosAnalisis;
}


void OpticalFlow::setUmbral(int u){
        this->umbral = u;
}

void OpticalFlow::setUmbralVelocidad(int uv){
        this->umbralVelocidad = uv;
}

int OpticalFlow::getUmbral(){
        return this->umbral;
}
int OpticalFlow::getUmbralVelocidad(){
        return this->umbralVelocidad;
}



  float OpticalFlow::getMaxEspacio() {
        return this->maxEspacio;
 }


//**********************************************************
//******** CALCULAR TAMANO VENTANA DE BUSQUEDA *************
//**********************************************************

void OpticalFlow::calcularVentanaBusqueda(int offX, int offY){

    float coeficiente;

    // Size en X
    coeficiente =   ((float)sizeBusquedaXMin - (float)sizeBusquedaXMax) / ((float)XDim/2.0);
    if (offX>(XDim/2)){
            offX = XDim - offX;
    }
    sizeBusquedaX = (coeficiente * offX) + sizeBusquedaXMax;

    // Size en Y
    coeficiente =   ((float)sizeBusquedaYMin - (float)sizeBusquedaYMax) / ((float)YDim/2.0);

    if (offY>(YDim/2)){
            offY = YDim - offY;
    }

    sizeBusquedaY = (coeficiente * offY) + sizeBusquedaYMax;



}

//**********************************************************
//**** CALCULAR LA POSICION DE LA VENTANA DE BUSUQEDA ******
//**********************************************************

void OpticalFlow::calcularPosicionBusqueda(int posX, int posY,int *origenVentanaX, int *origenVentanaY){

    float desplazamientoX = 0.0 , desplazamientoY = 0.0;
    



    desplazamientoX = float((posX - float(XDim/2) )/(XDim/2)) * float(sizeBusquedaX/2);
    desplazamientoY = float((posY - float(YDim/2) )/(YDim/2)) * float(sizeBusquedaY/2);

    *origenVentanaX = (posX - (sizeBusquedaX/2)) + desplazamientoX;
    *origenVentanaY = (posY - (sizeBusquedaY/2)) + desplazamientoY;

    // Corregimos los posibles errores en los marcos

    // Se sale por la izquierda
    if(*origenVentanaX<0){

        sizeBusquedaX = sizeBusquedaX + *origenVentanaX;
        *origenVentanaX = 0;
    }

    // Se sale por abajo
    if(*origenVentanaY<0){
        sizeBusquedaY = sizeBusquedaY + *origenVentanaY;
        *origenVentanaY = 0;
    }

    // Se sale por la derecha
    if((*origenVentanaX + sizeBusquedaX)>XDim){
        sizeBusquedaX = XDim - *origenVentanaX - 1;

    }

    // Se sale por arriba
    if((*origenVentanaY + sizeBusquedaY)>YDim){
        sizeBusquedaY = YDim - *origenVentanaY - 1;

    }


}



//*****************************************************
//************** BUSCAR PATRON ************************
//*****************************************************

void OpticalFlow::BuscarPatron(MIL_ID ImagenID1,MIL_ID ImagenID2, int posX, int posY, int *x2, int *y2)
{
  int origenVentanaX = 0, origenVentanaY = 0;
  double x=0.0, y=0.0;
  //x2=0;
  //y2=0;


    if  ((posX-(sizePatronX/2))>=0 && (posY-(sizePatronY/2))>=0){
  if (((posX+sizePatronX)<XDim)&&((posY+sizePatronY)<YDim)){
  MIL_ID patron;
  MIL_ID PatResultId;

  calcularVentanaBusqueda(posX,posY);


  MpatAllocModel(M_DEFAULT, ImagenID1, posX-(sizePatronX/2), posY-(sizePatronY/2), sizePatronX, sizePatronY, M_NORMALIZED, &patron);

  // Se establece la ventana de busqueda
  calcularPosicionBusqueda(posX,posY,&origenVentanaX,&origenVentanaY);

  MpatSetPosition(patron, origenVentanaX,origenVentanaY,sizeBusquedaX, sizeBusquedaY);



  MpatSetAcceptance(patron, porcentajeValido);

  MpatAllocResult(M_DEFAULT, 1L, &PatResultId);
  MpatFindModel(ImagenID2, patron, PatResultId);
  MpatFree(patron);
  MpatGetResult(PatResultId, M_POSITION_X, &x);
  MpatGetResult(PatResultId, M_POSITION_Y, &y);

  MpatFree(PatResultId);

  }

  }
   *x2=(int)x;
  *y2=(int)y;

 }

//***************************************************
// ********* INTESIDAD MEDIA DE LA ZONA  ************
//***************************************************


int OpticalFlow::intensidadMedia(byte **matriz, int offX, int offY, int sizeX, int sizeY)
{



  int i,j;
  int x,y;
  int resultado = 0;

  for(i=0;i<=sizeX;i++){
        x = offX+i;
          for(j=0;j<=sizeY;j++){
                  y = offY+j;


                          resultado = resultado + matriz[y][x];


          }
  }

  resultado = resultado / (sizeX*sizeY);

  if(resultado>=18)
          return 1;
  else


  return -1;



}



//***************************************************
// ********* CALCULAR OPTICAL FLOW ******************
//***************************************************

void OpticalFlow::calcularOpticalFlow(TMatriz *matrizOptical,TImagen *img1,TImagen *img2){

  //Reinicio el contador de puntos de analisis
 numPuntosAnalisis = 0;



 int x2=0;
 int y2=0;





 // Matriz para comprobar las intensidades
 byte **matriz =img1->TImagen2RawBN();


  int difX=0,difY =0;
  int argX=0, argY=0;
  int cont = 0;
  float espacio = 0.0;
  maxEspacio = 0.0;

  float ptoInicialVel=0.0;
  float ptoFinalVel=0.0;

  int umbralLocal;

  for(int i=0;i<matrizOptical->getDimX();i++)
  {
  for(int j=0;j<matrizOptical->getDimY();j++)
        {


                // Con este IF consigo que se comprueben mas puntos en la zona de la carretera
                if(j>matrizOptical->getDimY()*0.7)
                        umbralLocal = umbralVelocidad;
                else
                        umbralLocal = umbral;


               if(matriz[j*matrizOptical->getDistanciaPuntos()][i*matrizOptical->getDistanciaPuntos()]>umbralLocal){
                       numPuntosAnalisis++;
                BuscarPatron(img1->ImagenID,img2->ImagenID, i*matrizOptical->getDistanciaPuntos(), j*matrizOptical->getDistanciaPuntos(), &x2, &y2);

                if (x2>0 || y2>0){
                        matrizOptical->setPunto(i,j,x2,y2);

                        cont = cont + 1;
                        
                        // Para la velocidad
                        if(j>=matrizOptical->getDimY()*0.7){



                             ptoInicialVel = j*matrizOptical->getDistanciaPuntos();
                             ptoInicialVel = (0.000188*ptoInicialVel*ptoInicialVel) - (0.21995*ptoInicialVel) + (69.143297);
                             ptoFinalVel = y2;
                             ptoFinalVel = (0.000188*ptoFinalVel*ptoFinalVel) - (0.21995*ptoFinalVel) + (69.143297);
                             
                             espacio =  ptoInicialVel - ptoFinalVel +0.1;

                             if(espacio>maxEspacio){
                                maxEspacio = espacio;
                             }



                        }


                        difX = x2-i*matrizOptical->getDistanciaPuntos();
                        difY = y2-j*matrizOptical->getDistanciaPuntos();

                        argX = argX + difX;
                        argY = argY + difY;

                }


           }


           }

}

 // Vector Velocidad
 if (cont>0){
 argX = -argX/cont;
 argY = -argY/cont;
 }
 numVectores = cont;

 vectorVelocidadX = (vectorVelocidadX + argX)/2;
 vectorVelocidadY = (vectorVelocidadY + argY)/2;


 delete []matriz[0];
 delete []matriz;


}




//***************************************************
// ********* CALCULAR ALTURA MAXIMA *****************
//***************************************************

void OpticalFlow::alturaMaxima(TMatriz *matriz1, int &h1, int &h2, int &x1, int &y1, int &x2, int &y2){

        int i,j;
        h1=0;
        h2=0;
        x1=0;
        y1=0;
        x2=0;
        y2=0;

        int altMax=0, x1Aux=0, y1Aux=0, x2Aux=0, y2Aux=0;
        int auxX1,auxY1,despX1,despY1,auxX2,auxY2,despX2,despY2;
        bool primero = true, haySegundo=false;

  for(int i=0;i<matriz1->getDimX();i++)
  {
  for(int j=0;j<matriz1->getDimY();j++)
        {

                if(matriz1->hayVector(i,j)){

                        if (primero){
                                primero = false;
                                x1Aux = i;
                                y1Aux = j;

                        }else{
                                x2Aux =  i;
                                y2Aux =  j;
                                haySegundo=true;
                        }


                }

          }
          primero = true;
          if (haySegundo){
          haySegundo=false;
          if (altMax< (y2Aux-y1Aux)){
                altMax = y2Aux - y1Aux;
                x1=x1Aux;
                x2=x2Aux;
                y1=y1Aux;
                y2=y2Aux;


                }
                }
        }


        h1 = altMax*distanciaPuntos;






        // 1� Aprox : Si no terminan en la misma columnas y estamos cometiendo un error!!!
        h2 = matriz1->getY(x2,y2) - matriz1->getY(x1,y1);
        x1=x1*9;
        y1=y1*9;
        x2=x2*9;
        y2=y2*9;




}



//***************************************************
// ********* FILTRO VECTORES LINEALES ***************
//***************************************************
void OpticalFlow::filtroVectoresLineales(TMatriz *matrizResultado, TMatriz *matriz1,TMatriz *matriz2){



int i,j;
int auxX, auxY;
int despX,despY;



  for(int i=0;i<matriz1->getDimX();i++)
  {
  for(int j=0;j<matriz1->getDimY();j++)
        {

                if(matriz1->hayVector(i,j)){

                        auxX = matriz1->getX(i,j)/distanciaPuntos;
                        despX = matriz1->getX(i,j)% distanciaPuntos;
                        if(despX>5)
                                auxX= auxX+1;

                        auxY = matriz1->getY(i,j)/distanciaPuntos;
                        despY = matriz1->getY(i,j)% distanciaPuntos;
                        if(despY>5)
                                auxY= auxY+1;

                        if(matriz2->hayVector(auxX,auxY)){
                                // Filtramos vectores en X de derecha a izquierda y de izquierda a dederecha
                                if(((i>matriz1->getX(i,j)/distanciaPuntos)&&(matriz1->getX(i,j)/distanciaPuntos>matriz2->getX(auxX,auxY)/distanciaPuntos))||((i<matriz1->getX(i,j)/distanciaPuntos)&&(matriz1->getX(i,j)/distanciaPuntos<matriz2->getX(auxX,auxY)/distanciaPuntos))){
                                        // Filtramos vectores en Y de arriba a abajo y de abajo a arriba
                                        if(((j<matriz1->getY(i,j)/distanciaPuntos)&&(matriz1->getY(i,j)/distanciaPuntos<matriz2->getY(auxX,auxY)/distanciaPuntos))||((j>matriz1->getY(i,j)/distanciaPuntos)&&(matriz1->getY(i,j)/distanciaPuntos>matriz2->getY(auxX,auxY)/distanciaPuntos))){
                                               matrizResultado->setPunto(i,j,matriz1->getX(i,j),matriz1->getY(i,j));


                                        }
                                }


                        }


                }



          }
         }


}



//***************************************************
// ********* CALCULAR DISTANCIA *********************
//***************************************************
void OpticalFlow::calcularDistancia(int h1,int h2, float foco, float velocidad, float tiempo, float &h, float &d){

h=0.0;
d=0.0;
float h1mm=h1*0.0233;
float h2mm=h2*0.0233;

float velocidadAux = (velocidad * 1000)/3.6;


if ((h1mm-h2mm)<0)
d=-(velocidadAux*tiempo*h2mm)/(h1mm-h2mm);
h=(d*h1mm)/foco;

h=h/1000;
 
d=d/1000;

}


//***************************************************
// ********* LECTURA DE FICHERO DE CONFIGURACION ****
//***************************************************

void OpticalFlow::lecturaFicheroConfiguracion(){
char str[256];
AnsiString linea;
AnsiString var;

ifstream fin("config.dat");
if(fin.is_open()){
while (!fin.eof()){

fin.getline(str,100);
linea=(AnsiString) str;

var="COEFICIENTE_VENTANA_MAX=";
if (linea.SubString(0,var.Length())==var)
coeficienteVentanaMax = (float) linea.SubString(var.Length()+1,linea.Length()).ToDouble();
var="COEFICIENTE_VENTANA_MIN=";
if (linea.SubString(0,var.Length())==var)
coeficienteVentanaMin = (float) linea.SubString(var.Length()+1,linea.Length()).ToDouble();
var="COEFICIENTE_PATRON=";
if (linea.SubString(0,var.Length())==var)
coeficientePatron = (float) linea.SubString(var.Length()+1,linea.Length()).ToDouble();
var="UMBRAL=";
if (linea.SubString(0,var.Length())==var)
umbral = linea.SubString(var.Length()+1,linea.Length()).ToInt();
var="ESPACIO_ENTRE_VECTORES=";
if (linea.SubString(0,var.Length())==var)
distanciaPuntos = linea.SubString(var.Length()+1,linea.Length()).ToInt();
var="PORCENTAJE_VALIDO=";
if (linea.SubString(0,var.Length())==var)
porcentajeValido = (float) linea.SubString(var.Length()+1,linea.Length()).ToDouble();



}
}




}



