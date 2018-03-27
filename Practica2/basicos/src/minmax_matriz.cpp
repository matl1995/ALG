#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>
using namespace std;
using namespace std::chrono;

pair<int,int> Max_Min(int **M,int inicioi,int inicioj,int n)
{
	pair<int,int> minmax;

	if(n==1)
	{
		minmax.first=M[inicioi][inicioj];
		minmax.second=M[inicioi][inicioj];
	}
	else if(n==2)
	{
		//Compruebo la posicion 0,0 y 0,1 para ver cual sera le maximo o minimo de ellas
		if(M[inicioi][inicioj]>M[inicioi][inicioj+1])
		{
			minmax.first=M[inicioi][inicioj+1];
			minmax.second=M[inicioi][inicioj];
		}
		else
		{
			minmax.first=M[inicioi][inicioj];
			minmax.second=M[inicioi][inicioj+1];
		}

		//Compruebo si la posicion 1,0 contiene el maximo o minimo
		if(minmax.first>M[inicioi+1][inicioj])
		{
			minmax.first=M[inicioi+1][inicioj];
		}
		else if(minmax.second<M[inicioi+1][inicioj])
		{
			minmax.second=M[inicioi+1][inicioj];
		}
		
		//Compruebo si la posicion 1,1 contiene el maximo o minimo
		if(minmax.first>M[inicioi+1][inicioj+1])
		{
			minmax.first=M[inicioi+1][inicioj+1];
		}
		else if(minmax.second<M[inicioi+1][inicioj+1])
		{
			minmax.second=M[inicioi+1][inicioj+1];
		}
	}
	else
	{
		//Busco el mínimo y máximo en 4 cuadrantes, de forma que el primero empieza
		//en los indices que se pasan, el segundo se desplaza en x hasta la mitad,
		//el tercero se desplaza en y hasta la mitad, y el cuarto se desplaza tanto
		//en x como en y hasta la mitad, se hace partiendo de los indices i,j recibidos
		//ya que así si es la segunda o sucesivas llamadas recursivas a max,min vamos acumulando los
		//indices anteriores, para que la posicion sea correcta, de otra manera si divides
		//n/2 se va llendo todo hacia el primer cuadrante.
		pair<int,int> minmax_1=Max_Min(M,inicioi,inicioj,n/2+n%2);

		pair<int,int> minmax_2=Max_Min(M,inicioi,inicioj+n/2,n/2+n%2);

		pair<int,int> minmax_3=Max_Min(M,inicioi+n/2,inicioj,n/2+n%2);

		pair<int,int> minmax_4=Max_Min(M,inicioi+n/2,inicioj+n/2,n/2+n%2);

		//Busco cual es el minimo mas pequeño de los cuatro cuadrantes
		if(minmax_1.first<minmax_2.first)
		{
			minmax.first=minmax_1.first;
		}
		else
		{
			minmax.first=minmax_2.first;
		}

		if(minmax.first>minmax_3.first)
		{
			minmax.first=minmax_3.first;
		}
			
		if(minmax.first>minmax_4.first)
		{
			minmax.first=minmax_4.first;
		}

		//Busco cual es el maximo mas grande de los cuatro cuadrantes
		if(minmax_1.second>minmax_2.second)
		{
			minmax.second=minmax_1.second;
		}
		else
		{
			minmax.second=minmax_2.second;
		}
		
		if(minmax.second<minmax_3.second)
		{
			minmax.second=minmax_3.second;
		}
			
		if(minmax.second<minmax_4.second)
		{
			minmax.second=minmax_4.second;
		}
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

	//Reserva de memoria
	int **M=new int*[tam];
	for(int i=0;i<tam;i++)
	{
	    M[i]=new int[tam];
	}

	srand(time(0));            // Inicialización del generador de números pseudoaleatorios
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		for(int j=0;j<tam;j++)
		{
			M[i][j]=rand()%100;    // Generar aleatorio [0,tam]
			//cout<<M[i][j]<<" ";
		}
		//cout<<endl;
	}
	//cout<<endl;

	//Procedo a medir los tiempos
	high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 	duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end y start
  
 	start = high_resolution_clock::now(); //iniciamos el punto de inicio

	pair<int,int> minmax=Max_Min(M,0,0,tam);

	end = high_resolution_clock::now(); //anotamos el punto de de fin 
 	//el tiempo transcurrido es
 	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);
 
  	// Mostramos resultados
  	cout << tam << "\t" <<tiempo_transcurrido.count() << endl;

	/*cout<<"Minimo: "<<minmax.first<<endl;
	cout<<"Maximo: "<<minmax.second<<endl;*/
}