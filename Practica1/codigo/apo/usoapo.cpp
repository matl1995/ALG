#include "apo.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){

// Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=tam;    // Valor máximo
  if (tam<=0 || vmax<=0)
    sintaxis();

// Generación del vector caso peor
  int *v=new int[tam];       // Reserva de memoria
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = i;

 APO<int>ap_int;
 
 high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start
  
 start = high_resolution_clock::now(); //iniciamos el punto de inicio

 for (int i=0;i<tam;i++){
	   ap_int.insertar(v[i]);
 }
 
 for(int i=0;i<tam;i++)
 {
 	ap_int.minimo();
 	ap_int.borrar_minimo();
 }

 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

 // Mostramos resultados
 cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
 delete [] v;     // Liberamos memoria dinámica
 
}