#ifndef CONFIG_GETTER
#define CONFIG_GETTER

#define MAX_SIZE 128    

#define CODEGEN_CONFIG_BIN ".codegen_config_bin"


/*
* This is the main structure of this program. It will be written into
* the binary file as explained in the begining.
* (Same as the one in config_parser.y)
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


/**
* This Macro is used to access the values contained by the
* binary file .codegen_config_bin. This is an exemple on how
* to use it:
* 
* GET_CONFIF (                  
*                               <       
*	printf("%s", ds->source);   <    Value of 'JOB'
*                               <
* )
*
* this means that inside the brackets of GET_CONFIG, you have access 
* to the structure "ds" containing all the information in the binary.
* You can do whatever you want with it execept free(ds). After your 
* instruction; the macro just uses the function free() to free the
* memory used by the struture.
*
* This macro also checks for empty defintions so the user can have
* detail on why his config file is not valid.
*/
#define GET_CONFIG(JOB) \
do {\
	FILE * bin_config = fopen (CODEGEN_CONFIG_BIN, "r");\
\
	if (bin_config == NULL) {\
		fprintf(stderr, "error: could not open the file\n");\
		exit (EXIT_FAILURE);\
	}\
\
	struct dir_struct *ds = (struct dir_struct *)\
		malloc(sizeof(struct dir_struct));\
	\
	fread (&ds->source,      sizeof(ds->source),      1, bin_config);\
	fread (&ds->include,     sizeof(ds->include),     1, bin_config);\
	fread (&ds->object,      sizeof(ds->object),      1, bin_config);\
	fread (&ds->bin,         sizeof(ds->bin),         1, bin_config);\
	fread (&ds->name,        sizeof(ds->name)       , 1, bin_config);\
	fread (&ds->c_extension, sizeof(ds->c_extension), 1, bin_config);\
	fread (&ds->h_extension, sizeof(ds->h_extension), 1, bin_config);\
	\
	if (strcmp(ds->source, "$void") == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty source path.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	if (strcmp(ds->include, "$void") == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty include path.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	if (strcmp(ds->object, "$void") == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty object path.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	if (strcmp(ds->bin, "$void") == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty bin path.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	if (strcmp(ds->name, "$void") == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty target name.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	if (strcmp(ds->c_extension, "$void") == 0 || strlen(ds->c_extension) == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty source extension value.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	if (strcmp(ds->h_extension, "$void") == 0 || strlen(ds->h_extension) == 0) {\
		fprintf(stderr, "\n\033[1;31merror\033[0m: Empty include extension value.\n");\
		exit (EXIT_FAILURE);\
	}\
\
	JOB\
\
	free(ds);\
} while (0);

#endif
