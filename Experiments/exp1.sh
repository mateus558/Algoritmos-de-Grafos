#!/bin/bash

for i in `seq 0 29`
do
	number=$(sh rand.sh)
	rands[i]=$((number))
done

for a in 0.1 0.2 0.3
do
	for i in `seq 0 29`
	do
		res=$(./cvrp1 $1 $a ${rands[i]}) 
		echo $res 
	done
	echo 
done	

