/**
* Yacc grammar used to parse the configuration file that is read
* by codegen.  
* 
* Codegen uses to main files to map a directory:
* -> a file called codegen_config.txt where the user can define the
* following informations about the directory:
* source = 
* include = 
* extensions =
* object =
* bin = 
* name =
*
* -> a binary file containing the information in the codegen_config.txt file.
* We use a binary to simplify the communication between codegen and the 
* user's demands: it is easier to read a binary file in c/c++ then parsing 
* a .txt. The structure we write in the binary is "struct dir_struct" (defined
* after this)
*
*
* The purpose of this yacc file is to parse the .txt file and write the parsed
* information into a binary file (.codegen_config_bin)
*/

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Necessary headers to avoid yacc warnings: */
void yyerror (const char *);

int yylex_destroy ();

extern int yylex ();
/* ------------------------------------------- */


/* Identifiers (ie. the options given by the user) are limited to 128 
characters. 
*/
#define MAX_SIZE 128


/* The binary file this program is about to build is called
* .codegen_config_bin
*/
#define CONFIG_PATH "./.codegen_config_bin"


/* Enumeration of the possible definitions in the config file.
* This serves as a numeric identifier for the definition. 
* 
*/
enum defs { SOURCE_, INCLUDE_, EXTENSIONS_, OBJECT_, BIN_, NAME_ };


/* Links the enum identifier to the name of the definition:
	defs_names[SOURCE_] = "source";
	defs_names[INCLUDE_] = "include";
	ect...
*/
const char * defs_names [6] = { "source", "include", "extensions", "object",
	"bin", "name" };


/*
* This is the main structure of this program. It will be written into
* the binary file as explained in the begining.
*/
struct dir_struct {
	char source  [MAX_SIZE];
	char include [MAX_SIZE];
	char object  [MAX_SIZE];
	char bin     [MAX_SIZE];
	char name    [MAX_SIZE];

	char c_extension [MAX_SIZE];
	char h_extension [MAX_SIZE];
};

struct dir_struct codegen_config;


/*
* This array of integers will count how many times each 
* definition appears in the config file (used to avoid
* poorly built configuration files.)
*/
int nb_of_definitions [6] = {0};




/* Used to remove all new lines from a string */
void no_new_lines(char* s) {
    const char* d = s;
    do {
        while (*d == '\n') {
            ++d;
        }
    } while (*s++ = *d++);
}




/*
* Tests if there were no redefinitions (using the array 
* nb_of_definitions) and if the identifier the user gave
* is not too large.
*/
void test_if_valid (enum defs d, const char * id) {

	if (nb_of_definitions [d] != 0) {
		fprintf (stderr, "\033[1;31merror\033[0m: Redefinition of %s\n",
			defs_names [d]);
		exit (EXIT_FAILURE);
	}

	if (strlen(id) > MAX_SIZE) {
		fprintf (stderr, "\033[1;31merror\033[0m: Identifier too large:\n %s\n"
			,id);
		exit (EXIT_FAILURE);
	}

}



/* 
* Used to parse the output of the user for the definition of
* the extensions. For exemple:
*
* c/h -> codegen_config.c_extension is loaded with c
		 and codegen_config.h_extension is loaded with h
*/
void load_extensions (const char * id) {
	int k = 0;

	while ( id[k] && id[k++] != '/' );

	snprintf (codegen_config.c_extension, k, "%s", id);
	snprintf (codegen_config.h_extension, MAX_SIZE, "%s", id + k);
}



/* 
* Adds the content of the identifier parsed by yacc and flex into
* the structure dir_struct so that we can write the structure in
* the binary file.
*
* Every time we add a new identifier, we make sure it was not already
* added by calling the function test_if_valid.
*/
void add (enum defs d, const char * id) {

	test_if_valid (d, id);
	
	switch (d) {
	case SOURCE_:
		snprintf (codegen_config.source, MAX_SIZE, "%s", id);
		nb_of_definitions[SOURCE_]++;
		break;

	case INCLUDE_:
		snprintf (codegen_config.include, MAX_SIZE, "%s", id);
		nb_of_definitions[INCLUDE_]++;
		break;

	case EXTENSIONS_:
		load_extensions (id);
		nb_of_definitions[EXTENSIONS_]++;
		break;

	case OBJECT_:
		snprintf (codegen_config.object, MAX_SIZE, "%s", id);
		nb_of_definitions[OBJECT_]++;
		break;

	case BIN_:
		snprintf (codegen_config.bin, MAX_SIZE, "%s", id);
		nb_of_definitions[BIN_]++;
		break;

	case NAME_:
		snprintf (codegen_config.name, MAX_SIZE, "%s", id);
		nb_of_definitions[NAME_]++;
		break;
	}
}



