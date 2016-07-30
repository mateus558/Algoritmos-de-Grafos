#!/bin/bash

RANGE=100000

number=$(( ( RANDOM % $RANGE )  + 1 ))

echo $number
