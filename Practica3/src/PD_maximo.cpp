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

vector<int> Suma(vector<int> &S, int &M)
{
	vector<int> resultado;
	return resultado;
}

int main (int argc, char * argv[]) {

	if(argc!=3)
  	{
		cout<<"Formato para ejecución: ./PD_maximo conjunto_de_numeros.txt numero_entero_a_sumar(mayor o igual a 0)"<< argv[1] << endl;
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
		cout<<"Formato para ejecución: ./PD_maximo conjunto_de_numeros.txt numero_entero_a_sumar(mayor o igual a 0)"<< argv[1] << endl;
		exit(-1);
  	}

	vector<int> resultado; //Vector que contendrá los elementos que formarán la solución

	//Llamamos a la función para obtener la solución
	resultado=Suma(S,M);

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