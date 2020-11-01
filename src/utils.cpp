#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <list>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <pthread.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#include "utils.h"
#include "path.h"




void interupt(int syserr, const char * msg, ...) {
	va_list ap;

	va_start(ap, msg);
	vfprintf(stderr, msg, ap);
	fprintf (stderr, "\n");
	va_end(ap);

	if (syserr == 1)
		perror("");

	exit(EXIT_FAILURE);
}




bool file_exists (const char * name) {
    return ( access( name, F_OK ) != -1 );
}




bool has_dot (string token) {
	for (auto & c : token) {
		if ( c == '.' )
			return true;
	}
	return false;
}




string __execute__ (int * exit_code, size_t * len, const char * path, 
	char * const cmd []) {

	int err_reason, pipefd [2];
	
	string cmd_output_str;
	char buf [BUFSIZ];
	
	FILE * cmd_output;

	size_t nbytes = 0;
	*len = 0;

	CHECK (pipe (pipefd));

	switch (fork ()) {
	case -1 :
		interupt (1, "fork failed.");
		break;
	
	case 0 :
		CHECK (dup2 (pipefd[1], STDOUT_FILENO));
		CHECK (close (pipefd[0]));
		CHECK (close (pipefd[1]));
		execv (path, cmd);
		fprintf(stderr, "execv error: failed command is:\n");
		while ( *cmd ) 
			{ fprintf (stderr, "%s ", *cmd++); }
		interupt (1, "\nexecv error: path is: \n\"%s\"", path);
		break;

	default :
		CHECK (wait (&err_reason));
		CHECK (close (pipefd[1]));
		CHECKN (cmd_output = fdopen (pipefd[0], "r"));
		*exit_code = WEXITSTATUS (err_reason);
	
		while ((nbytes = fread(buf, 1, sizeof(buf), cmd_output)) == BUFSIZ) {
			for (size_t i = 0; i < BUFSIZ; i++)
        		cmd_output_str.push_back(buf[i]);
		}
		
		for (size_t i = 0; i < nbytes; i++)
     		cmd_output_str.push_back(buf[i]);
	}

	if (fclose(cmd_output) == EOF)
		interupt (1, "fclose() failed.");

	if (cmd_output_str.empty())
		return "";

	return cmd_output_str;
}




string execute (int & exit_code, const char * path, vector<char*> cmd) {

	cmd.push_back(NULL);

  	char **cmd_ptr = cmd.data();

	size_t len;

	string output = __execute__ (&exit_code, &len, path, cmd_ptr);

	output [len - 1] = '\0';

	return output;
}



string s_execute (int & exit_code, const char * path, const char * s) {
	
	vector<char*> cmd;

	cmd.push_back (const_cast<char*>(s));

	cmd.push_back(NULL);

  	char **cmd_ptr = cmd.data();

	size_t len;

	string output = __execute__ (&exit_code, &len, path, cmd_ptr);

	output [len - 1] = '\0';

	return output;
}




void reverse_str (string & str) { 
    int n = str.length(); 
  
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]); 
} 



string parse_extension (string path, string & extension) {
	size_t path_len = path.length();
	string path_extension; 
	int break_point = 0;
	
	for (int i = path_len - 1; i >= 0; i--) {
		if (path[i] == '.') {
			break_point = i;
			break;
		}

		path_extension.push_back(path[i]);
	}

	reverse_str (path_extension);

	extension = path_extension;

	return path.substr(0, path_len - break_point - 1);
}



string cut_file (string path) {
	bool to_exit = true;
	stringstream ss(path);
	string token;

    while ( getline(ss, token, '/') ) {
		if ( token == "." || token == ".." )
			continue;
        else if ( has_dot (token) ) {
			to_exit = false;
			break;
		}
	}

	if (to_exit)
		return path;

	int exit_code;
	vector<char*> cmd;

	LOAD_CMD ("dirname");
	LOAD_CMD (path.c_str());

	string out = execute(exit_code, DIRNAME_PATH, cmd);
	CHECK_CODE (exit_code);

	out.erase(remove(out.begin(), out.end(), '\n'), out.end());

	return out;
}