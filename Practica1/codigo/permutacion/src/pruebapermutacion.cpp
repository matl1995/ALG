#include <iostream>
#include "permutacion.h"
#include <string> 
template <class T>
ostream & operator<<(ostream &os, const vector<T> & d){
   for (int i=0;i<d.size();i++)
      os<<d[i]<<" ";
   os<<endl;
   return os;
}

void MuestraPermutaciones(const Permutacion & P){
  Permutacion::const_iterator it;
  int cnt=1;
  for (it=P.begin();it!=P.end();++it,++cnt)
      cout<<cnt<<"->"<<*it<<endl;
      
}


void ImprimeCadena(const string &c,const Permutacion &P){
  const vector<unsigned int> s= (*(P.begin()));
  
  for (unsigned int i=0;i<s.size();i++)
     cout<<c[s[i]-1];
  cout<<endl;
}

int main(){
  int n;
  cout<<"Dime el tamaño de las permutaciones:";
  cin>>n;
  
  Permutacion P(n);
  cout<<"El numero total de permutaciones: "<<P.NumeroPermutacionesPosibles()<<endl;
  MuestraPermutaciones(P);
   
  //Para no tener almacenadas todas las permutaciones solo la acutal
  
  
  //Leemos una cadena y generamos todas sus permutaciones
  string cad;
  cout<<"Dime una palabra:";
  cin>>cad;
  Permutacion Otra(cad.size(),1);
  int cnt=1;
  do{
    cout<<cnt<<"-->";
    ImprimeCadena(cad,Otra);
    cnt++;
  }while(Otra.GeneraSiguiente());
}  
  
  
   
  
