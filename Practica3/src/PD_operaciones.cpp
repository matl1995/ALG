#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

//Creo un enumerado con las operaciones
enum operacion { no,suma, resta, multiplicacion, division };

//Creo un struct que sera el contenido de cada casilla de la tabla
struct casilla {
	int valor=numeric_limits<int>::max();
	operacion op=no;
};

istream &operator>>(istream& is, vector<int> &S) {
  
	string line; //String que almacena una linea del archivo

	while(getline(is, line)) //While se ejecuta mientras reciba lineas
	{                   
		S.push_back(atoi(line.c_str())); //Convierto la linea en un entero y la meto al vector
	}
  
	return is;
}

vector<casilla> Operaciones(vector<int> S, int M) //Función para obtener la suma con PD
{
	/*******CREO LA TABLA*******/

	int n=S.size(); //Numero de objetos disponibles

	casilla tabla[n+1][(M*S[0])+1]; //Reservo la memoria para la tabla

	//Relleno la fila 0 de la tabla, cada valor con su correspondiente numero de columna
	for(int i=0;i<=(M*S[0]);i++)
		tabla[0][i].valor=i;

	//Relleno la columna 0 de la tabla con 0
	for(int i=0;i<=n;i++)
		tabla[i][0].valor=0;

	//Relleno el resto de la tabla
	for(int i=1;i<=n;i++)
	{
	    for(int j=1;j<=(M*S[0]);j++)
	    {
		    casilla v1,v2,v3,v4,v5;

		    //Si no cojo el elemento actual
		    v1.valor=tabla[i-1][j].valor;

		    //Si cojo el elemento actual con suma
		    if(j-S[i-1]<0) //Si la posicion para calcular el valor actual esta fuera de la tabla ponemos +infinito
		    	v2.valor=numeric_limits<int>::max();
		    else //Si la posicion esta dentro calculamos con la formula
		    {
		    	v2.valor=tabla[i-1][j-S[i-1]].valor;
		    	v2.op=suma;
		    }

		    //Si cojo el elemento actual con resta
		    if(j+S[i-1]>(M*S[0])) //Si la posicion para calcular el valor actual esta fuera de la tabla ponemos +infinito
		    	v3.valor=numeric_limits<int>::max();
		    else //Si la posicion esta dentro calculamos con la formula
		    {
		    	v3.valor=tabla[i-1][j+S[i-1]].valor;
		    	v3.op=resta;
		    }

		    //Si cojo el elemento actual con multiplicacion
		    if(j%S[i-1]!=0) //Si la division no devuelve un numero entero ponemos +infinito
		    	v4.valor=numeric_limits<int>::max();
		    else //Si la posicion devuelve un numero entero calculamos con la formula
		    {
		    	v4.valor=tabla[i-1][j/S[i-1]].valor;
		    	v4.op=multiplicacion;
		    }

		    //Si cojo el elemento actual con division
		    if(j*S[i-1]>(M*S[0])) //Si la posicion para calcular el valor actual esta fuera de la tabla ponemos +infinito
		    	v5.valor=numeric_limits<int>::max();
		    else //Si la posicion esta dentro calculamos con la formula
		    {
		    	v5.valor=tabla[i-1][j*S[i-1]].valor;
		    	v5.op=division;
		    }

		    //Cojo el minimo de todas las opciones
		    casilla minimo=v1;

		    if(v2.valor<minimo.valor)
		    {
		    	minimo.valor=v2.valor;
		    	minimo.op=v2.op;
		    }
		    
		    if(v3.valor<minimo.valor)
		    {
		    	minimo.valor=v3.valor;
		    	minimo.op=v3.op;
		    }

		    if(v4.valor<minimo.valor)
		    {
		    	minimo.valor=v4.valor;
		    	minimo.op=v4.op;
		    }

		    if(v5.valor<minimo.valor)
		    {
		    	minimo.valor=v5.valor;
		    	minimo.op=v5.op;
		    }

		    tabla[i][j]=minimo;
		}
	}

	//Imprimo la tabla
	for(int i=0;i<=n;i++)
	{
	    for(int j=0;j<=(M*S[0]);j++)
	    {
	    	cout<<tabla[i][j].valor;
			if(tabla[i][j].op==suma)
				cout<<"+";
			else if(tabla[i][j].op==resta)
				cout<<"-";
			else if(tabla[i][j].op==multiplicacion)
				cout<<"*";
			else if(tabla[i][j].op==division)
				cout<<"/";

			cout<<" ";
	    }
	    cout<<endl;
	}
	cout<<endl;

	//Ahora obtengo el vector con los valores de la solucion optima
	vector<casilla> resultado;

	int i=n,j=M;

	while(i>0 && j>0) //Mientras que los indices no se salgan de la tabla
	{

		if(tabla[i][j].valor!=tabla[i-1][j].valor) //Si el elemento no es igual que el de la fila superior
		{
			casilla tmp;
			tmp.valor=S[i-1];
			tmp.op=tabla[i][j].op;
			resultado.push_back(tmp); //Lo meto como solución

			//Muevo indice de columna a el valor correspondiente en función de la operacion aplicada
			if(tabla[i][j].op==suma)
        		j=j-S[i-1];
      		else if(tabla[i][j].op==resta)
        		j=j+S[i-1];
      		else if(tabla[i][j].op==multiplicacion)
        		j=j/S[i-1];
      		else
        		j=j*S[i-1];

			i-=1; //Muevo el indice a la fila anterior
		}
		else //Si el elemento es igual que el de la fila superior, este no se mete como solucion
		{
			i-=1; //Muevo el indice a la fila anterior
		}
	}

	return resultado;
}

