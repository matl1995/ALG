#!/bin/bash -vx
echo > salidamoda.dat
for ((i=1000;i<=200000;i=i+1000))
do
./moda $i >> salidamoda.dat
done
