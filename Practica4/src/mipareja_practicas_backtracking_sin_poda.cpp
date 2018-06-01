#include <iostream>
#include <fstream>
#include "Apermutacion.h"
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std::chrono;

istream &operator>>(istream& is, vector<vector<int>> &M) 
{
	string linea;	//String que contiene una linea del archivo
	istringstream entrada_str;	//Contendrá la linea pasada a string

	getline(is, linea);	//Desecho la primera linea del archivo
	getline(is, linea);	//Cojo la segunda en la que tengo el tamaño de la matriz

	entrada_str.str(linea);

	int fil,col;
	entrada_str>>fil; //Introduzco el numero de filas desde el archivo
	entrada_str>>col; //Introduzco el numero de columnas desde el archivo

	//Creo la matriz
	for(int i=0;i<fil;i++)
	{
    	vector<int> tmp;

    	getline(is, linea);	//Obtengo la linea siguiente
		entrada_str.str(linea); //Contiene la linea en string
		entrada_str.clear();	//Limpio los flags de error   

    	for(int j=0;j<col;j++)
    	{
        	int tmp1;
        	entrada_str>>tmp1; //Meto cada elemento de la linea en la variable tmp1
        	tmp.push_back(tmp1); //Voy creando un vector con los elementos de la linea
    	}
    	M.push_back(tmp); //Inserto el vector como una fila de la matriz
	}

	return is;
}

vector<vector<int>> calcularMatrizDiscrepancias(vector<vector<int>> M)
{
	int size=M.size();

	//Creo la matriz con su tamaño reservado
	vector<vector<int>> resultado;
	resultado.resize(size);
	for(unsigned int i=0;i<resultado.size();i++)
	{
		resultado[i].resize(size);
	}

	//Relleno la diagonal con infinito
	for(int i=0;i<size;i++)
	{
		resultado[i][i]=numeric_limits<int>::max();
	}

	for(unsigned int i=0;i<M.size()-1;i++) //Bucle para recorrer cada alumno
	{
		for(unsigned int j=i+1;j<M.size();j++) //Bucle para comparar cada alumno con el resto
		{
			int discrepancia=0;
			for(unsigned int k=0;k<M[0].size();k++) //Bucle para calcular cada una de las discrepancias
			{
				discrepancia+=abs(M[i][k]-M[j][k]);
			}
			resultado[i][j]=resultado[j][i]=discrepancia; //Introduzco la discrepancia en i,j y j,i ya que es el mismo par
		}
	}

	return resultado;
}

int Suma_Discrepancias(const Apermutacion &P,const vector<vector<int>> discrepancias)
{
	//Creo un iterador para recorrer el arbol
	Apermutacion::const_iterator it;
	//Creo la variable que contendrá la suma de discrepancias que hay hasta el nodo actual
	int discrepancia=0;
	//Creo variable para recorrer los alumnos
	int i=0;
	//Recorro en el arbol hasta el nodo actual
	for(it=P.begin();it!=P.end();++it)
	{
		//Sumo las discrepancias de la matriz que corresponden a las parejas que hay en los nodos del arbol
		discrepancia+=discrepancias[i][*it-1];
		//Incremento la variable para que vaya al siguiente alumno
		i++;
	}
  
	//Devuelvo el valor de la suma de discrepancias que hay con las parejas hechas hasta el nodo actual relleno del arbol
	return discrepancia;
}

int pareja_backtracking(int n, Apermutacion &ab,const vector<vector<int>> &discrepancias, int &nodos_recorridos)
{
	//Creo un arbol permutacional para ir creando las posibles soluciones al problema en el
	Apermutacion P(n);
	//Creo una variable para mantener el bucle ejecutandose
	bool seguir=true;
	//Almaceno en una variable como mejor discrepancia el mayor entero posible, ya que vamos a buscar la
	//discrepancia mas pequeña, por lo que cualquier combinación de parejas sustituirá a este valor
	int best_discrepancia=numeric_limits<int>::max();
	//Creo una variable para ir almacenando la discrepancia actual
	int dact;
	//Entro en el bucle para crear todas las posibles combinaciones del arbol permutacional
	while(seguir)
	{
		//Aumento el número de nodos recorridos
		nodos_recorridos++;
		//Obtengo la suma de discrepancias con las combinaciones de alumnos creadas hasta el momento
		dact=Suma_Discrepancias(P,discrepancias);

		//En caso de que este en el ultimo nivel del arbol, es decir, que haya generado todas las combinaciones
		//de parejas posibles entra en el if
		if(P.GetLevel()==n-1)
		{
			//Si la discrepancia actual mejora a la mejor que hay almacenada entra al if
			if(dact<best_discrepancia)
			{
				best_discrepancia=dact; //Almaceno la actual como mejor discrepancia
				
				//Guardo en el arbol que contendrá la solucion el actual, ya que contiene la mejor solución hasta
				//el momento, que puede que al final sea la definitiva
				ab=P;
			}		
		}

		//Genero el siguiente nodo
		seguir=P.GeneraSiguienteProfundidad();
	}
	
	return best_discrepancia;
}

int main (int argc, char * argv[]) {

	if(argc!=2)
  	{
		cout<<"Formato para ejecución: ./mipareja_practicas_voraz gustos.txt"<< argv[1] << endl;
	  	exit(-1);
	}

	ifstream archivo(argv[1]);

	if (!archivo){
		cout<<"No se pudo abrir el fichero "<<argv[1]<<endl;
	}
	  
	vector<vector<int>> M;

	archivo>>M; //Lleno la matriz con los datos del archivo

	//Imprimo la matriz
	cout<<"Archivo leido: "<<endl;
	int fil=M.size();
	int col=M[0].size();

	cout<<fil<<" "<<col<<endl;
	for(int i=0;i<fil;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	//Obtengo la matriz de discrepancias entre los alumnos
	vector<vector<int>> discrepancias=calcularMatrizDiscrepancias(M);

	//Imprimo la matriz de discrepancias
	cout<<"Matriz de discrepancias: "<<endl;
	for(unsigned int i=0;i<discrepancias.size();i++)
	{
		for(unsigned int j=0;j<discrepancias[0].size();j++)
		{
			cout<<discrepancias[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	int nodos_recorridos=0;
	Apermutacion ab(discrepancias.size());

	/**************Mido el tiempo**************/

	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;
	start=high_resolution_clock::now();

	//Llamo a la función de backtracking
	int discrepancia_total=pareja_backtracking(discrepancias.size(),ab,discrepancias,nodos_recorridos);

	end=high_resolution_clock::now();
    tiempo_transcurrido=duration_cast<duration<double>>(end-start);

	/**************Mido el tiempo**************/

	int total=ab.NumeroSecuenciasPosibles();
	float porcentaje=(nodos_recorridos/(float)total)*100;

	cout<<"Numero de nodos recorridos: "<<nodos_recorridos<<", total de nodos: "<<total<<endl;
	cout<<"Porcentaje de nodos recorridos: "<<porcentaje<<endl;
	cout<<"Discrepancia con Backtracking: "<<discrepancia_total<<endl;

	Apermutacion::iterator it;
	int i=1;
	for(it=ab.begin();it!=ab.end();++it)
	{
		cout << "Persona " << i << " con Persona " << *it << endl;
		i++;
	}

	
	cout<<endl<<"Tiempo: "<<tiempo_transcurrido.count()<<endl;
}