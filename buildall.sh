#!/bin/bash

export STDCPP=gnu++2a
for dir in */
do 
	echo "$dir"
	pushd "$dir"
	make $*
	popd
	echo ""
done
