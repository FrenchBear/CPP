#!/bin/bash

# For raspberry pi, add
# export STDCPP=gnu++14

for dir in */
do 
	echo "$dir"
	pushd "$dir"
	make
	popd
done
