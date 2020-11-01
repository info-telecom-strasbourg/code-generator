#ifndef PARSE_ARGS
#define PARSE_ARGS

/**
 * @brief : Prints the usage of codegen
 * 
 * @param exit_val: used to decide if the
 * exit is with either EXIT_SUCCESS or EXIT_FAILURE
 *
 */
void case_h (int exit_val);


/**
 * @brief : Parses the arguments given by the user.
 * Checkout codegen --help to see the possible arguments
 * you can input into codegen
 *
 */
void parse_args (int argc, char ** argv);

#endif