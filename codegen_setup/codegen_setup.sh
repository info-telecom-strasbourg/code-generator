#!bin/bash/

# $1: FILE
# $2: codegen path

CONFIG_PRE_PARSER_BIN="$2/codegen_setup/config_pre_parser/config_pre_parser"

CONFIG_PARSER_BIN="$2/codegen_setup/config_parser/config_parser"

$CONFIG_PRE_PARSER_BIN < $1 | $CONFIG_PARSER_BIN
