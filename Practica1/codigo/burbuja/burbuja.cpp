#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void burbuja(int *v, int n)
{
	int temp;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=n-i;j++)
		{
			if (v[j]>v[j+1])
			{
				temp=v[j];
				v[j]=v[j+1];
				v[j+1]=temp;
			}
		}
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
  burbuja(v,tam); // de esta forma forzamos el peor caso
  
 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);
/*
 //Mostrar el vector
 for(int i=0;i<tam;i++)
 {
  cout<<v[i]<<" ";
 }
 cout<<endl;
*/
  // Mostramos resultados
  cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
  delete [] v;     // Liberamos memoria dinámica
}