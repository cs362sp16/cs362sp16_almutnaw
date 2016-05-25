#!/bin/bash

# Check if the num of parameters is correct
if [ "$#" -ne 3 ]; then
	echo "Wrong number of parameters"
	echo "diffdominion.sh [directory 1] [directory 2] [seed]"
	exit
fi



# get the name of directories in variables
directory1=$1
directory2=$2
seed=$3

# clean directory and run make
make clean
make all


# move to the second directory and clean and make all
cd $directory2
make clean
make all

cd -


output1="file1.out"
output2="file2.out"
domc="dominion.c"
testdom="testdominion"


$directory1$testdom $seed > $directory1$output1
$directory2$testdom $seed > $directory1$output2

diff $directory1$output1 $directory1$output2 > dominionDifferences.diff
gcov $directory1$domc >> dominionDifferences.diff
gcov $directory2$domc >> dominionDifferences.diff


# check if the two outputs are simmilar or different
if [ ! -s dominionDifferences.diff ]
then
	echo "TEST PASSED"
else
	echo "TEST FAILED"
fi