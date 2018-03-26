#include "imagen.h"
#include <fstream>

int formas(Imagen &I,Imagen &forma)
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
      resultado=1;
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

    //Franjas centrales verticales
    Imagen i5(I.num_filas()/2+I.num_filas()%2,(forma.num_cols()*2)-2);
    Imagen i6(I.num_filas()/2,(forma.num_cols()*2)-2);

    //Franjas centrales horizontales
    Imagen i7((forma.num_filas()*2)-2,I.num_cols()/2+I.num_cols()%2);
    Imagen i8((forma.num_filas()*2)-2,I.num_cols()/2);

    /*pongo en los nuevos cuadrantes el estracto deseado de la original*/

    i1.PutImagen();
    i2.PutImagen();
    i3.PutImagen();
    i4.PutImagen();
    i5.PutImagen();
    i6.PutImagen();
    i7.PutImagen();
    i8.PutImagen();

    int num_cuad_1=formas(i1,forma);
    int num_cuad_2=formas(i2,forma);
    int num_cuad_3=formas(i3,forma);
    int num_cuad_4=formas(i4,forma);
    int num_cuad_5=formas(i5,forma);
    int num_cuad_6=formas(i6,forma);
    int num_cuad_7=formas(i7,forma);
    int num_cuad_8=formas(i8,forma);

    resultado=num_cuad_1+num_cuad_2+num_cuad_3+num_cuad_4+num_cuad_5+num_cuad_6+num_cuad_7+num_cuad_8;
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

  /*Imagen i1(I.num_filas()/2+I.num_filas()%2,I.num_cols()/2+I.num_cols()%2);
  i1.PutImagen(50,50,I);
  i1.EscribirImagen("resultado");*/
  
  //Vuestro codigo para implementar la funcion que busca la forma en I
  
  int num_formas=formas(I,forma);

  cout<<"El numero de ocurrencias de la forma buscada es: "<<num_formas<<endl;

}