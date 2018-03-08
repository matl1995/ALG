#!/bin/bash -vx
echo > salidaapo.dat
for ((i=200;i<=200000;i=i+200))
do
./usoapo $i 10000 >> salidaapo.dat
done
