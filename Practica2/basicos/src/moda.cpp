#include <iostream>
#include <cstdlib>  //Para generación de números pseudoaleatorios
#include <algorithm> //Para desordenar el vector de pies
#include <utility> //Para hacer pair
#include <vector> //Para tener vectores
using namespace std;

pair<int,int> pivote(int *elementos, int inicio, int fin)
{
	int p,k,l,aux;
	k=inicio;
	p=elementos[(inicio+fin)/2];
	/***DEBUG***cout<<"valor de pivote="<<p<<endl;***/
	l=fin;

	//Ejecuto el funcionamiento del pivote para los pies, por lo que el pivote
	//obtenido proviene de los zapatos
    while(k<l)
    {
        while(elementos[k]<=p && k<=fin)
            k++;

        while(elementos[l]>p && l>=inicio)
			l--;

        if(k<l)
        {
            aux=elementos[k];
            elementos[k]=elementos[l];
            elementos[l]=aux;
        }
    }

    //Coloco los elementos con mismo valor que pivote a la izquierda
    //de la posición final que tendrá el pivote
    int pos=k-1;
    for(int i=0;i<pos;i++)
    {
    	if(elementos[i]==p)
    	{
    		while(elementos[pos]==p && pos>i)
    			pos--;

    		aux=elementos[pos];
            elementos[pos]=elementos[i];
            elementos[i]=aux;
    	}
    }

    /*****DEBUG****for (int i=inicio;i<=fin;i++)  // Recorrer vector
	{
		cout<<elementos[i]<<" ";
	}
	cout<<endl;
	cout<<endl;*/
	
	//Devuelvo un pair que indica en la primera posicion el valor hasta el que se encuentran los menores
	//y en la derecha el valor a partir del que se encuentran los mayores, coinciden tanto para pies
	//como para zapatos ya que ambos tienen los mismos elementos, por lo tanto al aplicar el pivote
	//ambos quedan con los menores y mayores a partir de las mismas posiciones
	return make_pair(pos,k);
}

pair<int,int> moda(int *elementos,int inicio,int fin)
{
	pair<int,int> resultado;

	if(inicio-fin==0) //si el vector solo tiene un elemento devuelvo el elemento y su frequencia que es 1
	{
		resultado=make_pair(elementos[inicio],1);
	}
	else
	{
		//Obtengo el pivote
		pair<int,int> p=pivote(elementos,inicio,fin);

		int het_men=0;
		for(int i=inicio;i<p.first;i++)
		{
			het_men++;
		}

		int hom=0;
		for(int i=p.first;i<p.second;i++)
		{
			hom++;
		}

		int het_may=0;
		for(int i=p.second;i<=fin;i++)
		{
			het_may++;
		}
		

		if(hom>het_may && hom>het_men)
		{
			resultado=make_pair(elementos[p.first],hom);
		}
		else
		{
			//Ahora llamo recursivamente para comprobar los heterogeneos mayores y menores
			pair<int,int> homogeneos_menores,homogeneos_mayores;

			homogeneos_menores=moda(elementos,inicio,p.first-1);
			homogeneos_mayores=moda(elementos,p.second,fin);

			//Ahora escogemos cual es el numero que se repite mas, que será la moda, en caso de que haya
			//varios numero moda, se quedará con el que primero aparezca, primero el de homogeneos, luego
			//el de la recurrencia sobre los menores y luego el de la recurrencia sobre los mayores
			if(hom>=homogeneos_menores.second && hom>=homogeneos_mayores.second)
			{
				resultado=make_pair(elementos[p.first],hom);
			}
			else if(homogeneos_menores.second>=hom && homogeneos_menores.second>=homogeneos_mayores.second)
			{
				resultado=homogeneos_menores;
			}
			else
			{
				resultado=homogeneos_mayores;
			}
		}
		
	}

	return resultado;
}

int main(int argc, char * argv[])
{
	if (argc!=2)
	{
		cout<<"Formato: ./zapatos numero-de-niños/zapatos"<<endl;
		return -1;
	}

	int tam=atoi(argv[1]);	// Tamaño de la matriz

	//Creo el vector de zapatos y pies
	int *elementos=new int[tam];

	srand(time(0));            // Inicialización del generador de números pseudoaleatorios

	cout<<"Conjunto de elementos:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		elementos[i]=rand()%tam;    // Generar aleatorio [0,5]
		cout<<elementos[i]<<" ";
	}
	cout<<endl;

	pair<int,int> moda_freq=moda(elementos,0,tam-1);

	cout<<"Elemento moda: "<<moda_freq.first<<", numero de veces que aparece: "<<moda_freq.second<<endl;
}