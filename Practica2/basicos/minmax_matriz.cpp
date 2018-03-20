#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
using namespace std;

pair<int,int> Max_Min(int **M,int inicioi,int inicioj,int n)
{
	pair<int,int> minmax;

	if(n==1)
	{
		minmax.first=M[0][0];
		minmax.second=M[0][0];
	}
	else if(n==2)
	{
		if(M[0][0]>M[0][1])
		{
			minmax.first=M[0][1];
			minmax.second=M[0][0];
		}
		else
		{
			minmax.first=M[0][0];
			minmax.second=M[0][1];
		}

		
			if(minmax.first>M[1][0])
			{
				minmax.first=M[1][0];

				if(minmax.second<M[1][1])
					minmax.second=M[1][1];
			}

			if(minmax.first>M[1][1])
			{
				minmax.first=M[1][1];

				if(minmax.second<M[1][0])
					minmax.second=M[1][0];
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
		cout<<"Formato: ./maxmin tamaño_matriz"<<endl;
		return -1;
	}

	int tam=atoi(argv[1]);	// Tamaño de la matriz

	int **M=new int[tam][tam];       // Reserva de memoria
	srand(time(0));            // Inicialización del generador de números pseudoaleatorios
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		for(int j=0;j<tam;j++)
		{
			M[i][j]=rand()%tam;    // Generar aleatorio [0,tam]
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	pair<int,int> minmax=Max_Min(M,0,0,tam);
	cout<<"Minimo: "<<minmax.first<<endl;
	cout<<"Maximo: "<<minmax.second<<endl;
}