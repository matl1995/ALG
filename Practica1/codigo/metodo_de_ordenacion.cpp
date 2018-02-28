#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void seleccion(const int *v, int n)
{
	int min, pos_min, intercambia;

	for(int izda = 0; izda < n; izda++){
		min = v[izda];
		pos_min = izda;

		for(int i = izda + 1; i < n; i++){
			if(v[i] < min){
				min = v[i];
				pos_min = i;
			}
		}

		intercambia = v[izda];
		v[izda] = v[pos_min];
		v[pos_min] = intercambia;
	}
}


void insercion(const int *v, int n)
{
	int a_desplazar;

	for (int izda = 1; izda < n; izda++){
		a_desplazar = v[izda];

		for (i = izda; i > 0 && a_desplazar < v[i-1]; i--)
			v[i] = v[i-1];

		v[i] = a_desplazar;
	}
}


void burbuja(const int *v, int n)
{
	bool cambio;
	int intercambia;

	cambio = true;

	for (int izda = 0; izda < n && cambio; izda++){
		cambio = false;
		for (int i = n-1; i > izda; i--){
			if(v[i] < v[i-1]){
				cambio = true;
				intercambia = v[i];
				v[i] = v[i-1];
				v[i-1] = intercambia;
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
  int metodo=atoi(argv[2]);    // Método de ordenación a usar
  if (tam<=0 || vmax<=0)
    sintaxis();
  
  // Generación del vector aleatorio
  int *v=new int[tam];       // Reserva de memoria
  srand(time(0));            // Inicialización del generador de números pseudoaleatorios
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = rand() % vmax;    // Generar aleatorio [0,vmax[
  
 high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start
  
 start = high_resolution_clock::now(); //iniciamos el punto de inicio
 
  int x = vmax+1;  // Buscamos un valor que no está en el vector
  buscar(v,tam,x); // de esta forma forzamos el peor caso
  
 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

  // Mostramos resultados
  cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
  delete [] v;     // Liberamos memoria dinámica
}
