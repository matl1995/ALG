#include <iostream>
#include <cstdlib>  //Para generación de números pseudoaleatorios
#include <algorithm> //Para desordenar el vector de pies
#include <utility> //Para hacer pair
using namespace std;

pair<int,int> pivote(int *zapatos,int *pies, int inicio, int fin)
{
	int p,k,l,aux;
	k=inicio;
	p=zapatos[(inicio+fin)/2];
	/***DEBUG***cout<<"valor de pivote="<<p<<endl;***/
	l=fin;

	//Ejecuto el funcionamiento del pivote para los pies, por lo que el pivote
	//obtenido proviene de los zapatos
    while(k<l)
    {
        while(pies[k]<=p && k<=fin)
            k++;

        while(pies[l]>p && l>=inicio)
			l--;

        if(k<l)
        {
            aux=pies[k];
            pies[k]=pies[l];
            pies[l]=aux;
        }
    }

    //Coloco los elementos con mismo valor que pivote a la izquierda
    //de la posición final que tendrá el pivote
    int pos=k-1;
    for(int i=0;i<pos;i++)
    {
    	if(pies[i]==p)
    	{
    		while(pies[pos]==p && pos>i)
    			pos--;

    		aux=pies[pos];
            pies[pos]=pies[i];
            pies[i]=aux;
    	}
    }

    //Inicializo los valores para ahora ejecutar el pivote sobre zapatos
	k=inicio;
	l=fin;
	int p2=pies[pos];


	//Ejecuto el funcionamiento del pivote para los zapatos, por lo que el pivote
	//obtenido proviene de los pies, obtenido en p2
	while(k<l)
    {
        while(zapatos[k]<=p2 && k<=fin)
            k++;

        while(zapatos[l]>p2 && l>=inicio)
			l--;

        if(k<l)
        {
            aux=zapatos[k];
            zapatos[k]=zapatos[l];
            zapatos[l]=aux;
        }
    }

    //Coloco los elementos con mismo valor que pivote a la izquierda
    //de la posición final que tendrá el pivote
    pos=k-1;
    for(int i=0;i<pos;i++)
    {
    	if(zapatos[i]==p2)
    	{
    		while(zapatos[pos]==p2 && pos>i)
    			pos--;

    		aux=zapatos[pos];
            zapatos[pos]=zapatos[i];
            zapatos[i]=aux;
    	}
    }

    /*****DEBUG****for (int i=inicio;i<=fin;i++)  // Recorrer vector
	{
		cout<<zapatos[i]<<" ";
	}
	cout<<endl;

	for (int i=inicio;i<=fin;i++)  // Recorrer vector
	{
		cout<<pies[i]<<" ";
	}
	cout<<endl;
	cout<<endl;*/
	
	//Devuelvo un pair que indica en la primera posicion el valor hasta el que se encuentran los menores
	//y en la derecha el valor a partir del que se encuentran los mayores, coinciden tanto para pies
	//como para zapatos ya que ambos tienen los mismos elementos, por lo tanto al aplicar el pivote
	//ambos quedan con los menores y mayores a partir de las mismas posiciones
	return make_pair(pos,k);
}

void tallas(int *zapatos,int *pies,int inicio,int fin)
{
	if(inicio<fin)
	{
		pair<int,int> p=pivote(zapatos,pies,inicio,fin);

		/***DEBUG*****cout<<"pivote para menores="<<p.first<<endl;
		cout<<"pivote para mayores="<<p.second<<endl;*/

		if(inicio<p.first-1)
			tallas(zapatos,pies,inicio,p.first-1);

		if(p.second<fin)
      		tallas(zapatos,pies,p.second,fin);
	}
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
	int *zapatos=new int[tam];
	int *pies=new int[tam];

	srand(time(0));            // Inicialización del generador de números pseudoaleatorios

	cout<<"Vectores antes de ordenar:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		zapatos[i]=rand()%tam;    // Generar aleatorio [0,5]
		pies[i]=zapatos[i];
		cout<<zapatos[i]<<" ";
	}
	cout<<endl;

	//Desordeno pies
	random_shuffle(&pies[0],&pies[tam]);

	//Imprimo las tallas de los pies
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<pies[i]<<" ";
	}
	cout<<endl;

	tallas(zapatos,pies,0,tam-1);

	cout<<"Vectores despues de ordenar:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<zapatos[i]<<" ";
	}
	cout<<endl;

	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<pies[i]<<" ";
	}
	cout<<endl;
}