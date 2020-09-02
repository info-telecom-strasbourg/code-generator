/**
 * Unit tests on codeWrite
 */

#include <iostream>
#include "unit_test.hpp"
#include "codeWrite.hpp"

/**
 * Test the generation of flux
 */
void test_flux(void)
{
    codeWrite cw("files/files_code_write/testFile.cpp");
    cw._include("<iostream>");
    cw._function_free("int", "test");
    cw._start();
    cw._end();
    cw._function_prot("int", "main", "void");
    cw._function("int", "main", "void");
        cw._code("int nb, qty;");
        cw._cout("\"Hello world\"");
        cw._cerr("\"Hello world\"");
        cw._cin("nb","qty");
        cw._flux_in("flux_in", "nb","qty");
        cw._flux_out("flux_out", "\"Hello world\"");
        cw._try();
        cw._end();
        cw._catch("Exception e");
        cw._end();
        cw._return(0);
    cw._end();
    cw.flush();
    assert_file("files/files_code_write/testFile.cpp", "files/files_code_write/flux.txt");
    remove("files/files_code_write/testFile.cpp");
}

/**
 * Test the generation of preprocessor directives
 */
void test_preproc(void)
{
    codeWrite cw("files/files_code_write/testFile.cpp");
    cw._ifndef("TEST_H");
    cw._define("TEST_H");
    cw._linebreak();
    cw._endif();
    cw.flush();
    assert_file("files/files_code_write/testFile.cpp", "files/files_code_write/preproc.txt");
    remove("files/files_code_write/testFile.cpp");
}

/**
 * Test the generation of objects
 */
void test_objects(void)
{
    codeWrite cw("files/files_code_write/testFile.cpp");
    cw._struct_typedef("Coord");
        cw._code("int x"); cw._semicolon();
        cw._code("int y"); cw._semicolon();
    cw._end_object();

    cw._linebreak();

    cw._class("Coord");
    cw._private();
    cw._protected();
    cw._public();
    cw._end_object();
    cw.flush();
    assert_file("files/files_code_write/testFile.cpp", "files/files_code_write/objects.txt");
    remove("files/files_code_write/testFile.cpp");
}

/**
 * Test the generation of instructions
 */
void test_instructions(void)
{
    codeWrite cw("files/files_code_write/testFile.cpp");
    cw._for("int i = 0; i < 2; i ++");
        cw._while("true");
            cw._switch("i");
                cw._case("0");
                    cw._if("i%2==0");
                        cw._break();
                    cw._end();
                    cw._else();
                        cw._break();
                    cw._end();
                cw._default();
                    cw._exit("EXIT_FAILURE");
            cw._end();
        cw._end();
    cw._end();
    cw._do();
       cw._break();
    cw.do_while("true");
    cw.flush();
    assert_file("files/files_code_write/testFile.cpp", "files/files_code_write/instructions.txt");
    remove("files/files_code_write/testFile.cpp");
}

/**
 * Test the generation of comments
 */
void test_comments(void)
{
    codeWrite cw("files/files_code_write/testFile.cpp");
    cw._comment("This program shows how to declare a variable.");
    cw._comment_line("Declaration of the variable");
    cw._linebreak();
    cw._code("int nb = 2;");
    cw._comment_line("the variable nb is equal to 2");
    cw.flush();
    assert_file("files/files_code_write/testFile.cpp", "files/files_code_write/comments.txt");
    remove("files/files_code_write/testFile.cpp");
}

int main(void)
{
    std::cout << "----- Launch tests for the library codeWrite -----" << std::endl << std::endl;
    TEST(test_flux);
    TEST(test_preproc);
    TEST(test_objects);
    TEST(test_instructions);
    TEST(test_comments);

    return 0;
}
