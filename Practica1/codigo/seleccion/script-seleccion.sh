#!/bin/bash -vx
echo > salidaseleccion.dat
for ((i=1000;i<=50000;i=i+1000))
do
./seleccion $i 10000 >> salidaseleccion.dat
done
