#!/bin/bash

for dir in ~/Development/GitHub/CPP/*/
do 
	echo "$dir"
	cd "$dir" && make
done
