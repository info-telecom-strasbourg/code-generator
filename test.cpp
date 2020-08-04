#include <iostream>
#include "unit_test.hpp"
#include "codeComprehension.h"


void test_fileInVector(void)
{
    std::string stringToExtract(codeComprehension::fileInVector("fileInVector.txt"));
    assert(stringToExtract == "This\nis\na\ntest\nfile"); 
}

void test_getNextString(void)
{
    std::string stringToExtract("");
    assert(codeComprehension::getNextString(stringToExtract) == ""); 

    stringToExtract = "Nothing to get";
    assert(codeComprehension::getNextString(stringToExtract) == ""); 

    stringToExtract = " \"Prank\"";
    assert(codeComprehension::getNextString(stringToExtract) == ""); 

    stringToExtract = "\"Keep this string\"";
    assert(codeComprehension::getNextString(stringToExtract) == "\"Keep this string\""); 

    stringToExtract = "\"Keep this string\" but not this one";
    assert(codeComprehension::getNextString(stringToExtract) == "\"Keep this string\""); 

    stringToExtract = "\"Are u \\\"kidding\\\" me\"";
    assert(codeComprehension::getNextString(stringToExtract) == "\"Are u \\\"kidding\\\" me\""); 

    stringToExtract = "\"Line\\ \n break\"";
    assert(codeComprehension::getNextString(stringToExtract) == "\"Line\\ \n break\""); 
}

void test_getNextComment(void)
{
    std::string stringToExtract("");
    assert(codeComprehension::getNextComment(stringToExtract) == ""); 

    stringToExtract = "No comment";
    assert(codeComprehension::getNextComment(stringToExtract) == ""); 

    stringToExtract = " //Prank";
    assert(codeComprehension::getNextComment(stringToExtract) == ""); 

    stringToExtract = " /*Prank*/";
    assert(codeComprehension::getNextComment(stringToExtract) == ""); 

    stringToExtract = "//Comment";
    assert(codeComprehension::getNextComment(stringToExtract) == "//Comment"); 

    stringToExtract = "/*Comment*/";
    assert(codeComprehension::getNextComment(stringToExtract) == "/*Comment*/"); 

    stringToExtract = "/*Comment*/ but not here";
    assert(codeComprehension::getNextComment(stringToExtract) == "/*Comment*/"); 

    stringToExtract = "/*Comment";
    assert(codeComprehension::getNextComment(stringToExtract) == "/*Comment"); 

    stringToExtract = "/*//Tricky comment*/";
    assert(codeComprehension::getNextComment(stringToExtract) == "/*//Tricky comment*/"); 

    stringToExtract = "///*Comment";
    assert(codeComprehension::getNextComment(stringToExtract) == "///*Comment"); 

    stringToExtract = "/*Comment\nwith a line break*/";
    assert(codeComprehension::getNextComment(stringToExtract) == "/*Comment\nwith a line break*/"); 
}

void test_getNextIf(void)
{
    std::string stringToExtract("");
    assert(codeComprehension::getNextIf(stringToExtract) == ""); 
}


int main(void)
{
    TEST(test_fileInVector);
    TEST(test_getNextString);
    TEST(test_getNextComment);
    TEST(test_getNextIf);
    
    

    return 0;
}