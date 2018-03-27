#!/bin/bash -vx
echo > salidamaxmin.dat
for ((i=1000;i<=200000;i=i+1000))
do
./maxmin $i >> salidamaxmin.dat
done
