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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <getopt.h>
#include <ctype.h>

/** You can add a new flag here **/

/* flag --makefile (-m) : create a makefile */
/* flag --indent (-i) : set indent configs */

enum flags_t { FLAG_M, FLAG_I };

/**                             **/


/** You can decide what options are to be parsed with a given flag **/

struct flags_args_type {
	char ** args_type;

	char ** flags_args;

	unsigned int * flags_start_idxes;
	
	unsigned int * flags_end_idxes;
};

/**                                                                **/

struct args_t {
	enum flags_t flags;

	struct flags_args_type * fat;
};

/* ---------------------------------------------------------------- */

/**
 * @file : args_parser.cpp
 * 
 * @brief : This function is used to test if the string s1 is
 * a subset string s2
 * 
 * @return : boolean value
 */
int find (const char * s1, const char * s2) {
	unsigned int i1 = 0;
	unsigned int i2 = 0;
	unsigned int matching_cnt = 0;

	size_t s1_size =  strlen(s1);

	while (s2 [i2]) {

		if (s2 [i2] == s1 [i1]) {
			matching_cnt++;
			i1++;

			if (matching_cnt == s1_size)
				return i2 + 2;
		}
		else {
			matching_cnt = 0;
			i1 = 0;
		}

		i2++;
	}

	return -1;
}




struct args_t * init_args_t (struct args_t * a, const char ** args_type,
	const unsigned int nb_of_types, const unsigned int *flags_start_idxes,
	const unsigned int * flags_end_idxes) {
	
	size_t type_size;

	a = calloc (1, sizeof(struct args_t));

	a->fat = calloc (1, sizeof(struct flags_args_type));

	a->fat->args_type = calloc (nb_of_types, sizeof(char*));

	for (size_t i = 0; i < nb_of_types; i++) {
		if (!args_type[i]) {
			fprintf(stderr, "error: nb_of_types does not match args_type.\n");
			exit (EXIT_FAILURE);
		}

		type_size = strlen(args_type[i]) + 1;

		a->fat->args_type[i] = calloc (type_size, sizeof(char));

		snprintf(a->fat->args_type[i], type_size, "%s", args_type[i]);
	}

	size_t start_size = flags_start_idxes[0] + 1;
	size_t end_size = flags_end_idxes[0] + 1;

	a->fat->flags_start_idxes = calloc (start_size, sizeof(int));
	a->fat->flags_end_idxes = calloc (end_size, sizeof(int));

	for (size_t i = 1; i < start_size; i++)
		a->fat->flags_start_idxes[i] = flags_start_idxes[i];

	for (size_t i = 1; i < end_size; i++)
		a->fat->flags_end_idxes[i] = flags_end_idxes[i];

	a->fat->flags_args = calloc(nb_of_types, sizeof(char*));

	for (size_t i = 0; i < nb_of_types; i++)
		a->fat->flags_args[i] = NULL;

	return a;
}




char * get_flag_arg(struct args_t * a, enum flags_t f,
	unsigned int arg_type_idx) {

	unsigned int flag_start_idx = a->fat->flags_start_idxes[f+1];

	if (a->fat->flags_args[flag_start_idx + arg_type_idx] == NULL)
		return "noarg";

	return a->fat->flags_args[flag_start_idx + arg_type_idx];
}




struct args_t * add_args (enum flags_t f, struct args_t * a, const char * s) {

	int flag_start_idx = a->fat->flags_start_idxes[f+1];
	int flag_end_idx = a->fat->flags_end_idxes[f+1];
	unsigned int new_arg_idx, flag_args_idx;
	int offset;

	size_t s_size = strlen(s);
	
	for (int i = flag_start_idx; i <= flag_end_idx; i++) {

		if ((offset = find (a->fat->args_type[i], s)) != -1) {
			flag_args_idx = 0;

			new_arg_idx = i;

			a->fat->flags_args[new_arg_idx] =
				calloc(s_size - offset + 1, sizeof(char));


			while ( s[offset] && s[offset] != ' ') {
				a->fat->flags_args[new_arg_idx][flag_args_idx] = s[offset];
				offset++;
				flag_args_idx++;
			}
		}
	}

	return a;
}




void print_usage () {
	puts("usage");
}




struct args_t * args_parser (int argc, char** argv, struct args_t * a,
	const char * short_opt) {

	int c = 0;
 	opterr = 0;

	struct option long_opt[] = {

		{"makefile", required_argument, NULL, 'm'},
		{"indent", required_argument, NULL, 'i'},
		{0, 0, 0, 0},

	};

	while ((c = getopt_long (argc, argv, short_opt, long_opt, NULL)) != -1) {
		switch (c) {
		case -1:
		case 0:
			break;

		case 'h':
			print_usage ();
			exit (0);
			break;

		case 'm':
			a->flags |= FLAG_M;

			a = add_args (FLAG_M, a, optarg);

			break;

		case 'i':
			a->flags |= FLAG_I;
			
			a = add_args (FLAG_I, a, optarg);
			
			break;

		case '?':
			fprintf(stderr, "Missing arguments\n");

			exit (EXIT_FAILURE);
		
		default:
			fprintf (stderr, "Unknown option character `%c'.\n", c);
			
			print_usage ();
			
			exit (EXIT_FAILURE);
		}
	}

	return a;
}




int main (int argc, char** argv) {

	struct args_t * a = NULL;
	
	const char * args_type [] = {
		"source",
		"include",
		"obj",
		"bin",
		"indent_size",
		"if_option",
		"julien"
	};

	const unsigned int nb_of_types = 7;

	const unsigned int flags_start_idxes[3] = {2,0,4};

	const unsigned int flags_end_idxes[3] = {2,3,6};

	a = init_args_t (a, args_type, nb_of_types, flags_start_idxes,
		flags_end_idxes);

	a = args_parser (argc, argv, a, "m:i:");

	printf("[%s]\n", get_flag_arg(a, FLAG_M, 0));
	
	printf("[%s]\n", get_flag_arg(a, FLAG_M, 1));

	printf("[%s]\n", get_flag_arg(a, FLAG_I, 2));

	return 0;
}
