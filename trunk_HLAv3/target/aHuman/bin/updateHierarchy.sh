#!/bin/sh

# cleanup
rm -rf dotfiles/*
F_CURDIR=`pwd`

# create wiki files ...
echo create wiki files ...
F_NAME=cmdUpdateHierarchy.xml
tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

echo successfully done.
