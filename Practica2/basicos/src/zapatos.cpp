#include <iostream>
#include <cstdlib>  //Para generación de números pseudoaleatorios
#include <algorithm> //Para desordenar el vector de pies
#include <utility> //Para hacer pair
using namespace std;

int pivote(int *zapatos,int *pies, int inicio, int fin)
{
	int p,p2,k,l,aux;
	k=inicio;
	p=zapatos[inicio];
	l=fin;

	//Ejecuto el funcionamiento del pivote para los pies, por lo que el pivote
	//obtenido proviene de los zapatos
	while(pies[k]<p && k<fin)
		k++;

	while(pies[l]>=p && l>inicio)
	{
		if(pies[l]==p)
			p2=pies[l];

		if(pies[l]==p && pies[k]>pies[l])
		{
			//swap pies[k] con pies[l]
			aux=pies[k];
			pies[k]=pies[l];
			pies[l]=aux;
		}

		l--;
	}

	while(k<l)
	{
		//swap pies[k] con pies[l]
		aux=pies[k];
		pies[k]=pies[l];
		pies[l]=aux;

		while(pies[k]<p)
			k++;

		while(pies[l]>=p)
		{
			if(pies[l]==p)
				p2=pies[l];

			if(pies[l]==p && pies[k]>pies[l])
			{
				//swap pies[k] con pies[l]
				aux=pies[k];
				pies[k]=pies[l];
				pies[l]=aux;
			}

			l--;
		}
	}

	k=inicio;
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
	
	return l;
}

void tallas(int *zapatos,int *pies,int inicio,int fin)
{
	if(inicio<fin)
	{
		int p=pivote(zapatos,pies,inicio,fin);

		if(p>inicio)
		{
			if(p==fin)
				tallas(zapatos,pies,inicio,p-1);
			else
            	tallas(zapatos,pies,inicio,p);
		}

      	if(p<fin)
      	{
      		if(p==inicio)
      			tallas(zapatos,pies,p+1,fin);	
      		else
      			tallas(zapatos,pies,p,fin);	
      	}
	}
/*
	int i=inicio;
	int j=fin;
    int tmp;
    int p=zapatos[inicio];
    int p2;
 
 	//Funcion pivote con los pies
    while(i<j) 
    {
    	tmp=pies[i];
        pies[i]=pies[j];
        pies[j]=tmp;

    	while(pies[i]<=p)
    	{
    		if(pies[i]==p)
    			p2=pies[i];

    		if(pies[i]!=pies[j])
    			i++;
    	}

    	do{
    		j++;
    	}while(pies[j]>p);

        if(pies[i]==p)
    		p2=pies[i];

    	if(pies[j]==p)
    		p2=pies[j];
    }

    i=inicio;
	j=fin;

	cout<<"pivote 1: "<<p<<" pivote 2: "<<p2<<endl;
    
    //Funcion pivote con los zapatos
    while(i<=j) 
    {
        while(zapatos[i]<p)
        {
            i++;
        }

        while(zapatos[j]>p)
        {
            j--;
        }

        if(i<=j)
        {
            tmp=zapatos[i];
            zapatos[i]=zapatos[j];
            zapatos[j]=tmp;
            i++;
            j--;
        }
    }

    if(inicio<j)
    {
    	tallas(zapatos,pies,inicio,j);
    }

    if(i<fin)
    {
    	tallas(zapatos,pies,i,fin);
    }*/
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