#include <iostream>
#include <fstream>
#include <limits>
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

//Funcion para ordenar del vector de menor a mayor
void OrdenacionSeleccion(vector<int> &v)
{
  int posicion_minimo, temp, n=v.size();

  for(int i=0;i<n-1;i++)
  {
    posicion_minimo=i;

    for(int j=i+1;j<n;j++)
    {
    	if(v[j]<v[posicion_minimo])
    	{
    		posicion_minimo=j;
    	}
    }

    temp=v[i];
    v[i]=v[posicion_minimo];
    v[posicion_minimo]=temp;
  }
}

int FuncionObjetivo(vector<int> &S, int M) //Devuelve el valor mas optimo para añadir a la solucion
{
	//Como ya hemos ordenado el vector para que siga el criterio establecido(Coger elemento menor)
	//solo tenemos que coger el primer elemento del vector devolverlo y eliminarlo de este

	int optimo;

	optimo=S[0]; //Introduzco el primer elemento (el optimo) en la variable a devolver

	S.erase(S.begin()); //Elimino dicho elemento del vector para que no se vuelva a considerar

	return optimo;
}

bool FuncionFactible(int M, int valor) //Comprueba si es posible usar el elemento para la suma
{
	if(M-valor>=0) //Si el elemento seleccionado cabe para la suma de M, se devuelve true
		return true;
	else //Si el elemento hace que la suma se pase de M, se devuelve false
		return false;
}

int FuncionSeleccion(vector<int> &S,int M) //Devuelve el elemento seleccionado por la función(objetivo) que coge el
{										   //elemento óptimo segun el criterio establecido

	//Como la función óbjetivo elige el mejor elemento solo llamamos a esta y ya nos devuelve el elemento óptimo
	int seleccionado;

	seleccionado=FuncionObjetivo(S,M);

	return seleccionado;
} 

vector<int> FuncionSolucion(vector<int> &S, int &M)
{
	int seleccionado;
	vector<int> resultado;

	//Ordeno el vector de menor a mayor para que siga el criterio establecido
	OrdenacionSeleccion(S);

	while(M!=0 && S.size()!=0) //Ejecuto bulce hasta que ya haya sumado M o no queden mas elementos para sumar
	{
		seleccionado=FuncionSeleccion(S,M); //Llamo a la función de selección para obtener el elemento optimo para la suma
		if(FuncionFactible(M,seleccionado)) //Si es posible añadir el elemento a la suma entro en el if
		{
			resultado.push_back(seleccionado); //Añado el elemento al resultado
			M-=seleccionado; //Disminuyo el tamaño para alcanzar el valor deseado, con el tamaño del elemento introducido
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
