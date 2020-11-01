#!bin/bash/

# $1: SOURCE
# $2: DEST

if [ "$#" -ne 2 ]; then
	>&2 echo "error: Missing arguments in script cpy_files.sh".
	exit 1
fi

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'

if test -f "$2"; then
	>&2 echo -e "${GREEN}info${NC}: \"$2\" wasn't created. It must already exist."
	exit 1
fi

cp $1 $2

if [ $? -eq 1 ]; then
	>&2 echo ""
	>&2 echo -e "error: copying $1 into $2".
	exit 1
fi