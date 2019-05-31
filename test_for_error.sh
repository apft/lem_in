#!/bin/sh

for i in $@
do
	echo $i
	./lem-in < $i > /dev/null
	[ $? -ne 0 ] && echo "KO"
done
