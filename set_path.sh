#!/bin/bash

DEFAULT_PATH="default_path.h"
PATH_H="path.h"
INCLUDE="./include"

cp $DEFAULT_PATH $PATH_H

USER_PATH=$(pwd)
BASH_PATH=$(which bash)

if [ "$?" -eq 1 ]; then
	>&2 echo "Please install which."
	rm $PATH_H
	exit 1
fi

DIRNAME_PATH=$(which dirname)
RM_PATH=$(which rm)

sed -i "s|\$BASH_PATH|$BASH_PATH|g" $PATH_H
sed -i "s|\$DIRNAME_PATH|$DIRNAME_PATH|g" $PATH_H
sed -i "s|\$RM_PATH|$RM_PATH|g" $PATH_H
sed -i "s|\$PATH|$USER_PATH|g" $PATH_H

mv $PATH_H $INCLUDE