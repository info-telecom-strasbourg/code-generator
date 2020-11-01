#ifndef FLAG_M
#define FLAG_M

#define IS_SOURCE 0
#define IS_INCLUDE 1
#define IS_OTHER 2

#include <string>




/**
 * @brief : Calls the script cpy_files.sh in order to copy a standard
 * file under /user/standard_files inside the current directory of
 * the user
 * 
 * @param path: This is the path of the new file that should
 * contain the data that the standard file has.
 * 
 * @param extension: This is the extension of the file: this is usefull
 * because the standard files are not the same if the program is in C or C++
 * 
 */
void create_standard_main_file (std::string path, std::string extension);


/**
 * @brief : Calls the script add_header.sh in order to copy a standard
 * file under /user/standard_files inside the current directory of
 * the user. This file contains inclusion guards by default.
 * 
 * @param file_name: This is the name of the new file that should
 * contain the data that the standard file has (ie. the inclusion guards). 
 * 
 * @param include_path: This is the path where the new standard file will
 * be added.
 * 
 */
void create_standard_include (string file_name, string include_path);


/**
 * @brief : Creates a directory if it does not exist already. In
 * either cases, prints out a message to the user to inform him of
 * the attemps or the new directories that were added.
 * 
 * @param path: the path of the directory to create
 * 
 */
void create_dir (std::string path);


/**
 * @brief : codegen allow for the path of source and include, to be
 * a path to a file (and not a folder). This function calls the functions
 * defined above to create the directories and the file in case the
 * user specified a file. 
 * 
 * @param path: the path that is going to be added if it doesn't
 * exist already
 * 
 * @param extension: extension is usefull for the function
 * create_standard_main_file (see the comments above this function)
 * 
 * @param type: type can either be IS_SOURCE, IS_INCLUDE or IS_OTHER.
 * If it is IS_SOURCE; if there would have been a file in the path, such
 * file would be treated as a source file.
 * If it is IS_INCLUDE; the same thing happens execept for an inclusion file.
 * If it is IS_OTHER; the program will only create new directories and
 * raise an error if the user tried to pass a file under the definitions
 * of Object, Bin or Name (Of course Name is always a file, but it has no extension
 * - because it is a binary - so there is no risk of false error raising.)
 * 
 */
std::string parse_path (const char * path, const char * extension, int type);


/**
 * @brief : This is the function that creates the Makefile using
 * the script build_makefile.sh. It gives the script 8 values that
 * correspond to parameters of the Makefile (check out the script for
 * the description of what those parameters are)
 * 
 * In addition it gives the script, as its last parameter, the path of
 * the makefile template under codegen/user/. This is because we have
 * centralized every path under path.h so it is easy for the user to change
 * the root path of codegen (because only path.h needs to me modified, which
 *  is easyly done with a script.) 
 *
 */
void flag_m ();

#endif
