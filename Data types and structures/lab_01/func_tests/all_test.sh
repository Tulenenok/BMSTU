#!/bin/bash

RED="\033[0;31m" 
GREEN="\033[0;32m"
BLUE="\033[0;34m"
export RED
export GREEN

for file_in in ./pos_??_in.txt
do
	n=${file_in:6:2}
	./pos_test.sh "$n"
done

echo " "

for file_in in ./neg_??_in.txt
do
    n=${file_in:6:2}
	./neg_test.sh "$n"
done