/* 
* Adds the output of the identifier command to the structure dir_struct
* so that we can write the structure in the binary file.
*
*/
void add_cmd (enum defs d, const char * id) {
	FILE *fp;
	char buf [MAX_SIZE];

	size_t id_size = strlen(id);
	
	char * cmd = calloc(id_size, sizeof(char));

	snprintf(cmd, id_size - 2, "%s", id + 2);

	puts("");
	fp = popen(cmd, "r");
	if (fp == NULL) {
		fprintf(stderr,"\n\033[1;31merror\033[0m: popen failed");
		fprintf(stderr," with command: %s\n", cmd);
		exit (EXIT_FAILURE);
	}

	if ( fgets(buf, MAX_SIZE, fp) != NULL ) {
		no_new_lines (buf);
		add (d, buf);
	}
	else {
		fprintf(stderr,"\n\033[1;31merror\033[0m: bash failed with");
		fprintf(stderr," command:\n %s\n", cmd);
		exit (EXIT_FAILURE);
	}

	fclose (fp);
	free(cmd);
}


%}

%union {
	char str [128];
}

%token <str> ID
%token <str> CMD
%token <str> SOURCE
%token <str> INCLUDE
%token <str> EXTENSIONS
%token <str> OBJECT
%token <str> BIN
%token <str> NAME

%start definitions

%%

definitions : | definitions definition

definition : SOURCE ID { add (SOURCE_,     $2); }
	| INCLUDE ID       { add (INCLUDE_,    $2); }
	| OBJECT ID        { add (OBJECT_,     $2); }
	| EXTENSIONS ID    { add (EXTENSIONS_, $2); }
	| BIN ID           { add (BIN_,        $2); }
	| NAME ID          { add (NAME_,       $2); }
	| SOURCE CMD       { add_cmd (SOURCE_,     $2); }
	| INCLUDE CMD      { add_cmd (INCLUDE_,    $2); }
	| OBJECT CMD       { add_cmd (OBJECT_,     $2); }
	| EXTENSIONS CMD   { add_cmd (EXTENSIONS_, $2); }
	| BIN CMD          { add_cmd (BIN_,        $2); }
	| NAME CMD         { add_cmd (NAME_,       $2);}
;

%%

/*
* Necessary function in order for yacc to work.
*/
void yyerror (const char * msg) {

	fprintf(stderr, "%s\n", msg);
	exit (EXIT_FAILURE);
}


/*
* Writes the content of the global variable codegen_config,
* who has been loaded witht the parsed identifiers, into the
* binary file.
*/
void add_to_bin () {
	FILE * config_bin = fopen(CONFIG_PATH, "w");

	if (config_bin == NULL) {
		fprintf(stderr, "\033[1;31merror\033[0m: could not open a file.\n");
		fprintf(stderr, "path was: %s\n", CONFIG_PATH);
		exit (EXIT_FAILURE);
	}

	if (fwrite(&codegen_config, sizeof(codegen_config), 1, config_bin) != 1) {
		fprintf(stderr, "\033[1;31merror\033[0m: could not write into %s.\n",
			CONFIG_PATH);
		exit (EXIT_FAILURE);
	}

	fclose (config_bin);
}


int main (void) {
	int y = yyparse();

	for (int i = 0; i < 6; i++) {
		if (nb_of_definitions[i] != 1) {
			fprintf(stderr, "\033[1;31merror\033[0m: %s was not defined.\n",
				defs_names[i]);
			exit (EXIT_FAILURE);
		}
	}

	add_to_bin ();

	yylex_destroy();

	return y;
}
