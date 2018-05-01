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

vector<int> Suma(vector<int> S, int M)
{
	/*******CREO LA TABLA*******/

	int n=S.size(); //Numero de objetos disponibles

	int tabla[n+1][M+1];

	//Relleno la fila 0 de la tabla con 0
	for(int i=0;i<=M;i++)
		tabla[0][i]=0;

	//Relleno la columna 0 de la tabla con 0
	for(int i=0;i<=n;i++)
		tabla[i][0]=0;

	//Relleno el resto de la tabla
	for(int i=1;i<=n;i++)
	{
	    for(int j=1;j<=M;j++)
	    {
		    int v1,v2;

		    //Si no cojo el elemento actual
		    v1=tabla[i-1][j];

		    //Si cojo el elemento actual
		    if(j-S[i-1]<0)
		    	v2=numeric_limits<int>::min();
		    else
		    	v2=tabla[i-1][j-S[i-1]]+S[i-1];

		    //Cojo el minimo de las dos opciones
		    if(v1>=v2)
		    	tabla[i][j]=v1;
		    else
		    	tabla[i][j]=v2;
		}
	}

	//Ahora obtengo el vector con los valores de la solucion optima
	vector<int> resultado;

	int i=n,j=M;

	while(i>0 && j>0)
	{

		if(tabla[i][j]!=tabla[i-1][j])
		{
			resultado.push_back(S[i-1]);
			j=j-S[i-1];
			i-=1;
		}
		else
		{
			i-=1;
		}
	}

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