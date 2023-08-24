#!/bin/bash 
gcc cache.c -o cache.x
echo "l1  c1  l2  c2  method  clock_type  intervalo";
read l1 c1 l2 c2 method clock_type x
for ((i=1; i<=x; i++))
do
   echo "$i"; 
   ./cache.x $l1 $c1 $l2 $c2 $method $clock_type
done