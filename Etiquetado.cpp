#include "Etiquetado.h"




//***************************************************
//*********** CONSTRUCTOR ***************************
//***************************************************
Etiquetado::Etiquetado() {

// INICIALIZO LOS DOS PUNTOS DE LA ZONA INICIAL
 zonaInicial.x1 = 0;
 zonaInicial.y1 = 0;
 zonaInicial.x2 = 0;
 zonaInicial.y2 = 0;

// INICIALIZO LOS DOS PUNTOS DE LA ZONA FINAL 
 zonaFinal.x1 = 0;
 zonaFinal.y1 = 0;
 zonaFinal.x2 = 0;
 zonaFinal.y2 = 0;

// INICIALIZO ULTIMA ETIQUETA

 ultimaEtiqueta = 0;


// CREO LAS LISTAS DE LOS ARRAYS
listaAnterior = new TListaEtiquetas();
listaNueva = new TListaEtiquetas();

// INICIALIZO EL NUMERO DE OBJETOS ENCONTRADOS EN LA ULTIMA IMAGEN
hayObjetos = false;

}


//***************************************************
//*********** DESTRUCTOR ****************************
//***************************************************
Etiquetado::~Etiquetado() {

}

//***************************************************
//**** METODOS DE LECTURA Y ESCRITURA ATRIBUTOS******
//***************************************************

TListaEtiquetas* Etiquetado::getListaAnterior(){
 return this->listaAnterior;
}



//***************************************************
//*********** HAY OBJETOS ENCONTRADOS ***************
//***************************************************
bool Etiquetado::hayObjetosEncontrados(){
        return hayObjetos;
}


//***************************************************
//*********** CREAR ZONA OBJETO *********************
//***************************************************

void Etiquetado::crearZonaObjeto(int x1,int y1,int x2,int y2){

 zonaInicial.x1 = x1;
 zonaInicial.y1 = y1;
 zonaInicial.x2 = x2;
 zonaInicial.y2 = y2;

}


//***************************************************
//*********** ESTIMAR PUNTO FUTURO ******************
//***************************************************
void Etiquetado::estimarPuntoFuturo(TMatriz *matrizOptical,int x1,int y1, int *x2, int *y2){

 int i=0,j=0;
 int d = matrizOptical->getDistanciaPuntos();
 int cont = 0;
 int argX = 0;
 int argY = 0;
 // CALCULO LOS TAMAÑOS DE LOS VECTORES DEL OPTICAL FLOW
 for(i=(x1/d)-5;i<(x1/d)+5;i++){
        for(j=(y1/d)-5;j<(y1/d)+5;j++){
              if((i>0)&&(i<matrizOptical->getDimX())&&(j>0)&&(j<matrizOptical->getDimY())){

              if(matrizOptical->hayVector(i,j)){
                cont = cont + 1;
                argX = argX + matrizOptical->getX(i,j) - i*d;
                argY = argY + matrizOptical->getY(i,j) - j*d;
              }
              }
        }
 }
 // REALIZO LA MEDIA DE TODOS LOS TAMAÑOS ENCONTRADOS
 if (cont != 0){
         *x2=(int)(argX/cont);
         *y2=(int)(argY/cont);
 }else{
         *x2=(int)0;
         *y2=(int)0;
 }

}



//***************************************************
//*********** ESTIMAR ZONA FUTURA *******************
//***************************************************
bool Etiquetado::estimarZonaFutura(TMatriz *matrizOptical){

 int x1Estimado = 0;
 int y1Estimado = 0;
 int x2Estimado = 0;
 int y2Estimado = 0;
 bool punto1Encontrado = false;
 bool punto2Encontrado = false;

 estimarPuntoFuturo(matrizOptical,zonaInicial.x1,zonaInicial.y1,&x1Estimado,&y1Estimado);
 
 if ((x1Estimado!=0)&&(y1Estimado!=0)){
        punto1Encontrado = true;
        zonaFinal.x1 = zonaInicial.x1 + x1Estimado;
        zonaFinal.y1 = zonaInicial.y1 + y1Estimado;


 }



 estimarPuntoFuturo(matrizOptical,zonaInicial.x2,zonaInicial.y2,&x2Estimado,&y2Estimado);

 if ((x2Estimado!=0)&&(y2Estimado!=0)){
         punto2Encontrado = true;
         zonaFinal.x2 = zonaInicial.x2 + x2Estimado;
         zonaFinal.y2 = zonaInicial.y2 + y2Estimado;


 }

 if(!punto1Encontrado && punto2Encontrado){
        zonaFinal.x1 = zonaInicial.x1 + x2Estimado;
        zonaFinal.y1 = zonaInicial.y1 + y2Estimado;
        
 }else if(punto1Encontrado && !punto2Encontrado){
        zonaFinal.x2 = zonaInicial.x2 + x1Estimado;
        zonaFinal.y2 = zonaInicial.y2 + y1Estimado;
 }


 if(!punto1Encontrado && !punto2Encontrado){
        zonaFinal.x1 = zonaInicial.x1;
        zonaFinal.y1 = zonaInicial.y1;
        zonaFinal.x2 = zonaInicial.x2;
        zonaFinal.y2 = zonaInicial.y2;
 }
 // AUMENTO LA ZONA FINAL PARA CORREGIR POSIBLES ERRORES

        zonaFinal.x1 = zonaFinal.x1 - 20;
        zonaFinal.y1 = zonaFinal.y1 - 20;
        zonaFinal.x2 = zonaFinal.x2 + 20;
        zonaFinal.y2 = zonaFinal.y2 + 20;


 return (punto1Encontrado && punto2Encontrado);
}




