#!/bin/bash -vx
echo > salidaabb.dat
for ((i=500;i<=30000;i=i+500))
do
./usoabb $i 10000 >> salidaabb.dat
done
