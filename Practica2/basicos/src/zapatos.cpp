#include <iostream>
#include <cstdlib>  //Para generación de números pseudoaleatorios
#include <algorithm> //Para desordenar el vector de pies
#include <utility> //Para hacer pair
using namespace std;

pair<int,int> pivote(int *zapatos/*,int *pies*/, int inicio, int fin)
{
	int p,k,l,aux;
	k=inicio;
	p=zapatos[(inicio+fin)/2];
	cout<<"pivote seleccionado: "<<p<<endl;
	l=fin;

	//Ejecuto el funcionamiento del pivote para los pies, por lo que el pivote
	//obtenido proviene de los zapatos
    while(k<l)
    {
        while(zapatos[k]<=p && k<=fin)
            k++;

        while(zapatos[l]>p && l>=inicio)
			l--;

        if(k<l)
        {
            aux=zapatos[k];
            zapatos[k]=zapatos[l];
            zapatos[l]=aux;
        }
    }

    //Coloco los elementos pivote a la izquierda de la posición final
    //que tendrá el pivote
    int pos=k-1;
    for(int i=0;i<pos;i++)
    {
    	if(zapatos[i]==p)
    	{
    		while(zapatos[pos]==p && pos>i)
    			pos--;

    		aux=zapatos[pos];
            zapatos[pos]=zapatos[i];
            zapatos[i]=aux;
    	}
    }

	return make_pair(pos,k);

	/*k=inicio;
	l=fin;

	//Ejecuto el funcionamiento del pivote para los zapatos, por lo que el pivote
	//obtenido proviene de los pies, cogiendo el valor de la posicion del pivote ya
	//obtenido para pies, para que se nos queden los dos ordenados igual
	//Ejecuto el funcionamiento del pivote para los pies, por lo que el pivote
	//obtenido proviene de los zapatos
	while(zapatos[k]<p2 && k<fin)
		k++;

	while(zapatos[l]>=p2 && l>inicio)
	{
		if(zapatos[l]==p2 && zapatos[k]>zapatos[l])
		{
			//swap pies[k] con pies[l]
			aux=zapatos[k];
			zapatos[k]=zapatos[l];
			zapatos[l]=aux;
		}

		l--;
	}

	while(k<l)
	{
		//swap pies[k] con pies[l]
		aux=zapatos[k];
		zapatos[k]=zapatos[l];
		zapatos[l]=aux;

		while(zapatos[k]<p2)
			k++;

		while(zapatos[l]>=p2)
		{
			if(zapatos[l]==p2 && zapatos[k]>zapatos[l])
			{
				//swap pies[k] con pies[l]
				aux=zapatos[k];
				zapatos[k]=zapatos[l];
				zapatos[l]=aux;
			}

			l--;
		}
	}
	
	return l;*/
}

void tallas(int *zapatos/*,int *pies*/,int inicio,int fin)
{
	if(inicio<fin)
	{
		pair<int,int> p=pivote(zapatos,inicio,fin);

		if(inicio<p.first-1)
			tallas(zapatos,inicio,p.first-1);

		if(p.second<fin)
      		tallas(zapatos,p.second,fin);
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
		//pies[i]=zapatos[i];
		cout<<zapatos[i]<<" ";
	}
	cout<<endl;

	//Desordeno pies
	//random_shuffle(&pies[0],&pies[tam]);
/*
	//Imprimo las tallas de los pies
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<pies[i]<<" ";
	}
	cout<<endl;
*/
	tallas(zapatos,0,tam-1);

	cout<<"Vectores despues de ordenar:"<<endl;
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<zapatos[i]<<" ";
	}
	cout<<endl;
/*
	for (int i=0;i<tam;i++)  // Recorrer vector
	{
		cout<<pies[i]<<" ";
	}
	cout<<endl;*/
}