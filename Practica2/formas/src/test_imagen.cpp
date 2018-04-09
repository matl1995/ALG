#include "imagen.h"
#include <fstream>

int CuantasFormas(Imagen &I,Imagen &forma,int inicio_i,int inicio_j,int tam,Imagen &mask)
{
  int resultado;

  if(I.num_filas()<forma.num_filas() || I.num_cols()<forma.num_cols())
  {
    resultado=0;
  }
  else if(I.num_filas()==forma.num_filas() && I.num_cols()==forma.num_cols())
  {
    bool coincide=true;

    for(int i=0;i<I.num_filas();i++)
    {
      for(int j=0;j<I.num_cols();j++)
      {
        if(I(i,j)!=forma(i,j))
          coincide=false;
      }
    }

    if(!coincide)
      resultado=0;
    else
    {
      resultado=1;

      //Establezco los valores de la mascara a 1
      for(int i=0;i<mask.num_filas();i++)
      {
        for(int j=0;j<mask.num_cols();j++)
        {
          mask(i,j)='255';
        }
      }
    }
  }
  else
  {
    /*Creo las imagenes de los subcuadrantes a inspeccionar y de las zonas cerca del eje*/

    //Cuadrantes superiores
    Imagen i1(I.num_filas()/2+I.num_filas()%2,I.num_cols()/2+I.num_cols()%2);
    Imagen i2(I.num_filas()/2+I.num_filas()%2,I.num_cols()/2);

    //Cuadrantes inferiores
    Imagen i3(I.num_filas()/2,I.num_cols()/2+I.num_cols()%2);
    Imagen i4(I.num_filas()/2,I.num_cols()/2);

    /*pongo en los nuevos cuadrantes el estracto deseado de la original*/

    i1.PutImagen(0,0,I);
    
    for(int i=0;i<i2.num_filas();i++)
    {
    	for(int j=0;j<i2.num_cols();j++)
    	{
    		i2(i,j)=I(i+I.num_filas()/2+I.num_filas()%2,j);
    	}
    }

    for(int i=0;i<i3.num_filas();i++)
    {
    	for(int j=0;j<i3.num_cols();j++)
    	{
    		i3(i,j)=I(i,j+I.num_cols()/2+I.num_cols()%2);
    	}
    }

    for(int i=0;i<i4.num_filas();i++)
    {
    	for(int j=0;j<i4.num_cols();j++)
    	{
    		i4(i,j)=I(i+I.num_filas()/2,j+I.num_cols()/2);
    	}
    }

    int num_cuad_1=formas(i1,forma);
    int num_cuad_2=formas(i2,forma);
    int num_cuad_3=formas(i3,forma);
    int num_cuad_4=formas(i4,forma);

    /*Ahora compruebo en la franjas alrededor de los limites entre subcuadrantes*/
    bool coincide;

    int num_franja_h=0;
    //Fraja horizontal
    for(int i=(I.num_filas()/2)-forma.num_filas();i<I.num_filas()/2;i++)
    {
    	for(int j=0;j<I.num_cols();j++)
    	{
    		coincide=true;
    		for(int l=0;l<forma.num_filas();l++)
    		{
    			for(int m=0;m<forma.num_cols();m++)
    			{
    				if(I(i+l,j+m)!=forma(l,m))
          		coincide=false;
    			}
    		}
    		if(coincide)
		      num_franja_h+=1;
    	}
    }

    int num_franja_v=0;
    //Fraja vertical
    for(int i=0;i<I.num_filas();i++)
    {
    	for(int j=(I.num_cols()/2)-forma.num_cols();j<I.num_cols()/2;j++)
    	{
    		coincide=true;
    		for(int l=0;l<forma.num_filas();l++)
    		{
    			for(int m=0;m<forma.num_cols();m++)
    			{
    				if(I(i+l,j+m)!=forma(l,m))
          		coincide=false;
    			}
    		}
    		if(coincide)
		      num_franja_v+=1;
    	}
    }

    resultado=num_cuad_1+num_cuad_2+num_cuad_3+num_cuad_4+num_franja_h+num_franja_h;
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

  //Genero la imagen máscara
  Imagen mask(I.num_filas(),I.num_cols());

  //Inicializo a 0 la matriz mascara
  for(int i=0;i<mask.num_filas();i++)
  {
    for(int j=0;j<mask.num_cols();j++)
    {
      mask(i,j)='0';
    }
  }
  
  //Llamo a la función que contabiliza el número de formas  
  int num_formas=CuantasFormas(I,forma,0,0,I.num_filas(),mask);

  //Imprimo por pantalla el numero de veces que aparece la forma buscada
  cout<<"El numero de ocurrencias de la forma buscada es: "<<num_formas<<endl;
}