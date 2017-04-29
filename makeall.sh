#!/bin/bash

for dir in ~/GitHub/CPP/*/
do 
	echo "$dir"
	cd "$dir" && make
done
