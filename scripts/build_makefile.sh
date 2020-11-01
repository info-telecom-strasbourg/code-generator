#!/bin/bash

# g++ or gcc = $1

# CEXTENSION = $2
# HEXTENSION = $3

# INCLUDE_PATH = $4

# TARGET = $5

# SRCDIR = $6
# OBJDIR = $7
# BINDIR = $8

# MAKEFILE_TEMPLATE_PATH = $9

replace () { 
	sed -i "s|$1|$2|g" Makefile
}

cp "$9" "./Makefile"

replace "opt_0" "$1"
replace "opt_1" "$2"
replace "opt_2" "$3"
replace "opt_3" "$4"
replace "opt_4" "$5"
replace "opt_5" "$6"
replace "opt_6" "$7"
replace "opt_7" "$8"