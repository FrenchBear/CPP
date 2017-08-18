#!/bin/bash

for dir in */
do 
	echo "$dir"
	pushd "$dir"
	make
	popd
done
