#include <iostream>
#include <fstream>
#include "Apermutacion.h"
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <chrono>
#include <queue>

using namespace std::chrono;

struct nodo {
	int da;
	int CI;
	int DE;
	int CS;
	Apermutacion V=Apermutacion(1);

	nodo(const int &dact, const int &cota_inferior, const int &destimada, const int &cota_superior, const Apermutacion &P) {
		da=dact;
		CI=cota_inferior;
		DE=destimada;
		CS=cota_superior;
		V=P;
	}

	nodo(): da(0), CI(0), DE(0), CS(0), V(1) {}
};

bool operator<(const nodo &n1,const nodo &n2){
	if(n2.DE<n1.DE)
		return true;
	else
		return false;
}

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
		//Con el if evito que se contabilice la discrepancia de la pareja dos veces, ya que lo hago doble
		//al encontrar al primer componente de la pareja, entonces, cuando llega al segundo no entrará al if ya que
		//ya ha sido contabilizado
		if(i<*it-1)
		{
			//Sumo la discrepancia por dos para que asi contabilice la de la pareja y no la de un solo componente
			discrepancia+=discrepancias[i][*it-1]*2;
		}
		//Incremento la variable para que vaya al siguiente alumno
		i++;
	}
  
	//Devuelvo el valor de la suma de discrepancias que hay con las parejas hechas hasta el nodo actual relleno del arbol
	return discrepancia;
}

int CotaInferior(const vector<int> alumnos_emparejados, const vector<vector<int>> discrepancias)
{
	//Creo una variable que contendrá el valor de la discrepancia con el algoritmo voraz,
	//que determina la cota inferior
	int discrepancia=0;

	//Creo un vector que tiene 1 si el elemento esta libre y 0 si está emparejado
	//El vector se crea con todos libres
	vector<int> libres(alumnos_emparejados.size(),1);

	//Recorro la lista de alumnos y sus parejas hasta el momento
	for(unsigned int i=0;i<alumnos_emparejados.size();i++)
	{
		//En caso de que ya este emparejado el alumno entra al if
		if(alumnos_emparejados[i]!=0)
		{
			libres[i]=0; //Marco como emparejado al alumno
			libres[alumnos_emparejados[i]-1]=0; //Marco como emparejado a su pareja
		}
	}

	//Recorro la matriz para emparejar los alumnos que quedan por emparejar
	for(unsigned int i=0;i<discrepancias.size();i++)
	{
		int min=numeric_limits<int>::max(); //Creo una variable con el minimo inicializada con el valor mayor posible
		bool encontrado=false; //Creo una variable para guardar si encuentra pareja al alumno actual

		if(libres[i]==1) //Si el alumno que queremos emparejar esta libre entra al if
		{
			//Recorro los posibles alumnos (j) para emparejar con i
			//Incluye la parte izquierda de la matriz, ya que los nodos del final pueden emparejar con los del principio
			//que esten libres, si fuera solo la diagonal deracha en una matriz de 10, el elemento 8 solo podria 
			//emparejar con 9, ya que es el unico que le queda a su derecha de la matriz
			for(unsigned int j=0;j<discrepancias[0].size();j++) //El alumno i tiene que estar libre para poder
			{												//buscarle pareja, en caso de que no este libre ya la tiene asignada
				if(libres[j]==1 && i!=j) //Si el alumno con el que queremos emparejar i esta libre y no es el mismo entra al if
				{
					if(discrepancias[i][j]<min) //Si la discrepancia es menor que la mínima guardada entra al if
					{
						min=discrepancias[i][j]; //Guardamos la nueva discrepancia mínima
					}
					encontrado=true; //Marcamos encontrado como true ya que le ha encontrado una pareja
				}
			}

			//Si se ha encontrado una pareja para i entra en el if
			if(encontrado)
				discrepancia+=min; //Incremento la discrepancia con la solución voraz
		}
	}

	//Devuelvo la discrepancia estimada por voraces de seguir recorriendo esa rama del arbol
	return discrepancia;
}

int CotaSuperior(const vector<int> alumnos_emparejados, const vector<vector<int>> discrepancias)
{
	//Creo una variable que contendrá el valor de la discrepancia con el algoritmo voraz,
	//que determina la cota inferior
	int discrepancia=0;

	//Creo un vector que tiene 1 si el elemento esta libre y 0 si está emparejado
	//El vector se crea con todos libres
	vector<int> libres(alumnos_emparejados.size(),1);

	//Recorro la lista de alumnos y sus parejas hasta el momento
	for(unsigned int i=0;i<alumnos_emparejados.size();i++)
	{
		//En caso de que ya este emparejado el alumno entra al if
		if(alumnos_emparejados[i]!=0)
		{
			libres[i]=0; //Marco como emparejado al alumno
			libres[alumnos_emparejados[i]-1]=0; //Marco como emparejado a su pareja
		}
	}

	//Recorro la matriz para emparejar los alumnos que quedan por emparejar
	for(unsigned int i=0;i<discrepancias.size();i++)
	{
		int min=numeric_limits<int>::max(); //Creo una variable con el minimo inicializada con el valor mayor posible
		bool encontrado=false; //Creo una variable para guardar si encuentra pareja al alumno actual
		int pos; //Creo una variable para almacenar la posicion del alumno con el que tiene menor discrepancia

		if(libres[i]==1) //Si el alumno que queremos emparejar esta libre entra al if
		{
			for(unsigned int j=i+1;j<discrepancias[0].size();j++) //El alumno i tiene que estar libre para poder
			{												//buscarle pareja, en caso de que no este libre ya la tiene asignada
				if(libres[j]==1 && i!=j) //Si el alumno con el que queremos emparejar i esta libre y no es el mismo entra al if
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
				discrepancia+=min*2; //Incremento la discrepancia dos veces, por los dos elementos emparejados
			}
		}
	}

	//Devuelvo la discrepancia estimada por voraces de seguir recorriendo esa rama del arbol
	return discrepancia;
}

