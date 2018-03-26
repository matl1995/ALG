#include <iostream>
#include <cstdlib>  //Para generación de números pseudoaleatorios
#include <algorithm> //Para desordenar el vector de pies
#include <utility> //Para hacer pair
#include <vector> //Para tener vectores
using namespace std;

pair<int,int> moda(vector<int> elementos,int n)
{
	pair<int,int> resultado;

	if(n==0) //Si el vector recibido esta vacio devolvemos 0,0
	{
		resultado=make_pair(0,0);
	}
	else if(n==1) //si el vector solo tiene un elemento devuelvo el elemento y su frequencia que es 1
	{
		resultado=make_pair(elementos[0],1);
	}
	else
	{
		//Obtengo el primer pivote
		int pivote=elementos[rand()%n];
		vector<int> heterogeneos_menores, heterogeneos_mayores, homogeneos;

		//Busco los elementos menores mayores e iguales para introducirlos en sus respectivos conjuntos
		for(int i=0;i<n;i++)
		{
			if(elementos[i]<pivote)
			{
				heterogeneos_menores.push_back(elementos[i]);
			}
			else if(elementos[i]>pivote)
			{
				heterogeneos_mayores.push_back(elementos[i]);
			}
			else
			{
				homogeneos.push_back(elementos[i]);
			}
		}

		if(homogeneos.size()>heterogeneos_mayores.size() && homogeneos.size()>heterogeneos_menores.size())
		{
			resultado=make_pair(homogeneos[0],homogeneos.size());
		}
		else
		{
			//Ahora llamo recursivamente para comprobar los heterogeneos mayores y menores
			pair<int,int> homogeneos_menores,homogeneos_mayores;

			homogeneos_menores=moda(heterogeneos_menores,heterogeneos_menores.size());
			homogeneos_mayores=moda(heterogeneos_mayores,heterogeneos_mayores.size());

			//Ahora escogemos cual es el numero que se repite mas, que será la moda, en caso de que haya
			//varios numero moda, se quedará con el que primero aparezca, primero el de homogeneos, luego
			//el de la recurrencia sobre los menores y luego el de la recurrencia sobre los mayores
			if(homogeneos.size()>=homogeneos_menores.second && homogeneos.size()>=homogeneos_mayores.second)
			{
				resultado=make_pair(homogeneos[0],homogeneos.size());
			}
			else if(homogeneos_menores.second>=homogeneos.size() && homogeneos_menores.second>=homogeneos_mayores.second)
			{
				resultado=homogeneos_menores;
			}
			else
			{
				resultado=homogeneos_mayores;
			}
		}
		
	}

	return resultado;
}

int main(int argc, char * argv[])
{
	if (argc!=2)
	{
		cout<<"Formato: ./zapatos numero-de-niños/zapatos"<<endl;
		return -1;
	}

	int tam=atoi(argv[1]);	// Tamaño de la matriz

	//Creo el vector de zapatos y pies
	vector<int> elementos;

	srand(time(0));            // Inicialización del generador de números pseudoaleatorios

	cout<<"Conjunto de elementos:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		elementos.push_back(rand()%tam);    // Generar aleatorio [0,5]
		cout<<elementos[i]<<" ";
	}
	cout<<endl;

	pair<int,int> moda_freq=moda(elementos,tam);

	cout<<"Elemento moda: "<<moda_freq.first<<", numero de veces que aparece: "<<moda_freq.second<<endl;
}