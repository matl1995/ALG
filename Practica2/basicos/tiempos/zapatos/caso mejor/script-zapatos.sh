#!/bin/bash -vx
echo > salidazapatos.dat
for ((i=100;i<=50000;i=i+100))
do
./zapatos $i >> salidazapatos.dat
done