int pareja_branch_bound(int tam, Apermutacion &ab,const vector<vector<int>> &discrepancias, int &nodos_recorridos)
{
	//Creo el vector con todas las posiciones a cero
	vector<int> aux(tam,0);

	//Creo el arbol permutacion con el vector creado antes y el level -1
	Apermutacion P(aux,-1);

	//Creo la cola de prioridad para los nodos vivos
	priority_queue<nodo> pq;

	//Creo un vector con todos libres para calcular la cota superior e inferior inicial
	vector<int> alumnos_emparejados=P.GetSecuencia();

	//Cota inferior
	int cota_inferior=CotaInferior(alumnos_emparejados,discrepancias);

	//Cota superior
	int cota_superior=CotaSuperior(alumnos_emparejados,discrepancias);

	//Discrepancia estimada
	int destimada=(cota_inferior+cota_superior)/2;

	//Creo C
	int C=cota_superior;

	//Creo una variable para ir almacenando la discrepancia actual
	int dact=0;

	//Almaceno en una variable como mejor discrepancia el mayor entero posible, ya que vamos a buscar la
	//discrepancia mas pequeña, por lo que cualquier combinación de parejas sustituirá a este valor
	int best_discrepancia=numeric_limits<int>::max();

	//Creo el nodo actual
	nodo n(dact, cota_inferior, destimada, cota_superior, P);

  	//Inserto el nodo en la cola de prioridad
  	pq.push(n);

  	//Variable para no contar el primer nodo ya que es el arbol permutacional vacio
  	bool first=true;

	//Entro en el bucle para crear todas las posibles combinaciones del arbol permutacional
	while(!pq.empty())
	{
		if(first==true)
			first=false;
		else
			nodos_recorridos++;


		//Obtengo el nodo mas prioritario de la priority queue
		n=pq.top();

		//Elimino el nodo prioritario que acabo de obtener de la cola
		pq.pop();

		//Si la cota inferior del nodo es menor que C, al poder mejorar la solucion que tenemos
		//exploramos el nodo, en caso contrario se poda el nodo
		if(n.CI<=C)
		{
			vector<vector<int>> hijos=n.V.GeneraHijos(); //Genero los hijos del nodo actual

			//Recorro los hijos del nodo actual
			for(unsigned int i=0;i<hijos.size();i++)
			{
				//Creo un arbol permutacional para el nodo hijo actual
				Apermutacion H(hijos[i],n.V.GetLevel()+1);

				dact=Suma_Discrepancias(H,discrepancias);

				alumnos_emparejados=H.GetSecuencia();

				cota_inferior=dact+CotaInferior(alumnos_emparejados,discrepancias);
				cota_superior=dact+CotaSuperior(alumnos_emparejados,discrepancias);

				destimada=(cota_inferior+cota_superior)/2;

				//En caso de ser un nodo hoja y mejorar la discrepancia mejor hasta el momento,
				//hemos encontrado una solucion que mejor la actual asique entra en el if
				if(H.GetLevel()==tam-1 && dact<best_discrepancia)
				{
					best_discrepancia=dact; //Guardamos la nueva mejor discrepancia

					//En caso de que la discrepancia actual mejore a C, sustituimos C
					if(C>dact)
						C=dact;
					
					//Guardamos en el arbol solución, la secuencia actual, que es la mejor hasta el momento
					//y puede terminar siendo la mejor solución
					ab=H;
				}
				else //En caso de no ser nodo hoja o no mejorar a la mejor discrepancia
				{
					//Si la cota inferior del nodo mejora a C entra en el if
					if(cota_inferior<=C)
					{
						//Creo un nuevo nodo con el hijo actual
						nodo nhijo(dact, cota_inferior, destimada, cota_superior, H);
						//Lo meto en la cola de nodos vivos
						pq.push(nhijo);

						//Si la cota superior del nodo hijo mejora a C, se sustituye C
						if(C>cota_superior)
							C=cota_superior;
					}
				}
			}
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

	/**************Mido el tiempo**************/

	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;
	start=high_resolution_clock::now();

	//Llamo a la función de backtracking
	int discrepancia_total=pareja_branch_bound(discrepancias.size(),ab,discrepancias,nodos_recorridos);

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