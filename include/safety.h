#ifndef SAFETY
#define SAFETY

#include <string>
 
/**
 * @brief : Checks if the extension given by the user can be
 * recognized by codegen; this is specialy used to check if the
 * extension given under codegen_config.txt and the file added
 * by the user have the same extension. If not, a warning is 
 * thrown to the user.
 * 
 * @param path: path of the file that needs to be created by
 * codegen. Only the extension of the file is analyzed.
 * 
 * @param extension: the extension given under condegen_config.txt
 *
 */
void extension_safety (std::string path, std::string extension );

#endif
