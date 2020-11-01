#!bin/bash/

# $1: Template name
# $2: Path to the templates folder

RED='\033[1;31m'
NC='\033[0m'

rm .codegen_config_bin &>/dev/null

if test -f "codegen_config.txt"; then
	>&2 echo ""
	>&2 echo -e "${RED}error${NC}: codegen_config.txt already exists."
	exit 1
fi

cp -a "$2$1/." "." 

if [ "$?" -ne "0" ]; then
	>&2 echo ""
	>&2 echo -e "${RED}error:${NC} Failed to load template $1."	
	>&2 echo "List of defined templates (under codegen/user/templates/):"
	>&2 ls "$2"
	exit 1
fi	

codegen -m 