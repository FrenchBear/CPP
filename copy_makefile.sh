#!/bin/bash

for folder in */
do
	echo $folder
	mv $folder/Makefile $folder/Makefile.bak
	cp Makefile $folder/Makefile
done
