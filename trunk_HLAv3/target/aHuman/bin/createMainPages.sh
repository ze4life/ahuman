#!/bin/sh

# create wiki files ...
echo create wiki files ...
F_NAME=cmdCreateMainPages.xml
tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

echo successfully done.
