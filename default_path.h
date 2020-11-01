#ifndef CODEGEN_PATH_INCLUDE_GUARD
#define CODEGEN_PATH_INCLUDE_GUARD

/**
 * This file is used to centralize every path used by codegen.
 * The idea behind this centralization is to be able to modify
 * the path of codegen easyly; without needing to change multiple
 * files.
 *
 * This is the default file, where $PATH was not yet replaced by the
 * correct path of codegen. The script set_path.sh will make a copy
 * of this default file and change $PATH. Then, it will add it to 
 * ./include under the name path.h
 *
 */

#define BASH_PATH "$BASH_PATH"

#define DIRNAME_PATH "$DIRNAME_PATH"

#define RM_PATH "$RM_PATH"

#define CODEGEN_PATH "$PATH"

#define CODEGEN_SETUP_SCRIPT_PATH "$PATH/codegen_setup/codegen_setup.sh"

#define CODEGEN_DIR_PARSING_SCRIPT_PATH "$PATH/codegen_setup/parse_dir_struct.sh"

#define CODEGEN_DIR_PARSING_BIN_PATH "$PATH/codegen_setup/codegen_setup"

#define CPY_FILES_SCRIPT_PATH "$PATH/scripts/cpy_files.sh"

#define ADD_HEADER_SCRIPT_PATH "$PATH/scripts/add_header.sh"

#define BUILD_MAKEFILE_SCRIPT_PATH "$PATH/scripts/build_makefile.sh"

#define MAKEFILE_TEMPLATE_PATH "$PATH/user/makefile/Makefile"

#define STANDARD_C_MAIN_FILE "$PATH/user/standard_files/smf.c"

#define STANDARD_C_FILE "$PATH/user/standard_files/sf.c"

#define STANDARD_CPP_MAIN_FILE "$PATH/user/standard_files/smf.cpp"

#define STANDARD_CPP_FILE "$PATH/user/standard_files/sf.cpp"

#define STANDARD_CC_MAIN_FILE "$PATH/user/standard_files/smf.cc"

#define STANDARD_CC_FILE "$PATH/user/standard_files/sf.cc"

#define LOAD_TEMPLATE_SCRIPT_PATH "$PATH/scripts/load_template.sh"

#define LOAD_TEMPLATES_DIR_PATH "$PATH/user/templates/"

#define BLANK_CONFIG_FILE_PATH "$PATH/user/codegen_config.txt"

#endif
