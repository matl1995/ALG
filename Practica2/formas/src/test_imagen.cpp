#include "imagen.h"
#include <fstream>

int CuantasFormas(Imagen &I,Imagen &forma,int inicio_i,int inicio_j,int tam_f,int tam_c,int **mask)
{
  int resultado;

  if(tam_f<forma.num_filas() || tam_c<forma.num_cols())
  {
    resultado=0;
  }
  else if(tam_f==forma.num_filas() && tam_c==forma.num_cols())
  {
    bool coincide=true;
    bool ya_contada=true;

    for(int i=inicio_i;i<tam_f;i++)
    {
      for(int j=inicio_j;j<tam_c;j++)
      {
        if(I(i,j)!=forma(i,j))
          coincide=false;

        if(mask[i][j]==0)
          ya_contada=false;
      }
    }

    if(!coincide)
      resultado=0;
    else if(coincide && !ya_contada)
    {
      resultado=1;

      //Establezco los valores de la mascara a 1
      for(int i=inicio_i;i<tam_f;i++)
      {
        for(int j=inicio_j;j<tam_c;j++)
        {
          mask[i][j]=255;
        }
      }
    }
  }
  else
  {
    //Hago las recurrencias de los cuatro cuadrantes
    int n1=CuantasFormas(I,forma,inicio_i,inicio_j,tam_f/2,tam_c/2,mask);

    int n2=CuantasFormas(I,forma,inicio_i,inicio_j+tam_c/2,tam_f/2,tam_c/2,mask);

    int n3=CuantasFormas(I,forma,inicio_i+tam_f/2,inicio_j,tam_f/2,tam_c/2,mask);

    int n4=CuantasFormas(I,forma,inicio_i+tam_f/2,inicio_j+tam_c/2,tam_f/2,tam_c/2,mask);

    //Hago las recurrencias de la franja horizontal
    int n5=CuantasFormas(I,forma,inicio_i+tam_f/2-forma.num_filas()+1,inicio_j,(forma.num_filas()*2)-2,tam_c/2,mask);

    int n6=CuantasFormas(I,forma,inicio_i+tam_f/2-forma.num_filas()+1,inicio_j+tam_c/2,(forma.num_filas()*2)-2,tam_c/2,mask);

    //Hago las recurrencias de la franja vertical
    int n7=CuantasFormas(I,forma,inicio_i,inicio_j+tam_c/2-forma.num_cols()+1,tam_f/2,(forma.num_cols()*2)-2,mask);

    int n8=CuantasFormas(I,forma,inicio_i+tam_f/2,inicio_j+tam_c/2-forma.num_cols()+1,tam_f/2,(forma.num_cols()*2)-2,mask);

    resultado=n1+n2+n3+n4+n5+n6+n7+n8;
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
  
  //Llamo a la función que contabiliza el número de formas  
  int num_formas=CuantasFormas(I,forma,0,0,I.num_filas(),I.num_cols(),mask);

  //Imprimo por pantalla el numero de veces que aparece la forma buscada
  cout<<"El numero de ocurrencias de la forma buscada es: "<<num_formas<<endl;
}