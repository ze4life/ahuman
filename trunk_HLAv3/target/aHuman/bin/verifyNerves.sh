#!/bin/sh

# cleanup
F_CURDIR=`pwd`

# verify model nerves ...
echo verify model nerves ...
F_NAME=cmdVerifyNerves.xml
tools console -s localhost:20002 -i $F_NAME -o $F_NAME.out

echo successfully done.
