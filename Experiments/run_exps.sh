#!/bin/bash

echo "Running experiments.. "

for instance in *.ins
do
	echo "Instance: " $instance
	echo
	echo "Running experiment 1..."
	[ -e "Results/exp_results_$instance.csv" ] && rm Results/exp_results_$instance.csv
	echo "\"Function Value\",\"Number of Vehicles\",Time" >> Results/exp_results_$instance.csv
	sh exp.sh $instance >> Results/exp_results_$instance.csv
	echo
	echo "Running experiment 2..."
	[ -e "Results/exp1_results_$instance.csv" ] && rm Results/exp1_results_$instance.csv
	echo "\"Function Value\",\"Number of Vehicles\",Alpha,Seed,Time" >> Results/exp1_results_$instance.csv
	sh exp1.sh $instance >> Results/exp1_results_$instance.csv
	echo
	echo "Running experiment 3..."
	[ -e "Results/exp2_results_$instance.csv" ] && rm Results/exp2_results_$instance.csv
	echo "\"Function Value\", \"Number of Vehicles\",Alpha,Seed,Time" >> Results/exp2_results_$instance.csv
	sh exp2.sh $instance >> Results/exp2_results_$instance.csv
	echo
done
