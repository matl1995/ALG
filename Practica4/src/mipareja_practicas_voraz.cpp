#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include <string>

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
        	entrada_str>>tmp1;
        	tmp.push_back(tmp1);
    	}
    	M.push_back(tmp);
	}

	return is;
}

/*//Funcion para ordenar del vector de menor a mayor
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

bool FuncionFactible(int M, int valor) //Comprueba si cabe el programa en la cinta
{
	if(M-valor>=0) //Si el programa tiene una longitud que cabe en lo que queda de cinta, devuelve true
		return true;
	else //Si el programa no cabe en lo que queda en la cinta, devuelve false
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

	while(M!=0 && S.size()!=0) //Ejecuto bulce hasta que ya se haya completado la cinta o no haya mas programas por almacenar
		{
		seleccionado=FuncionSeleccion(S,M); //Llamo a la función de selección para obtener el elemento optimo para la cinta
		if(FuncionFactible(M,seleccionado)) //Si es posible añadir el elemento a la cinta entro en el if
		{
			resultado.push_back(seleccionado); //Añado el programa al resultado
			M-=seleccionado; //Disminuyo el tamaño para alcanzar el maximo de la cinta, con la longitud del programa introducido
		}
	}

	return resultado;
}*/

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

	/*vector<int> resultado; //Vector que contendrá los elementos que formarán la solución

	//Llamamos a la función para obtener la solución
	resultado=FuncionSolucion(S);

	//Muestro el resultado
	cout<<"El subconjunto que incluye mas programas con longitur inferior a "<<argv[2]<<" son: ";

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
		cout<<"\nOcupando esta longitud dentro de la cinta: "<<suma<<endl;
	}*/
}
