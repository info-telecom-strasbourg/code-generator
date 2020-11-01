#ifndef OTHER_FLAGS
#define OTHER_FLAGS

#define IS_SOURCE 0
#define IS_INCLUDE 1


/**
 * @brief : Used to call the script load_template.sh
 * 
 * @param optarg_: the path of the template the user 
 * wants to be copied in his current directory
 *
 */
void flag_t (char * optarg_);


/**
 * @brief : Created a new standard file; either source or
 * include
 * 
 * @param name: the name (not a path) of the new file that
 * needs to be created
 * 
 * @param ext: the extension of the new file
 * 
 * @param dir: the dir where the new file will be located.
 * In summary: the new file has the following path:
 * 		dir/name.ext
 * 
 * @param type: used to inform the function if the file
 * is a source or include file. This is useful because the 
 * standard files are diferent if it's a source or include
 * file 
 * (check out /user/standard_files to see what the standard
 * files look like).
 */
void create_file (string name, string ext, string dir, int type);


/**
 * @brief : Used to add a couple of source/include files.
 * 
 * @param optarg_: the name of the couple the user wants to 
 * add (for exemple, otparg_ = test will add the files test.c
 * and test.h if the extensions are defined as c/h.
 *
 */
void flag_a (char * optarg_);


void flag_c ();


void flag_d ();

#endif
