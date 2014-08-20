#!/bin/sh

P_IMG=$1
P_AREA=$2

# cleanup
rm -rf dotfiles/*
F_CURDIR=`pwd`

# create wiki files ...

F_NAME=cmdCreateWikiAreaPages.xml
F_XNAME=$F_NAME.in
F_IMAGE_PATH="../../../../images/dot/aHuman"

if [ "$P_AREA" = "" ]; then
	echo create wiki files ...
	sed "s/@AREA@//;s/@CREATEALL@/true/" $F_NAME > $F_XNAME
else
	echo create wiki page $P_AREA ...
	sed "s/@AREA@/$P_AREA/;s/@CREATEALL@/false/" $F_NAME > $F_XNAME
fi

tools console -s localhost:20002 -i $F_XNAME -o $F_NAME.out

if [ "$P_IMG" = "yes" ]; then
	# wait
	echo press enter to continue...
	read x

	cd $F_CURDIR
	echo create images ...

	for x in `find dotfiles -name "*.dot"`; do
		echo create image from dot file $x ...
		fname=`basename $x`
		dot -Tpng dotfiles/$fname -o $F_IMAGE_PATH/$fname.png
	done
fi

echo successfully done.