//***************************************************
//*********** LEECTURA LISTA OBJETOS ****************
//***************************************************
void Etiquetado::lecturaListaObjetos(int imagenActual,TMatriz *matrizOptical,TMemo *Consola){

 AnsiString idImagen = "img\\" + (AnsiString)imagenActual + ".dat";

 int x1,y1,x2,y2;
  

 char str[256];
 AnsiString linea,parametro;

 // COMPRUEBO SI EXISTE EL ARCHIVO

 if(FileExists(idImagen)){
 
        ifstream fin(idImagen.c_str());

        if(fin.is_open()){
    
                while (!fin.eof()){
                        fin.getline(str,100);
                        linea = (AnsiString)str;
                        try{
                        // LEO LAS COORDEDAS DEL OBJETO
                        x1 = linea.SubString(0,3).ToInt();
                        y1 = linea.SubString(4,4).ToInt();
                        x2 = linea.SubString(8,4).ToInt();
                        y2 = linea.SubString(12,4).ToInt();

                       
                                                       
                        crearZonaObjeto(x1,y1,x2,y2);
                        estimarZonaFutura(matrizOptical);

                        // INSERTO ELEMENTO DIRECTAMENTE SIN ETIQUETA

                        listaNueva->insertar(zonaInicial.x1,zonaInicial.y1,zonaInicial.x2,zonaInicial.y2,zonaFinal.x1,zonaFinal.y1,zonaFinal.x2,zonaFinal.y2,"vacio");
                        
                        }catch(...){
                            // Si se produce algun error no hago nada, procedo con el siguiente objeto
                        }
                      

                        
                }
                fin.close();
        }
 }

 if(listaNueva->getNumElem()>0){
        hayObjetos = true;
 }else{
        hayObjetos = false;
 }

 

}


//***************************************************
//*********** ASIGNAR ETIQUETAS *********************
//***************************************************
void Etiquetado::asignarEtiquetas(TMemo *Consola){

 bool encontrado = false;


 if(listaAnterior->getNumElem()==0){
        for(int i=0;i<listaNueva->getNumElem();i++){
                ultimaEtiqueta++;
                listaNueva->setEtiqueta(i,"Obj-"+(AnsiString)ultimaEtiqueta);
        }
 }else{
        for(int i=0;i<listaNueva->getNumElem();i++){
                for(int j=0;j<listaAnterior->getNumElem();j++){

                         if(listaNueva->coincidePrediccion(listaNueva->getX1Inicial(i),listaNueva->getY1Inicial(i),listaNueva->getX2Inicial(i),listaNueva->getY2Inicial(i),listaAnterior->getX1Final(j),listaAnterior->getY1Final(j),listaAnterior->getX2Final(j),listaAnterior->getY2Final(j))){
                                listaNueva->setEtiqueta(i,listaAnterior->getEtiqueta(j));
                                encontrado = true;
                         }
                         


                }
                if(!encontrado){
                        ultimaEtiqueta++;
                        listaNueva->setEtiqueta(i,"Obj-"+(AnsiString)ultimaEtiqueta);

                }else{
                        encontrado = false;
                }
        }
 }


  
 listaAnterior->copiarLista(listaNueva); 
 listaNueva->setNumElem(0);






}


//***************************************************
//*********** ACTUALIZAR REGISTRO ETIQUETAS *********
//***************************************************
void Etiquetado::actualizarRegistroEtiquetas(int idImagen){
 AnsiString imagen = (AnsiString)idImagen + ".bmp";
 AnsiString nombreArchivo = "registroEtiquetas.dat";

 char str[256];
 
 AnsiString linea;

 // DECLARO EL OBJETO ARCHIVO Y LO ABRO EN MODO APPEND
 ofstream fon(nombreArchivo.c_str(),ofstream::app);
 
 
 fon<<"Imagen: "<<imagen<<"\n";
 fon<<"====================================================="<<"\n\n";
 fon<<"Etiqueta   Posicion Inicial       Posicion Futura"<<"\n";

 for(int i=0;i<listaAnterior->getNumElem();i++){
        fon<<listaAnterior->getEtiqueta(i);
        fon<<"      ("<<listaAnterior->getX1Inicial(i)<<","<<listaAnterior->getY1Inicial(i)<<")-("<<listaAnterior->getX2Inicial(i)<<","<<listaAnterior->getY2Inicial(i)<<")";
        fon<<"    ("<<listaAnterior->getX1Final(i)<<","<<listaAnterior->getY1Final(i)<<")-("<<listaAnterior->getX2Final(i)<<","<<listaAnterior->getY2Final(i)<<")";

        fon<<"\n\n";

 }
  fon<<"====================================================="<<"\n";

  fon.close();

}

