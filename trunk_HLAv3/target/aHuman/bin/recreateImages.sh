#!/bin/sh

echo create images ...
F_IMAGE_PATH="../../../../images/dot/aHuman"

for x in `find dotfiles -name "*.dot"`; do
	echo create image from dot file $x ...
	fname=`basename $x`
	dot -Tjpg dotfiles/$fname -o $F_IMAGE_PATH/$fname.jpg
done

echo successfully done.
