#include "abb.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void ListarAbb(ABB<int> &ab_bus){
  ABB<int>::nodo n;
 //cout<<endl<<"Elementos ordenados: ";
 
 for (n=ab_bus.begin();n!=ab_bus.end();++n){
	   //cout<<*n<<" ";
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

bool repetido(int *v,int tam, int aleatorio)
{
	for(int i=0;i<tam;i++) //Recorro los valores ya existentes en el vector
  	{
  		if(v[i]==aleatorio) //Si esta repetido
  		{
  			return true;
  		}
  		else
  		{
  			return false;
  		}
  	}
}

int main(int argc, char * argv[]){
 /*vector<int>v;
 int a;
 while (cin>>a){
	   v.push_back(a);
 }
cin.clear(); */

// Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=tam;    // Valor máximo
  if (tam<=0 || vmax<=0)
    sintaxis();
 
 /*
  // Generación del vector caso promedio
  int *v=new int[tam];       // Reserva de memoria
  srand(time(0));            // Inicialización del generador de números pseudoaleatorios
  for (int i=0; i<tam; i++)  // Recorrer vector
  {
  	int aleatorio=rand()%vmax; // Generar aleatorio [0,vmax[
  	
  	while(repetido(v,i,aleatorio))
  	{
  		aleatorio=rand()%vmax;
  	}

  	v[i]=aleatorio;
  }
*/

  // Generación del vector caso mejor
  int *v=new int[tam];       // Reserva de memoria
  v[0]=tam/2;
  int j=1;
  for (int i=0; i<tam/2; i++)  // Recorrer vector
  {
  	v[j]=tam/2-i;
  	v[j+1]=tam/2+i;
  	j=j+2;
  }


/*
// Generación del vector caso peor
  int *v=new int[tam];       // Reserva de memoria
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = i;
*/

 ABB<int>ab_bus;
 
 high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start
  
 start = high_resolution_clock::now(); //iniciamos el punto de inicio

 for (int i=0;i<tam;i++){
	   ab_bus.Insertar(v[i]);
 }
 ListarAbb(ab_bus);

 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

 // Mostramos resultados
 cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
 delete [] v;     // Liberamos memoria dinámica

/*
int x;

cout<<endl<<"Dime un elemento a borrar: ";
while (cin>>x) {
if (ab_bus.Buscar(x)){
	  cout<<endl<<x<<" esta"<<endl;
	  ab_bus.Borrar(x);
}
else{ cout<<"El elemento "<<x<<" no esta"<<endl;
}
ListarAbb(ab_bus);
}
*/
 
}