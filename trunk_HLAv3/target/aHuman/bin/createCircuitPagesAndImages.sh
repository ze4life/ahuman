#!/bin/sh

# cleanup
rm -rf dotfiles/*
F_CURDIR=`pwd`

# create wiki files ...
echo create wiki files ...
F_NAME=cmdCreateCircuitPages.xml
tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

# wait
echo press enter to continue...
read x

cd $F_CURDIR
echo create images ...
F_IMAGE_PATH="../../../../images/dot/aHuman"

for x in `find dotfiles -name "*.dot"`; do
	echo create image from dot file $x ...
	fname=`basename $x`
	dot -Tjpg dotfiles/$fname -o $F_IMAGE_PATH/$fname.jpg
done

echo successfully done.
