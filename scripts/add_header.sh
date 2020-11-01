#!bin/bash/

# $1: 0 if it is a new header file
#     1 if it is a new header INSIDE the file [TODO]

# $2 : The file name (without a path)

# $3: the include path

# $4: what to add

RED='\033[1;31m'
ORANGE='\033[1;33m'
GREEN='\033[1;32m'
NC='\033[0m'

file=$2
include=$3
to_add=$4

if [ "$1" == "0" ]; then
	if test -f "$include/$file"; then
    	>&2 echo -e "${GREEN}info${NC}: \"$include/$file\" wasn't created. It must already exist."
		exit 1
	fi

	name=`basename $file`
	ext="${name##*.}"
	name="${name%.*}"

	touch $include/$file

	printf "#ifndef " >> $include/$file
	printf "%s\n" ${name}_H | tr a-z A-Z >> $include/$file 
	printf "#define " >> $include/$file 
	printf "%s\n" ${name}_H | tr a-z A-Z >> $include/$file 

	echo " " >> $include/$file

	echo "#endif" >> $include/$file
fi

# if [ "$1" == "1" ]; then
# 	endif_line=$(grep -n -m 1 "#endif" $include/$file | tail -1 | cut -d':' -f1)

# 	last_line=$(cat $include/$file | sed '/^[[:space:]]*$/d' | tail -1)

# 	if ! [ "$last_line" == "#endif" ]; then
# 		>&2 echo -e "${RED}error:${NC} Aborted to prevent corruption of data."
# 		>&2 echo "line $endif_line: last line of $file should only contain #endif."
# 		exit 1
# 	fi

# 	if grep -q "#endif" $include/$file; then
# 		sed -i "${endif_line}d" $include/$file
# 		echo " " >> $include/$file
# 		echo "$to_add" >> $include/$file
# 		echo " " >> $include/$file
# 		echo "#endif" >> $include/$file
# 	else
# 		echo -e "\n$to_add" >> $include/$file
# 	fi
# fi