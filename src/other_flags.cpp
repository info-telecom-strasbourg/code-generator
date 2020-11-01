using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#include <unistd.h>

#include "config_getter.h"
#include "utils.h"
#include "path.h"
#include "other_flags.h"




void flag_t (char * optarg_) {
	int exit_code;
	vector<char*> cmd;

	LOAD_CMD ("bash");
	LOAD_CMD (LOAD_TEMPLATE_SCRIPT_PATH);
	LOAD_CMD (optarg_);
	LOAD_CMD (LOAD_TEMPLATES_DIR_PATH);

	cout << execute (exit_code, BASH_PATH, cmd);
	CHECK_CODE (exit_code);
}




void create_file (string name, string ext, string dir, int type) {
	int exit_code;
	vector<char*> cmd;
	
	string new_file = type == IS_SOURCE 
		? dir + "/" + name + "." + ext
		: name + "." + ext;

	LOAD_CMD ("bash");	
	
	if (type == IS_SOURCE) {
		LOAD_CMD (CPY_FILES_SCRIPT_PATH);

		if ( ext == "c" )
			LOAD_CMD (STANDARD_C_FILE);
		if ( ext == "cpp" )
			LOAD_CMD (STANDARD_CPP_FILE);
		if ( ext == "cc" )
			LOAD_CMD (STANDARD_CC_FILE);

		LOAD_CMD (new_file.c_str());

	}

	if (type == IS_INCLUDE) {
		LOAD_CMD (ADD_HEADER_SCRIPT_PATH);
		LOAD_CMD ("0");
		LOAD_CMD (new_file.c_str());
		LOAD_CMD (dir.c_str());
	}

	execute (exit_code, BASH_PATH, cmd);
	if ( !exit_code )
		cout << "\033[1;32minfo\033[0m: created a new standard file at \"" 
			<< new_file << "\".\n"; 
}




void flag_a (char *optarg_) {
	string name, ext_c, ext_h, src, include, extension;
	string optarg_str = optarg_;

	parse_extension (optarg_, extension);

	if (extension != optarg_) {
		cout << "\033[1;33mwarning\033[0m: ignoring \""<< extension
 			<< "\". Using the extensions defined in the config file.\n\n";
	}

	name = optarg_str.substr(0, optarg_str.length() - extension.length() - 1);

	GET_CONFIG (

	ext_c = ds->c_extension;
	ext_h = ds->h_extension;
	src = cut_file (ds->source);
	include = cut_file (ds->include);

	)
	
   	create_file (name, ext_c, src, IS_SOURCE);
   	create_file (name, ext_h, include, IS_INCLUDE);
}




void flag_c () {
	int exit_code;
	vector<char*> cmd;

	LOAD_CMD ("bash");
	LOAD_CMD (CPY_FILES_SCRIPT_PATH);
	LOAD_CMD (BLANK_CONFIG_FILE_PATH);
	LOAD_CMD (".");

	cout << execute (exit_code, BASH_PATH, cmd);
	CHECK_CODE (exit_code);

	cout << "\033[1;32minfo\033[0m: added codegen_config.txt to the"
		<< " directory.\n";  
}




void flag_d () {
	int exit_code;
	vector<char*> cmd;

	LOAD_CMD ("rm");
	LOAD_CMD ("codegen_config.txt");
	LOAD_CMD (".codegen_config_bin");

	cout << execute (exit_code, RM_PATH, cmd);
	CHECK_CODE (exit_code);

	cout << "\033[1;32minfo\033[0m: removed all codegen setup files.\n";  
}