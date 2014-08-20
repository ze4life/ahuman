#!/bin/sh

# cleanup
F_CURDIR=`pwd`

# create wiki files ...

echo create wiki files ...
F_NAME=cmdCreateMusclePages.xml

tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

echo successfully done.
