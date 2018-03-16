#!/bin/bash -vx
echo > salidamergesort.dat
for ((i=100;i<=10000;i=i+100))
do
./mergesort $i >> salidamergesort.dat
done
