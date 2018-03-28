#include <iostream>
#include <cstdlib>  //Para generación de números pseudoaleatorios
#include <algorithm> //Para desordenar el vector de pies
#include <utility> //Para hacer pair
#include <vector> //Para tener vectores
#include <chrono>
using namespace std;
using namespace std::chrono;

vector<pair<int,int>> tallas(vector<int> zapatos,vector<int> pies,int n)
{
	vector<pair<int,int>> resultado;

	if(n==0){}
	else if(n==1) //en caso de que sean los unicos elementos del vector recibido se introducen como pareja
	{
		resultado.push_back(make_pair(zapatos[0],pies[0]));
	}
	else
	{
		//Obtengo el primer pivote
		int pivote1=zapatos[rand()%n];
		vector<int> pmenores, pmayores, piguales;

		//Busco los pies que son de talla menor, igual o mayor y los meto en sus respectivos conjuntos
		for(int i=0;i<n;i++)
		{
			if(pies[i]<pivote1)
			{
				pmenores.push_back(pies[i]);
			}
			else if(pies[i]>pivote1)
			{
				pmayores.push_back(pies[i]);
			}
			else
			{
				piguales.push_back(pies[i]);
			}
		}

		//Cojo cual es el pie que encaja perfecto en el zapato pivote y lo convierto en el pivote2
		int pivote2=piguales[0];
		vector<int> zmenores, zmayores, ziguales;

		//Busco los zapatos que son de talla menor, igual o mayor y los meto en sus respectivos conjuntos
		for(int i=0;i<n;i++)
		{
			if(zapatos[i]<pivote2)
			{
				zmenores.push_back(zapatos[i]);
			}
			else if(zapatos[i]>pivote2)
			{
				zmayores.push_back(zapatos[i]);
			}
			else
			{
				ziguales.push_back(zapatos[i]);
			}
		}

		//Ahora llamo recursivamente en los subconjuntos mayores y menores
		vector<pair<int,int>> resultado_menores,resultado_mayores;

		resultado_menores=tallas(zmenores,pmenores,zmenores.size());
		resultado_mayores=tallas(zmayores,pmayores,zmayores.size());

		for(int i=0;i<resultado_menores.size();i++)
		{
			resultado.push_back(make_pair(resultado_menores[i].first,resultado_menores[i].second));
		}

		for(int i=0;i<ziguales.size();i++)
		{
			resultado.push_back(make_pair(ziguales[i],piguales[i]));
		}

		for(int i=0;i<resultado_mayores.size();i++)
		{
			resultado.push_back(make_pair(resultado_mayores[i].first,resultado_mayores[i].second));
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
	vector<int> zapatos,pies;

	srand(time(0));            // Inicialización del generador de números pseudoaleatorios

	/*//Caso peor: no hay repeditos, por lo que cada numero es diferente y hay pasar por todos los numeros (mas recursiones)
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		zapatos.push_back(i+1);    // Generar aleatorio [0,5]
		pies.push_back(zapatos[i]);
	}*/

	//Caso mejor: todos son el mismo entonces entran en iguales y las recursiones devuelven 0
	/*for (int i=0;i<tam;i++)  // Recorrer vector
	{
		zapatos.push_back(1);    // Generar aleatorio [0,5]
		pies.push_back(zapatos[i]);
	}*/

	//Caso promedio: hay repetidos, por lo que algunos se agruparan en el elemento iguales y habra menos recursiones
	//cout<<"Vectores antes de ordenar:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		zapatos.push_back(rand()%tam);    // Generar aleatorio [0,5]
		pies.push_back(zapatos[i]);
		//cout<<zapatos[i]<<" ";
	}
	//cout<<endl;

	//Desordeno pies
	random_shuffle(pies.begin(),pies.end());

	/*//Imprimo las tallas de los pies
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<pies[i]<<" ";
	}
	cout<<endl;*/

	//Procedo a medir los tiempos
	high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 	duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end y start
  
 	start = high_resolution_clock::now(); //iniciamos el punto de inicio

	vector<pair<int,int>> zapatos_pies=tallas(zapatos,pies,tam);

	end = high_resolution_clock::now(); //anotamos el punto de de fin 
 	//el tiempo transcurrido es
 	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);
 
  	// Mostramos resultados
  	cout << tam << "\t" <<tiempo_transcurrido.count() << endl;

	/*cout<<"Vectores despues de ordenar:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<zapatos_pies[i].first<<" ";
	}
	cout<<endl;

	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<zapatos_pies[i].second<<" ";
	}
	cout<<endl;*/
}