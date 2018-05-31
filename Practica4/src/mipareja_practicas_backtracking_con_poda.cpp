#include <iostream>
#include <fstream>
#include "Apermutacion.h"
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

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

vector<pair<int,int>> pareja_voraz(vector<vector<int>> discrepancias)
{
	vector<pair<int,int>> resultado(discrepancias.size()); //Creo el vector en el que irán los emparejamientos

	//Relleno un vector con todos libres (1)
	vector<int> libres(discrepancias.size(),1);

	//Recorro la matriz para asignar los alumnos
	for(unsigned int i=0;i<discrepancias.size();i++)
	{
		int min=numeric_limits<int>::max(); //Creo una variable con el minimo inicializada con el valor mayor posible
		int pos; //Creo una variable para almacenar la posicion del alumno con el que tiene menor discrepancia
		bool encontrado=false; //Creo una variable para guardar si encuentra pareja al alumno actual

		//Recorro los posibles alumnos (j) para emparejar con i
		for(unsigned int j=i+1;j<discrepancias[0].size() && libres[i]==1;j++) //El alumno i tiene que estar libre para poder
		{												//buscarle pareja, en caso de que no este libre ya la tiene asignada
			if(libres[j]==1) //Si el alumno con el que queremos emparejar i esta libre entra al if
			{
				if(discrepancias[i][j]<min) //Si la discrepancia es menor que la mínima guardada entra al if
				{
					min=discrepancias[i][j]; //Guardamos la nueva discrepancia mínima
					pos=j; //Guardamos la posicion del alumno con el que i tiene discrepancia mínima
				}
				encontrado=true; //Marcamos encontrado como true ya que le ha encontrado una pareja
			}
		}

		//Si se ha encontrado una pareja para i entra en el if
		if(encontrado)
		{
			libres[i]=0; //Marcamos i como ya emparejado
			libres[pos]=0; //Marcamos la pareja de i asignada como ya emparejado
			resultado[i].first=pos; //Metemos en pareja de i a el alumno que fue elejido en pos
			resultado[pos].first=i; //Metemos en pareja del alumno pos al alumno i
			resultado[i].second=min; //Metemos el valor de la discrepancia con su pareja
			resultado[pos].second=min; //Metemos el valor de la discrepancia con su pareja
		}
	}

	return resultado;
}

int Suma_Discrepancias(const Apermutacion &P,const vector<vector<int>> discrepancias)
{
	Apermutacion::const_iterator it;
	int discrepancia=0;
	int i=0;
	for(it=P.begin();it!=P.end();++it)
	{
		discrepancia+=discrepancias[i][*it-1];
		i++;
	}
  
	return discrepancia;
}

int pareja_backtracking(int n, Apermutacion &ab,const vector<vector<int>> &discrepancias, int &nodos_recorridos)
{
	Apermutacion P(n);
	bool seguir=true;
	int best_discrepancia=numeric_limits<int>::max();
	int bact;
	while(seguir)
	{
		nodos_recorridos++;
		bact=Suma_Discrepancias(P,discrepancias);
		if(P.GetLevel()==n-1)
		{
			if(bact<best_discrepancia)
			{
				best_discrepancia=bact;
				ab=P;
				seguir=P.Backtracking();
			}
			else
			{
				seguir=P.GeneraSiguienteProfundidad();
			}
		}
		else
		{
			seguir=P.GeneraSiguienteProfundidad();
		}
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

	int discrepancia_total=pareja_backtracking(discrepancias.size(),ab,discrepancias,nodos_recorridos);

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
}