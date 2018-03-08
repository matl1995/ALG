#include <iostream>
#include "permutacion.h"
#include <string> 
#include <chrono>// Recursos para medir tiempos
using namespace std::chrono;

template <class T>
ostream & operator<<(ostream &os, const vector<T> & d){
   for (int i=0;i<d.size();i++)
      os<<d[i]<<" ";
   os<<endl;
   return os;
}

void MuestraPermutaciones(const Permutacion & P){
  Permutacion::const_iterator it;
  int cnt=1;
  for (it=P.begin();it!=P.end();++it,++cnt)
      cout<<cnt<<"->"<<*it<<endl;
      
}


void ImprimeCadena(const string &c,const Permutacion &P){
  const vector<unsigned int> s= (*(P.begin()));
  
  for (unsigned int i=0;i<s.size();i++)
     cout<<c[s[i]-1];
  cout<<endl;
}

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){
  /*
  int n;
  cout<<"Dime el tamaño de las permutaciones:";
  cin>>n;
  
  Permutacion P(n);
  cout<<"El numero total de permutaciones: "<<P.NumeroPermutacionesPosibles()<<endl;
  MuestraPermutaciones(P);
  */

  // Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=100;    // Valor máximo
  if (tam<=0 || vmax<=0)
    sintaxis();

  /*
  // Generación del vector aleatorio
  int *v=new int[tam];       // Reserva de memoria
  srand(time(0));            // Inicialización del generador de números pseudoaleatorios
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = rand() % vmax;    // Generar aleatorio [0,vmax[
*/

/*
 // Generación del vector caso peor
  int *v=new int[tam];       // Reserva de memoria
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = tam-i;
*/


// Generación del vector caso mejor
  int *v=new int[tam];       // Reserva de memoria
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = i;


  Permutacion P(tam);
  bool ordenado=false;
  bool primeravez=true;

  //Para no tener almacenadas todas las permutaciones solo la acutal
  
  high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end               // y start
  
 start = high_resolution_clock::now(); //iniciamos el punto de inicio

 while(ordenado==false)
 {
    ordenado=true;

    if(primeravez==false)
      P.GeneraSiguiente(); //Genero la permutacion siguiente
    else
      primeravez=false;

    vector<unsigned int> perm=*P.begin();
    for(unsigned int i=1;i<perm.size() && ordenado;i++)
    {
      if(v[perm[i-1]-1]>v[perm[i]-1])
      {
        ordenado=false;
      }
    } 
 }

 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

 // Mostramos resultados
 cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
 delete [] v;     // Liberamos memoria dinámica
  
  /*
  //Leemos una cadena y generamos todas sus permutaciones
  string cad;
  cout<<"Dime una palabra:";
  cin>>cad;
  Permutacion Otra(cad.size(),1);
  int cnt=1;
  do{
    cout<<cnt<<"-->";
    ImprimeCadena(cad,Otra);
    cnt++;
  }while(Otra.GeneraSiguiente());
  */
}  
  
  
   
  
