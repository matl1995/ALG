#!/bin/bash -vx
echo > salidaburbuja.dat
for ((i=1000;i<=50000;i=i+1000))
do
./burbuja $i 10000 >> salidaburbuja.dat
done
