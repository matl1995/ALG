#!/bin/bash -vx
echo > salidapermutacion.dat
for ((i=100;i<=30000;i=i+100))
do
./pruebapermutacion $i 10 >> salidapermutacion.dat
done
