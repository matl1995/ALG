#include "imagen.h"
#include <fstream>




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
  
  //Vuestro codigo para implementar la funcion que busca la forma en I
  
  
  
}