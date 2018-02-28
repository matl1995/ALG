#!/bin/bash -vx
echo > salidainsercion.dat
for ((i=1000;i<=50000;i=i+1000))
do
./insercion $i 10000 >> salidainsercion.dat
done
