#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
using namespace std;

pair<int,int> Max_Min(int *v,int n)
{
	pair<int,int> minmax;

	if(n==1)
	{
		minmax.first=v[0];
		minmax.second=v[0];
	}
	else if(n==2)
	{
		if(v[0]>v[1])
		{
			minmax.first=v[1];
			minmax.second=v[0];
		}
		else
		{
			minmax.first=v[0];
			minmax.second=v[1];
		}
	}
	else
	{
		pair<int,int> minmax_izq=Max_Min(v,n/2);
		pair<int,int> minmax_der=Max_Min(v+n/2,n-n/2);

		if(minmax_izq.first<minmax_der.first)
			minmax.first=minmax_izq.first;
		else
			minmax.first=minmax_der.first;

		if(minmax_izq.second>minmax_der.second)
			minmax.second=minmax_izq.second;
		else
			minmax.second=minmax_der.second;
	}

	return minmax;
}

int main(int argc, char * argv[])
{
	if (argc!=2)
	{
		cout<<"Formato: ./maxmin tamaño_vector"<<endl;
		return -1;
	}

	int tam=atoi(argv[1]);	// Tamaño del vector

	int *v=new int[tam];       // Reserva de memoria
	srand(time(0));            // Inicialización del generador de números pseudoaleatorios
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		v[i]=rand()%tam;    // Generar aleatorio [0,tam]
		cout<<v[i]<<" ";
	}
	cout<<endl;

	pair<int,int> minmax=Max_Min(v,tam);
	cout<<"Minimo: "<<minmax.first<<endl;
	cout<<"Maximo: "<<minmax.second<<endl;
}