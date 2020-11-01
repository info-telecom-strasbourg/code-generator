#!bin/bash/

RED='\033[1;31m'
ORANGE='\033[1;33m'
YELLOW='\033[0;33m'
NC='\033[0m'

CONFIG_FILE="codegen_config.txt"

no_output () {
	if [ $2 -eq 1 ]; then
		>&2 printf "${RED}error$NC"
		>&2 echo ": no $1 files were found."
		exit 1
	else 
		>&2 printf "${ORANGE}warning$NC"
		>&2 echo ": no $1 files were found."
		>&2 echo "Using current directory by default."
		>&2 echo ""
	fi
}


source=$(find . -type f -name "*.c" \
	-o -type f -name "*.cpp" -o -type f -name "*.cc" |
	awk '{n=gsub("/","/",$0);printf "%04d/%s\n",n,$0}' |
	sort -t/ |
	sed 's|[^/]*/||')

if [ -z "$source" ]; then
	no_output "source" 1
	towrite_source="."
else
	source_name=$(echo $source | cut -d' ' -f1)
	towrite_source=$(dirname $source_name)
	filename=$(basename -- "$source_name")
	extension="${filename##*.}"
	towrite_cextension=$extension
fi


include=$(find . -type f -name "*.h" \
	-o -type f -name "*.hpp" |
	awk '{n=gsub("/","/",$0);printf "%04d/%s\n",n,$0}' |
	sort -t/ |
	sed 's|[^/]*/||')

if [ -z "$include" ]; then
	no_output "include" 0
	towrite_include="."
	towrite_hextension="h"
else
	name=$(echo $include | cut -d' ' -f1)
	towrite_include=$(dirname $name)
	filename=$(basename -- "$name")
	extension="${filename##*.}"
	towrite_hextension=$extension
fi


object=$(find . -type f -name "*.o" |
	awk '{n=gsub("/","/",$0);printf "%04d/%s\n",n,$0}' |
	sort -t/ |
	sed 's|[^/]*/||')

if [ -z "$object" ]; then
	no_output "object" 0
	towrite_object="."
	object_file="."
else
	name=$(echo $object | cut -d' ' -f1)
	towrite_object=$(dirname $name)
	object_file=$(dirname $name)
fi


BIN_FILES=$(find . \( ! -regex '.*/\..*' \) -type f | perl -lne 'print if -B') 
for f in $BIN_FILES; 
do 
	f_dir=$(dirname $f)

	if [[ "$f_dir" == "$object_file" ]]; then
		continue
	fi

	filename=$(basename -- "$f")
	extension="${filename##*.}"

	towrite_bin=$f_dir
	towrite_name=$filename
	break
done

source_name=$(basename $source_name)
source_name="${source_name%.*}"

>&2 printf "${ORANGE}warning$NC"
>&2 echo ": no binary file was found"
>&2 echo "Using current directory by default"
>&2 echo -e "Using target \"${YELLOW}$source_name${NC}\" by default."

towrite_bin="."
towrite_name=$source_name

> $CONFIG_FILE

echo "Source = $towrite_source" >> $CONFIG_FILE
echo "Extensions = $towrite_cextension/$towrite_hextension" >> $CONFIG_FILE
echo "Include = $towrite_include" >> $CONFIG_FILE
echo "Object = $towrite_object" >> $CONFIG_FILE
echo "Bin = $towrite_bin" >> $CONFIG_FILE
echo "Name = $towrite_name" >> $CONFIG_FILE