#!/bin/bash

for i in `seq 0 29`
do
	number=$(sh rand.sh)
	rands[i]=$((number))
done

for i in `seq 0 29`
do
	res=$(./cvrp2 $1 1500 100 0.1 10 ${rands[i]}) 
	echo $res 
done
echo 
		
