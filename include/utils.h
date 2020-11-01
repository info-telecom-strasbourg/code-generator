#ifndef UTILS
#define UTILS

/**
 * Macros used to check the returning values of primitive system, 
 * memory allocation and process exit values.
 *
 */
#define CHECK(op) do { if ((op) == -1) interupt (1, #op) ; } while (0)
#define CHECKN(op) do { if ((op) == NULL) interupt (1, #op) ; } while (0)
#define CHECK_CODE(op) do { if((op) == 1) exit (1); } while (0)


/**
 * the name "cmd" is always used as a vector<char*> and is used with
 * the function execute (defined after this), which launches a bash 
 * command and captures the stdout while such command is launched.
 * 
 * This macro is used to push back a string (a char* here) inside 
 * cmd in a more stylistic way
 *
 */
#define LOAD_CMD(op) do {cmd.push_back (const_cast<char*>(op));} while (0)


/**
 * @brief : Interupts the program and prints errno
 *
 */
void interupt (int syserr, const char * msg, ...);


/**
 * @brief : Simply tests if a file exists 
 * 
 * @param name: The path of the file
 *
 */
bool file_exists (const char * name);




/**
 * @brief : Checks if a string contains the character '.'
 * 
 * @param token: Here the string is a file or directory name.
 * Because the file or the folder does not exist yet, we test
 * if it's a file or not by checking for an extension.
 * 
 * @return true if the string has a dot
 */

bool has_dot (std::string token);




/**
 * @brief : Executes the commands under the vector cmd with 
 * the path used with execv. Returns stdout after execv printed
 * in it. The length of the string containing stdout and the exit
 * code of execv can also be captured with a pointer to adress 
 * for the paramater len.
 * 
 * @param exit_val: value returned by the process created with the
 * shell command under the vector cmd
 * 
 * @param len: length of the string outputed by the command.
 * 
 * @param path: path used for the function execv
 * 
 * @param cmd: vector containing the commands that shall be executed
 * by execv.
 *
 */
std::string __execute__ (int * exit_code, size_t * len, const char * path, 
	char * const cmd []);


/**
 * @brief : This simplifies the interaction with __execute__ by allowing
 * the cmd to be stocked in a C++ vector. To use execute, you juste have to 
 * declare cmd (vector<char*> cmd;) and exit_code (int exit_code) and then
 * use the macro LOAD_CMD defined above to load the vector with the list
 * of shell commands you want executed.
 * 
 * This is all you have to do. After that, execute adds a NULL value to the 
 * end of the vector and converts the C++ vector into a C vector internaly. 
 * It also make sure the string of stdout is correctly terminated.
 *
 */
std::string execute (int & exit_code, const char * path, 
	std::vector<char*> cmd);


/**
 * @brief : Same function as execute but does not demand a vector<char*> but
 * only a char*.
 * This should be used for very simple commands that do not demand multiple
 * shell commands to work.
 *
 */
std::string s_execute (int & exit_code, const char * path, const char * s);


/**
 * @brief : Reverts a C++ string
 * 
 * @param str: The adress of the string; meaning the modification is made
 * directly into the string that is passed in the function.
 *
 */
void reverse_str (std::string & str);


/**
 * @brief : Takes a path and modifies the paramater extension so it
 * contains the extension of the file under the given path.
 * 
 * @param path: explained above
 * 
 * @param extension: explained above
 * 
 * @return: returns the path WITHOUT the file name (with the extension)
 * This is useful because codegen needs the directory containing either
 * the source file or the include file given by the user. This is the 
 * directory given to the Makefile.
 *
 */
std::string parse_extension (std::string path, std::string & extension);



/**
 * @brief : Used to transform a file path into the path where such file
 * is found (This is exactly the bash command dirname)
 * 
 * @param path: explained above
 *
 * @return: returns the path without the file extension in case there was
 * one. Exemple:
 * 	cut_file (./src/test.c) = ./src/
 * 	cut_file (./src) = ./src
 */
string cut_file (string path);

#endif
