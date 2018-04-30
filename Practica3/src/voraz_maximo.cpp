#include <iostream>
#include <vector>

using namespace std;

istream &operator>>(istream& is, vector<int> &S) {
  
	string line; //String que almacena una linea del archivo

	getline(is, line); //Obtengo la primera linea del archivo

	while (!is.eof()) //While se ejecuta hasta que no se llegue al final del archivo
	{                   
		S.push_back(atoi(line.c_str())); //Convierto la linea en un entero y la meto al vector
		getline(is, line); //Meto la siguiente linea en line
	}
  
	return is;
}

void FuncionObjetivo(){

}

void FuncionFactible() {

}

void Funcion_Seleccion (){

} 

void Funcion_Solucion (){

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

	archivo>>S; //Lleno el vector con los numeros del archivo dado

	int M=atoi(argv[2]); //Meto el numero a sumar en la variable M
  
  	if(M<0)
  	{
		cout<<"Formato para ejecución: ./voraz_maximo conjunto_de_numeros.txt numero_entero_a_sumar(mayor o igual a 0)"<< argv[1] << endl;
		exit(-1);
  	}

	vector<int> resultado; //Vector que contendrá los elementos que formarán la solución

	//Llamamos a la función para obtener la solución
	Funcion_Solucion();

	//Muestro el resultado
	cout<<"Los numeros obtenidos para obtener "<<argv[2]<<" son: ";

	int suma=0; //Creo e inicializo la variable que contendra la suma de la solución obtenida

	if(resultado.empty()) //En caso de que no haya ninguna solución
	{
		cout<<0<<endl;
	}
	else //En caso de que si haya una solución
	{
		for(int i=0;i<resultado.size();i++) //Recorro el vector resultado
		{
			suma=suma+resultado[i]; //Voy sumando los elementos que forman parte de la solución

			cout<<resultado[i]<<" ";
		}
		cout<<"\nY su suma nos da: "<<suma<<endl;
	}
}
