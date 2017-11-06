#!/bin/bash

X=10

for i in {1..4}
do
	echo $X
	time ./ex1 $X >> out.txt
	echo " " >> out.txt
	X+=0
done

echo "You can find you output in out.txt !"
