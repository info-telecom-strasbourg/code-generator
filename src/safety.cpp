using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "utils.h"
#include "safety.h"

void extension_safety ( string path, string extension ) {
	string path_extension;

	parse_extension (path, path_extension);

	if ( path_extension != "c" && path_extension != "cc" 
		&& path_extension != "cpp") {
		cerr << "\nIn: " << path << endl;
		interupt(0, "\033[1;31merror\033[0m: Unrecognized extension \'%s\'",
			path_extension.c_str());
	}

	if ( extension == path_extension )
		return;

	cerr << endl;
	cerr << "\033[1;35mimportant warning\033[0m: The extension of " << path;
	cerr << " does not match the extension defined in the configuration";
	cerr << " file (which is " << extension << ", while the path's one is ";
	cerr << path_extension << ")." << endl;
	cerr << "\nThe chosen extension is " << extension;
	cerr << " so the nature of the file might not match the extension of its";
	cerr << " path." << endl;
	cerr << endl;
}