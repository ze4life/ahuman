#!/bin/sh

# cleanup
F_CURDIR=`pwd`

# verify model spinal cord ...
echo verify spinal cord ...
F_NAME=cmdVerifySpinal.xml
tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

echo successfully done.
