#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void seleccion(int *v, int n)
{
  int posicion_minimo,temp;

  for(int i=0;i<n-1;i++)
  {
    posicion_minimo=i;

    for(int j=i+1;j<n;j++){
      if(v[j]<v[posicion_minimo])
      {
        posicion_minimo=j;
      }
    }

    temp=v[i];
    v[i]=v[posicion_minimo];
    v[posicion_minimo]=temp;
  }
}

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
  // Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=atoi(argv[2]);    // Valor máximo
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
  
 high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start
  
 start = high_resolution_clock::now(); //iniciamos el punto de inicio
 
  //int x = vmax+1;  // Buscamos un valor que no está en el vector
  seleccion(v,tam); // de esta forma forzamos el peor caso
  
 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

 //Mostrar el vector
 /*for(int i=0;i<tam;i++)
 {
  cout<<v[i]<<" ";
 }
 cout<<endl;*/

  // Mostramos resultados
  cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
  delete [] v;     // Liberamos memoria dinámica
}