using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#include "parse_args.h"
#include "flag_m.h"
#include "other_flags.h"
#include "path.h"
#include "utils.h"




void case_h (int exit_val) {
	puts ("\nusage: \n"
		"-m\t Generates a makefile given the folder configuration.\n"
		"\n"
		"-t\t [TEMPLATE NAME] Loads a template in the current directory.\n"
		"\n"
		"-a\t [FILE NAME] Adds a new couple of source/header files\n"
		// "\n"
		// "-u\t [FUNCTION NAME] Adds the header of the function to the right include file\n"
		"\n"
		"-c\t Generates a blank configuration file."
		"\n"
		"-d\t Deletes codegen_config.txt and its binary.");
	
	exit (exit_val);
}




void parse_args (int argc, char ** argv) {
	int c = 0;
	int exit_code;

	if (argc == 1) {
		fprintf(stderr,"\033[1;31merror\033[0m: Missing arguments.\n");
		case_h (EXIT_FAILURE);
	}

 	while ((c = getopt (argc, argv, "hcdmt:a:")) != -1) {

		switch (c) {
		case -1:
		case 0:
	  		break;

		case 'h':
	  		case_h (EXIT_SUCCESS);
			break;

		case 'a':
			cout << s_execute (exit_code, CODEGEN_DIR_PARSING_BIN_PATH,
				"codegen_setup");	
			CHECK_CODE (exit_code);
			flag_a (optarg);
			break;

		case 'm':
			cout << s_execute (exit_code, CODEGEN_DIR_PARSING_BIN_PATH,
				"codegen_setup");	
			CHECK_CODE (exit_code);
			flag_m ();
			break;

		case 't':
			flag_t (optarg);
			break;

		case 'c':
			flag_c ();
			break;

		case 'd':
			flag_d ();
			break;

		default:
	  		fprintf (stderr, "Unknown option character `%c'.\n", c);
	  		case_h (EXIT_FAILURE);
		}
    }
}
