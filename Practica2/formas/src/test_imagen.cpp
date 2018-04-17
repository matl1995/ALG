#include "imagen.h"
#include <fstream>

int ComprobarForma(Imagen &I,Imagen &forma,int inicio_i,int inicio_j,int **mask)
{
    int resultado;
    bool coincide=true;
    bool ya_contada=true;
    bool dentro=true; //Variable para que no se acceda a posiciones fuera de las imagenes

    //cout<<"Compruebo imagen"<<endl;
    //Comprobamos si coincide la zona de la imagen con la forma
    for(int i=0;i<forma.num_filas() && dentro;i++)
    {
      for(int j=0;j<forma.num_cols() && dentro;j++)
      {
        //cout<<"Comprobando posicion: "<<i<<" "<<j<<" con indices: "<<inicio_i<<" y "<<inicio_j<<endl;
        
        if(inicio_i+i<0 || inicio_i+i>=I.num_filas() || inicio_j+j<0 || inicio_j+j>=I.num_cols())
          dentro=false;

        if(dentro)
        {
          if(I(inicio_i+i,inicio_j+j)!=forma(i,j))
            coincide=false;

          if(mask[inicio_i+i][inicio_j+j]==0)
            ya_contada=false;
        }
      }
    }

    if(!coincide || !dentro) //Si no coincide devolvemos un 0
      resultado=0;
  	else if(coincide && ya_contada && dentro)
  		resultado=0;
    else if(coincide && !ya_contada && dentro) //En caso de que si marcamos en la mascara para no volver a contabilizarla
    {
      resultado=1;

      //Establezco los valores de la mascara a 1
      for(int i=0;i<forma.num_filas();i++)
      {
        for(int j=0;j<forma.num_cols();j++)
        {
          mask[inicio_i+i][inicio_j+j]=255;
        }
      }
    }

    return resultado;
}

int CuantasFormas(Imagen &I,Imagen &forma,int inicio_i,int inicio_j,int tam_f,int tam_c,int **mask)
{
  int resultado;

  //cout<<"Filas: "<<tam_f<<" , columnas: "<<tam_c<<endl;

  if(tam_f<forma.num_filas() || tam_c<forma.num_cols())
  {
    //cout<<"Caso 0"<<endl;
    resultado=0;
  }
  else if(tam_f==forma.num_filas() && tam_c==forma.num_cols())
  {
    //cout<<"Caso 1"<<endl;
    resultado=ComprobarForma(I,forma,inicio_i,inicio_j,mask);
  }
  else
  {
    //Hago las recurrencias de los cuatro cuadrantes
    int n1=CuantasFormas(I,forma,inicio_i,inicio_j,tam_f/2,tam_c/2,mask);

    int n2=CuantasFormas(I,forma,inicio_i,inicio_j+tam_c/2,tam_f/2,tam_c/2,mask);

    int n3=CuantasFormas(I,forma,inicio_i+tam_f/2,inicio_j,tam_f/2,tam_c/2,mask);

    int n4=CuantasFormas(I,forma,inicio_i+tam_f/2,inicio_j+tam_c/2,tam_f/2,tam_c/2,mask);

    int n5=0;

    int n6=0;

    //cout<<"Comprobacion franja horizontal"<<endl;
    //Compruebo la franja horizontal
    for(int i=1;i<forma.num_filas();i++)
    {
      for(int j=0;j<=tam_c-forma.num_cols();j++)
      {
        //cout<<"Iteracion i: "<<i<<" , j: "<<j<<endl;
        resultado+=ComprobarForma(I,forma,inicio_i+tam_f/2-i,inicio_j+j,mask);
      }
    }
    //cout<<"Comprobacion franja vertical"<<endl;
    //Compruebo la franja vertical
    for(int j=1;j<forma.num_cols();j++)
    {
      for(int i=0;i<=tam_f-forma.num_filas();i++)
      {
        //cout<<"Iteracion i: "<<i<<" , j: "<<j<<endl;
        resultado+=ComprobarForma(I,forma,inicio_i+i,inicio_j+tam_c/2-j,mask);
      }
    }

    resultado=n1+n2+n3+n4+n5+n6;
  }

  return resultado;
}

int main(int argc, char * argv[]){
  if (argc!=3){
      cout<<"Los parametros son: ";
     cout<<"1.-Dime el nombre de una imagen"<<endl;
     cout<<"2.-Dime el nombre de una forma"<<endl;
     return 0;
  }   
  
  Imagen I,forma;
  I.LeerImagen(argv[1]);
  forma.LeerImagen(argv[2]);

  //Reservo la memoria para la mascara
  int **mask=new int*[I.num_filas()];
  for(int i=0;i<I.num_filas();i++)
  {
      mask[i]=new int[I.num_cols()];
  }
  
  //Relleno la mascara
  for (int i=0;i<I.num_filas();i++)  // Recorrer vector
  {
    for(int j=0;j<I.num_cols();j++)
    {
      mask[i][j]=0;    // Generar aleatorio [0,tam]
    }
  }
  cout<<"Datos recibidos"<<endl;
  //Llamo a la función que contabiliza el número de formas  
  int num_formas=CuantasFormas(I,forma,0,0,I.num_filas(),I.num_cols(),mask);

  //Imprimo por pantalla el numero de veces que aparece la forma buscada
  cout<<"El numero de ocurrencias de la forma buscada es: "<<num_formas<<endl;
}