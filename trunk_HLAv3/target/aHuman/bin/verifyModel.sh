#!/bin/sh

# cleanup
F_CURDIR=`pwd`

# verify model ...
echo verify model ...
F_NAME=cmdVerifyModel.xml
tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

echo successfully done.
