#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

istream &operator>>(istream& is, vector<int> &S) {
  
	string line; //String que almacena una linea del archivo

	while(getline(is, line)) //While se ejecuta mientras reciba lineas
	{                   
		S.push_back(atoi(line.c_str())); //Convierto la linea en un entero y la meto al vector
	}
  
	return is;
}

pair<int,int> FuncionObjetivo(vector<int> S, int M) //Devuelve el valor mas optimo para añadir a la solucion
{
	pair<int,int> min_indice=make_pair(100000,-1);

	for(unsigned int i=0;i<S.size();i++)
	{
		if(S[i]<min_indice.first)
		{
			min_indice.first=S[i];
			min_indice.second=i;
		}
	}

	return min_indice;
}

bool FuncionFactible(int M, int valor)
{
	if(M-valor>=0)
		return true;
	else
		return false;
}

pair<int,int> FuncionSeleccion(vector<int> S,int M) //Devuelve el valor e indice del elemento optimo para introducir
{
	pair<int,int> indice_valor;

	indice_valor=FuncionObjetivo(S,M);

	return indice_valor;
} 

vector<int> FuncionSolucion(vector<int> &S, int &M)
{
	pair<int,int> seleccionado;
	vector<int> resultado;

	while(M!=0 && S.size()!=0)
	{
		seleccionado=FuncionSeleccion(S,M);
		S.erase(S.begin()+seleccionado.second);
		if(FuncionFactible(M,seleccionado.first))
		{
			resultado.push_back(seleccionado.first);
			M-=seleccionado.first;
		}
	}

	return resultado;
}

int main (int argc, char * argv[]) {

	if(argc!=3)
  	{
		cout<<"Formato para ejecución: ./voraz_maximo conjunto_de_numeros.txt numero_entero_a_sumar(mayor o igual a 0)"<< argv[1] << endl;
	  	exit(-1);
	}

	ifstream archivo(argv[1]);

	if (!archivo){
		cout<<"No se pudo abrir el fichero "<<argv[1]<<endl;
	}
	  
	vector<int> S; //Creo el vector donde ira el conjunto de numeros

	archivo>>S; //Lleno el vector con los numeros del archivo dado (candidatos)

	int M=atoi(argv[2]); //Meto el numero a sumar en la variable M
  
  	if(M<0)
  	{
		cout<<"Formato para ejecución: ./voraz_maximo conjunto_de_numeros.txt numero_entero_a_sumar(mayor o igual a 0)"<< argv[1] << endl;
		exit(-1);
  	}

	vector<int> resultado; //Vector que contendrá los elementos que formarán la solución

	//Llamamos a la función para obtener la solución
	resultado=FuncionSolucion(S,M);

	//Muestro el resultado
	cout<<"Los numeros recibidos para obtener "<<argv[2]<<" son: ";

	int suma=0; //Creo e inicializo la variable que contendra la suma de la solución obtenida

	if(resultado.empty()) //En caso de que no haya ninguna solución
	{
		cout<<0<<endl;
	}
	else //En caso de que si haya una solución
	{
		for(unsigned int i=0;i<resultado.size();i++) //Recorro el vector resultado
		{
			suma=suma+resultado[i]; //Voy sumando los elementos que forman parte de la solución

			cout<<resultado[i]<<" ";
		}
		cout<<"\nY su suma nos da: "<<suma<<endl;
	}
}
