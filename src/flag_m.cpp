using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <sys/stat.h>

#include "path.h"
#include "config_getter.h"
#include "utils.h"
#include "safety.h"
#include "flag_m.h"




void create_standard_main_file (string path, string extension) {
	int exit_code;
	vector<char*> cmd;

	extension_safety (path, extension);
	
	LOAD_CMD ("bash");	
	LOAD_CMD (CPY_FILES_SCRIPT_PATH);

	if ( extension == "c" )
		LOAD_CMD (STANDARD_C_MAIN_FILE);
	else if ( extension == "cpp" )
		LOAD_CMD (STANDARD_CPP_MAIN_FILE);
	else if ( extension == "cc" )
		LOAD_CMD (STANDARD_CC_MAIN_FILE);
	else
		interupt(0, "\033[1;31merror\033[0m: Unrecognized extension \'%s\'",
			extension.c_str());

	LOAD_CMD (path.c_str());

	execute (exit_code, BASH_PATH, cmd);
	if (exit_code)
		return;

	if ( extension == "c" )
		cout << "\033[1;32minfo\033[0m: created a standard main C file at " 
			<< path << ".\n"; 
	else
		cout << "\033[1;32minfo\033[0m: created a standard main C++ file at " 
			<< path << ".\n"; 
}




void create_standard_include (string file_name, string include_path) {
	int exit_code;
	vector<char*> cmd;

	LOAD_CMD ("bash");
	LOAD_CMD (ADD_HEADER_SCRIPT_PATH);
	LOAD_CMD ("0");
	LOAD_CMD (file_name.c_str());
	LOAD_CMD (include_path.c_str());

	cout << execute (exit_code, BASH_PATH, cmd);
	if (exit_code)
		return;

	cout << "\033[1;32minfo\033[0m: created standard header " 
		<< file_name << ".\n";
}




void create_dir (string path) {
    if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        cout << "\033[1;32minfo\033[0m: directory \""<< path
			<< "\" wasn't created. It must already exist.\n";
    } else {
		cout << "\033[1;32minfo\033[0m: created directory \"" << path
			<< "\".\n";
	}
	
}




string parse_path (const char * path, const char * extension,
	int type) {

	vector<string> directories;	 
	string path_str = path;
	string extension_str = extension;
	stringstream ss(path_str);
	string token, dynamic_path = "./";

    while ( getline(ss, token, '/') ) {
		if ( token == "." || token == ".." )
			continue;
        else if ( has_dot (token) ) {
			if (type == IS_SOURCE)
				create_standard_main_file (path, extension_str);
			else if ( type == IS_INCLUDE )
				create_standard_include (token, dynamic_path);
			else {
				cerr << "\n\033[1;31merror\033[0m: ";
				cerr << token << "should be a directory.";
				exit (EXIT_FAILURE);
			}
		}
		else {
			dynamic_path += token + '/';
			create_dir (dynamic_path);
		}
    }

	return dynamic_path;
}




void flag_m () {
	if ( file_exists ("Makefile") || file_exists ("makefile") ) {
		cerr << "\n\033[1;31merror\033[0m: There is already a Makefile";
		cerr << " in the current directory." << endl;
		exit (EXIT_FAILURE);
	}

	int exit_code;
	string opt_0, opt_1, opt_2, opt_3, opt_4, opt_5, opt_6, opt_7;

	GET_CONFIG (
		opt_5 = parse_path (ds->source, ds->c_extension, IS_SOURCE);
		opt_3 = parse_path (ds->include, ds->h_extension, IS_INCLUDE);
		parse_path (ds->object, "?", IS_OTHER);
		parse_path (ds->bin, "?", IS_OTHER);

		opt_0 = strlen(ds->c_extension) == 1 ? "gcc" : "g++";
		opt_1 = ds->c_extension;
		opt_2 = ds->h_extension;

		opt_4 = ds->name;
		
		opt_6 = ds->object;
		opt_7 = ds->bin;
	)

	vector<char*> cmd;
	LOAD_CMD("bash");
	LOAD_CMD (BUILD_MAKEFILE_SCRIPT_PATH);
	LOAD_CMD (opt_0.c_str());
	LOAD_CMD (opt_1.c_str());
	LOAD_CMD (opt_2.c_str());
	LOAD_CMD (opt_3.c_str());
	LOAD_CMD (opt_4.c_str());
	LOAD_CMD (opt_5.c_str());
	LOAD_CMD (opt_6.c_str());
	LOAD_CMD (opt_7.c_str());
	LOAD_CMD (MAKEFILE_TEMPLATE_PATH);

	execute (exit_code, BASH_PATH, cmd);
	CHECK_CODE (exit_code);

	cout << "\n\033[1;32minfo\033[0m: Successfully created the Makefile !\n";
}