/**
   @file Ordenación por mezcla
*/

#include <string>    
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>// Recursos para medir tiempos
using namespace std::chrono;



/* ************************************************************ */ 
/*  MÈtodo de ordenación por mezcla  */

/**
   @brief Ordena un vector por el método de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static 
void mergesort(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de mezcla.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(int T[], int inicial, int final);


/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static 
void insercion(int T[], int num_elem);


/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserción.
*/
static void insercion_lims(int T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posiciún que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(int T[], int inicial, int final, int U[], int V[]);



/**
   Implementación de las funciones
**/


inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_MS = 100;

void mergesort(int T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(int T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      int * U = new int [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
	U[l] = T[l2];
      U[l] = INT_MAX;

      int * V = new int [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
	V[l] = T[l2];
      V[l] = INT_MAX;

      mergesort_lims(U, 0, k);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}
  

static void fusion(int T[], int inicial, int final, int U[], int V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
}





int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      std::cout << "Formato " << argv[0] << " <num_elem>" << std::endl;
      return -1;
    }

  int n = atoi(argv[1]);

  int * T = new int[n];
  assert(T);

  srandom(time(0));
/*
  //Caso promedio
  for (int i=0;i<n;i++)
    {
      T[i]=random();
    };
*//*
  //Caso peor
  for (int i=0;i<n;i++)
    {
      T[i]=n-i;
    };
*/
  //Caso mejor
  for (int i=0;i<n;i++)
    {
      T[i]=i;
    };


  const int TAM_GRANDE = 10000;
  const int NUM_VECES = 1000;

  if (n > TAM_GRANDE)
    {
    	high_resolution_clock::time_point t_antes,//punto de inicio
                                  t_despues; //punto de fin
 		duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end               // y start
  
 		t_antes = high_resolution_clock::now(); //iniciamos el punto de inicio
      
      mergesort(T, n);
      
          t_despues = high_resolution_clock::now(); //anotamos el punto de de fin 
		 //el tiempo transcurrido es
		 tiempo_transcurrido  = duration_cast<duration<double> >(t_despues - t_antes);

		 // Mostramos resultados
		 std::cout << n << "\t" <<tiempo_transcurrido.count() << std::endl;
    } else {
      int * U = new int[n];
      assert(U);

      for (int i = 0; i < n; i++)
		U[i] = T[i];
      
      	high_resolution_clock::time_point t_antes_vacio,//punto de inicio
                                  t_despues_vacio; //punto de fin
 		t_antes_vacio = high_resolution_clock::now(); //iniciamos el punto de inicio

      for (int veces = 0; veces < NUM_VECES; veces++)
		{
	  		for (int i = 0; i < n; i++)
	    		U[i] = T[i];
		}

		 t_despues_vacio = high_resolution_clock::now(); //anotamos el punto de de fin 

      	high_resolution_clock::time_point t_antes,//punto de inicio
                                  t_despues; //punto de fin
 		duration<double> tiempo_transcurrido1;  //objeto para medir la duracion de end               // y start
 		t_antes = high_resolution_clock::now(); //iniciamos el punto de inicio

      for (int veces = 0; veces < NUM_VECES; veces++)
		{
	  		for (int i = 0; i < n; i++)
	    		U[i] = T[i];

	  		mergesort(U, n);
		}
		 t_despues = high_resolution_clock::now(); //anotamos el punto de de fin 
      	 //el tiempo transcurrido es
		 tiempo_transcurrido1  = duration_cast<duration<double> >(t_despues - t_antes) - duration_cast<duration<double> >(t_despues_vacio - t_antes_vacio);
		 // Mostramos resultados
		 std::cout << n << "\t" <<tiempo_transcurrido1.count() << std::endl;

      delete [] U;
    }

  delete [] T;

  return 0;
};