int main (int argc, char * argv[]) {

	if(argc!=3)
  	{
		cout<<"Formato para ejecución: ./PD_operaciones conjunto_de_numeros.txt numero_entero_a_obtener(mayor o igual a 0)"<< argv[1] << endl;
	  	exit(-1);
	}

	ifstream archivo(argv[1]);

	if (!archivo){
		cout<<"No se pudo abrir el fichero "<<argv[1]<<endl;
	}
	  
	vector<int> S; //Creo el vector donde ira el conjunto de numeros

	archivo>>S; //Lleno el vector con los numeros del archivo dado (candidatos)

	for(unsigned int i=0;i<S.size();i++) //Recorro el vector resultado
	{
		cout<<S[i]<<" ";
	}
	cout<<endl;

	int M=atoi(argv[2]); //Meto el numero a sumar en la variable M

	cout<<"M: "<<M<<endl;
  
  	if(M<0)
  	{
		cout<<"Formato para ejecución: ./PD_operaciones conjunto_de_numeros.txt numero_entero_a_obtener(mayor o igual a 0)"<< argv[1] << endl;
		exit(-1);
  	}

	vector<casilla> resultado; //Vector que contendrá los elementos que formarán la solución

	//Llamamos a la función para obtener la solución
	resultado=Operaciones(S,M);

	//Muestro el resultado
	cout<<"Los numeros recibidos para obtener "<<argv[2]<<" son: ";

	if(resultado.empty()) //En caso de que no haya ninguna solución
	{
		cout<<0<<endl;
	}
	else //En caso de que si haya una solución
	{
		for(unsigned int i=0;i<resultado.size();i++) //Recorro el vector resultado
		{
			if(i==resultado.size()-1) //Si es el ultimo valor solo imprime el numero
				cout<<resultado[i].valor<<endl;
			else //Si no imprime el numero y la operacion
			{
				cout<<resultado[i].valor;
				if(resultado[i].op==suma)
					cout<<"+";
				else if(resultado[i].op==resta)
					cout<<"-";
				else if(resultado[i].op==multiplicacion)
					cout<<"*";
				else if(resultado[i].op==division)
					cout<<"/";
			}
		}
	}
}