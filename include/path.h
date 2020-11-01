#ifndef CODEGEN_PATH_INCLUDE_GUARD
#define CODEGEN_PATH_INCLUDE_GUARD

/**
 * This file is used to centralize every path used by codegen.
 * The idea behind this centralization is to be able to modify
 * the path of codegen easyly; without needing to change multiple
 * files.
 *
 * This is the default file, where /home/goncalo/codegen was not yet replaced by the
 * correct path of codegen. The script set_path.sh will make a copy
 * of this default file and change /home/goncalo/codegen. Then, it will add it to 
 * ./include under the name path.h
 *
 */

#define BASH_PATH "/usr/bin/bash"

#define DIRNAME_PATH "/usr/bin/dirname"

#define RM_PATH "/usr/bin/rm"

#define CODEGEN_PATH "/home/goncalo/codegen"

#define CODEGEN_SETUP_SCRIPT_PATH "/home/goncalo/codegen/codegen_setup/codegen_setup.sh"

#define CODEGEN_DIR_PARSING_SCRIPT_PATH "/home/goncalo/codegen/codegen_setup/parse_dir_struct.sh"

#define CODEGEN_DIR_PARSING_BIN_PATH "/home/goncalo/codegen/codegen_setup/codegen_setup"

#define CPY_FILES_SCRIPT_PATH "/home/goncalo/codegen/scripts/cpy_files.sh"

#define ADD_HEADER_SCRIPT_PATH "/home/goncalo/codegen/scripts/add_header.sh"

#define BUILD_MAKEFILE_SCRIPT_PATH "/home/goncalo/codegen/scripts/build_makefile.sh"

#define MAKEFILE_TEMPLATE_PATH "/home/goncalo/codegen/user/makefile/Makefile"

#define STANDARD_C_MAIN_FILE "/home/goncalo/codegen/user/standard_files/smf.c"

#define STANDARD_C_FILE "/home/goncalo/codegen/user/standard_files/sf.c"

#define STANDARD_CPP_MAIN_FILE "/home/goncalo/codegen/user/standard_files/smf.cpp"

#define STANDARD_CPP_FILE "/home/goncalo/codegen/user/standard_files/sf.cpp"

#define STANDARD_CC_MAIN_FILE "/home/goncalo/codegen/user/standard_files/smf.cc"

#define STANDARD_CC_FILE "/home/goncalo/codegen/user/standard_files/sf.cc"

#define LOAD_TEMPLATE_SCRIPT_PATH "/home/goncalo/codegen/scripts/load_template.sh"

#define LOAD_TEMPLATES_DIR_PATH "/home/goncalo/codegen/user/templates/"

#define BLANK_CONFIG_FILE_PATH "/home/goncalo/codegen/user/codegen_config.txt"

#endif
