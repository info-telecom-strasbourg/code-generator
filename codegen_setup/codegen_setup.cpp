#include <iostream>
#include <string>
#include <vector>
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

#include "../include/path.h"
#include "../include/config_getter.h"

using namespace std;

#define SETUP_SCRIPT 0
#define DIR_PARSER_SCRIPT 1

#define CODEGEN_CONFIG_TXT "codegen_config.txt"
#define CODEGEN_CONFIG_BIN ".codegen_config_bin"
#define BASH "bash"

#define CHECK(op) do { if ((op) == -1) interupt (1, #op) ; } while (0)
#define CHECKN(op) do { if ((op) == NULL) interupt (1, #op) ; } while (0)




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




inline bool file_exists (const char * name) {
    return ( access( name, F_OK ) != -1 );
}




void read_config_bin () {
	GET_CONFIG (

	puts("");
	printf("Successfully created/updated codegen_config.txt !\n");
	printf("Be aware that this is can be a guess on what the current");
	printf( "directory structure is.\n");

	puts(" ");
	printf("\
			Source = %s\n \
			Include = %s\n \
			Source extensions = %s\n \
			Include extensions = %s\n \
			Object = %s\n \
			Bin = %s\n \
			Name = %s\n", 
			ds->source, ds->include, ds->c_extension, ds->h_extension,
			ds->object, ds->bin, ds->name);
	puts(" ");

	)
}




void execute_script (bool to_print, int script_id) {
	int err_reason = 0;
	
	switch (fork ()) {
	case -1 :
		interupt (1, "error: fork failed in script process attempt.");
		break;
	
	case 0 :
		if (script_id == SETUP_SCRIPT) {
			execl (BASH_PATH, BASH, CODEGEN_SETUP_SCRIPT_PATH, 
				CODEGEN_CONFIG_TXT, CODEGEN_PATH, NULL);
		}
		if (script_id == DIR_PARSER_SCRIPT) {
			execl (BASH_PATH, BASH, CODEGEN_DIR_PARSING_SCRIPT_PATH,
				NULL);
		}
		interupt (1, "error: execl failed in script process");
		break;

	default :
		CHECK (wait (&err_reason));
		if (WEXITSTATUS (err_reason))
			exit (EXIT_FAILURE);
		if (to_print)
			read_config_bin ();
	}
}



void update_bin (bool to_print) {
	const char * txt = CODEGEN_CONFIG_TXT;
	const char * bin = CODEGEN_CONFIG_BIN;
	size_t mod_time_txt, mod_time_bin;

	struct stat result;
	
	if (stat(txt, &result) == 0) 
    	mod_time_txt = result.st_mtime;

	if (stat(bin, &result) == 0)
		mod_time_bin = result.st_mtime;

	if (mod_time_txt > mod_time_bin) {
		if (to_print) {
			cout << "Detected changes in the configuration file:"; 
			cout << " updating the binary...\n";
		}
		
		execute_script (to_print, SETUP_SCRIPT);
	}
}	




int main() {
	bool txt = file_exists (CODEGEN_CONFIG_TXT);
	bool bin = file_exists (CODEGEN_CONFIG_BIN);

	if ( (!txt && !bin) || (!txt && bin) ) {
		execute_script (false, DIR_PARSER_SCRIPT);
		execute_script (true, SETUP_SCRIPT);
	}

	if ( txt && !bin )
		execute_script (true, SETUP_SCRIPT);

	if ( txt && bin )
		update_bin (true);
	
	return 0;
}
