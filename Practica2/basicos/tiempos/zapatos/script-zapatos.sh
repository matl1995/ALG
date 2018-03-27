#!/bin/bash -vx
echo > salidaminmax_matriz.dat
for ((i=50;i<=5000;i=i+50))
do
./minmax_matriz $i >> salidaminmax_matriz.dat
done
