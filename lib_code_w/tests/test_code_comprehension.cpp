#include <iostream>
#include "unit_test.hpp"
#include "codeComprehension.hpp"


void test_stringExtracted(void)
{
    std::string stringExtracted(codeComprehension::fileInVector("filesCmp/stringToExtract.txt"));
    assert(stringExtracted == "This\nis\na\ntest\nfile");
}

void test_getNextString(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextString(stringExtracted) == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextString(stringExtracted) == "");

    stringExtracted = " \"Prank\"";
    assert(codeComprehension::getNextString(stringExtracted) == "");

    stringExtracted = "\"Keep this string\"";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Keep this string\"");

    stringExtracted = "\"Keep this string\" but not this one";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Keep this string\"");

    stringExtracted = "\"Are u \\\"kidding\\\" me\"";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Are u \\\"kidding\\\" me\"");

    stringExtracted = "\"Line\\ \n break\"";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Line\\ \n break\"");
}

void test_getNextComment(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextComment(stringExtracted) == "");

    stringExtracted = "No comment";
    assert(codeComprehension::getNextComment(stringExtracted) == "");

    stringExtracted = " //Prank";
    assert(codeComprehension::getNextComment(stringExtracted) == "");

    stringExtracted = " /*Prank*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "");

    stringExtracted = "//Comment";
    assert(codeComprehension::getNextComment(stringExtracted) == "//Comment");

    stringExtracted = "/*Comment*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment*/");

    stringExtracted = "/*Comment*/ but not here";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment*/");

    stringExtracted = "/*Comment";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment");

    stringExtracted = "/*//Tricky comment*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*//Tricky comment*/");

    stringExtracted = "///*Comment";
    assert(codeComprehension::getNextComment(stringExtracted) == "///*Comment");

    stringExtracted = "/*Comment\nwith a line break*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment\nwith a line break*/");
}

void test_getNextIf(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextIf(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextIf(stringExtracted) == "");

    stringExtracted = " if";
    assert(codeComprehension::getNextIf(stringExtracted) == "");

    stringExtracted = "if";
    assert(codeComprehension::getNextIf(stringExtracted) == "");

    stringExtracted = "ifouf";
    assert(codeComprehension::getNextIf(stringExtracted) == "");

    stringExtracted = "if ouf";
    assert(codeComprehension::getNextIf(stringExtracted) == "");

    stringExtracted = "if()";
    assert(codeComprehension::getNextIf(stringExtracted) == "if()");

    stringExtracted = "if(a&b)";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(a&b)");

    stringExtracted = "if(a&b) ";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(a&b)");

    stringExtracted = "if(test())";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(test())");

    stringExtracted = "if(char == ')')";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(char == ')')");

    stringExtracted = "if(str == \"prank)\")";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(str == \"prank)\")");

    stringExtracted = "if(test(\"prank)\",')'))";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(test(\"prank)\",')'))");
}

void test_getNextElse(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextElse(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextElse(stringExtracted) == "");

    stringExtracted = " else";
    assert(codeComprehension::getNextElse(stringExtracted) == "");

    stringExtracted = "else";
    assert(codeComprehension::getNextElse(stringExtracted) == "");

    stringExtracted = "elseoups";
    assert(codeComprehension::getNextElse(stringExtracted) == "");

    stringExtracted = "else oups";
    assert(codeComprehension::getNextElse(stringExtracted) == "");

    stringExtracted = "else{";
    assert(codeComprehension::getNextElse(stringExtracted) == "else");

    stringExtracted = "else{prank";
    assert(codeComprehension::getNextElse(stringExtracted) == "else");

}

void test_getNextWhile(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextWhile(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");

    stringExtracted = " while";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");

    stringExtracted = "while";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");

    stringExtracted = "whileoups";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");

    stringExtracted = "while oups";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");

    stringExtracted = "while()";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while()");

    stringExtracted = "while(a&b)";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(a&b)");

    stringExtracted = "while(a&b) ";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(a&b)");

    stringExtracted = "while(test())";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(test())");

    stringExtracted = "while(char == ')')";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(char == ')')");

    stringExtracted = "while(str == \"prank)\")";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(str == \"prank)\")");

    stringExtracted = "while(test(\"prank)\",')'))";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(test(\"prank)\",')'))");
}

void test_getNextFor(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextFor(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextFor(stringExtracted) == "");

    stringExtracted = " for";
    assert(codeComprehension::getNextFor(stringExtracted) == "");

    stringExtracted = "for";
    assert(codeComprehension::getNextFor(stringExtracted) == "");

    stringExtracted = "foroups";
    assert(codeComprehension::getNextFor(stringExtracted) == "");

    stringExtracted = "for oups";
    assert(codeComprehension::getNextFor(stringExtracted) == "");

    stringExtracted = "for()";
    assert(codeComprehension::getNextFor(stringExtracted) == "for()");

    stringExtracted = "for(x;y;z)";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(x;y;z)");

    stringExtracted = "for(x;y;z) ";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(x;y;z)");

    stringExtracted = "for((x);(y);(z))";
    assert(codeComprehension::getNextFor(stringExtracted) == "for((x);(y);(z))");

    stringExtracted = "for(char == ')')";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(char == ')')");

    stringExtracted = "for(str == \"prank)\")";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(str == \"prank)\")");

    stringExtracted = "for(test(\"prank)\",')'))";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(test(\"prank)\",')'))");    
}

void test_getNextSwitch(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextSwitch(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");

    stringExtracted = " switch";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");

    stringExtracted = "switch";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");

    stringExtracted = "switchouf";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");

    stringExtracted = "switch ouf";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");

    stringExtracted = "switch()";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch()");

    stringExtracted = "switch(a+b)";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(a+b)");

    stringExtracted = "switch(a+b) ";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(a+b)");

    stringExtracted = "switch(test())";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(test())");

    stringExtracted = "switch(char == ')')";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(char == ')')");

    stringExtracted = "switch(str == \"prank)\")";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(str == \"prank)\")");

    stringExtracted = "switch(test(\"prank)\",')'))";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(test(\"prank)\",')'))");  
}

void test_getNextCase(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextCase(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextCase(stringExtracted) == "");

    stringExtracted = " case";
    assert(codeComprehension::getNextCase(stringExtracted) == "");

    stringExtracted = "caseouf";
    assert(codeComprehension::getNextCase(stringExtracted) == "");

    stringExtracted = "case 'a':";
    assert(codeComprehension::getNextCase(stringExtracted) == "case 'a':");

    stringExtracted = "case 'a': ";
    assert(codeComprehension::getNextCase(stringExtracted) == "case 'a':");

    stringExtracted = "case ':':";
    assert(codeComprehension::getNextCase(stringExtracted) == "case ':':");
}

void test_getNextDefault(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextDefault(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");

    stringExtracted = " default";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");

    stringExtracted = "default";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");

    stringExtracted = "defaultoups";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");

    stringExtracted = "default oups";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");

    stringExtracted = "default:";
    assert(codeComprehension::getNextDefault(stringExtracted) == "default:");

    stringExtracted = "default:prank";
    assert(codeComprehension::getNextDefault(stringExtracted) == "default:");
}

void test_getNextDo(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextDo(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextDo(stringExtracted) == "");

    stringExtracted = " do";
    assert(codeComprehension::getNextDo(stringExtracted) == "");

    stringExtracted = "do";
    assert(codeComprehension::getNextDo(stringExtracted) == "");

    stringExtracted = "do";
    assert(codeComprehension::getNextDo(stringExtracted) == "");

    stringExtracted = "do";
    assert(codeComprehension::getNextDo(stringExtracted) == "");

    stringExtracted = "do{";
    assert(codeComprehension::getNextDo(stringExtracted) == "do");

    stringExtracted = "do{prank";
    assert(codeComprehension::getNextDo(stringExtracted) == "do");    
}

void test_getNextTry(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextTry(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextTry(stringExtracted) == "");

    stringExtracted = " try";
    assert(codeComprehension::getNextTry(stringExtracted) == "");

    stringExtracted = "try";
    assert(codeComprehension::getNextTry(stringExtracted) == "");

    stringExtracted = "try";
    assert(codeComprehension::getNextTry(stringExtracted) == "");

    stringExtracted = "try";
    assert(codeComprehension::getNextTry(stringExtracted) == "");

    stringExtracted = "try{";
    assert(codeComprehension::getNextTry(stringExtracted) == "try");

    stringExtracted = "try{prank";
    assert(codeComprehension::getNextTry(stringExtracted) == "try");   
}

void test_getNextCatch(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextCatch(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");

    stringExtracted = " catch";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");

    stringExtracted = "catch";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");

    stringExtracted = "catchouf";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");

    stringExtracted = "catch ouf";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");

    stringExtracted = "catch()";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch()");

    stringExtracted = "catch(a&b)";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch(a&b)");

    stringExtracted = "catch(a&b) ";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch(a&b)");

    stringExtracted = "catch(test())";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch(test())");
}

void test_getNextClassic(void)
{
    std::string stringExtracted(";");
    assert(codeComprehension::getNextClassic(stringExtracted) == ";"); 

    stringExtracted = "Something to get;";
    assert(codeComprehension::getNextClassic(stringExtracted) == "Something to get;");
}

void test_getNextPreProc(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextPreProc(stringExtracted) == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "");

    stringExtracted = " #case";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "");

    stringExtracted = "#endif";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#endif");

    stringExtracted = "#endif\n";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#endif");

    stringExtracted = "#define A 2";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define A 2");

    stringExtracted = "#define A 2\n";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define A 2");

    stringExtracted = "#define A 2\nprank";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define A 2");

}

void test_getNextInstr(void)
{    
    std::string stringExtracted("#\nprank");
    assert(codeComprehension::getNextInstr(stringExtracted) == "#\n prank"); 

    stringExtracted = "if()prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "if()");

    stringExtracted = "else{prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "else");

    stringExtracted = "while()prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "while()");

    stringExtracted = "for()prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "for()");

    stringExtracted = "switch()prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "switch()");

    stringExtracted = "do{prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "do");

    stringExtracted = "try{prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "try");

    stringExtracted = "catch()prank";
    assert(codeComprehension::getNextInstr(stringExtracted) == "catch()");

}


int main(void)
{
    TEST(test_stringExtracted);
    TEST(test_getNextString);
    TEST(test_getNextComment);
    TEST(test_getNextIf);
    TEST(test_getNextElse);
    TEST(test_getNextWhile);
    TEST(test_getNextFor);
    TEST(test_getNextSwitch);
    TEST(test_getNextCase);
    TEST(test_getNextDefault);
    TEST(test_getNextDo);
    TEST(test_getNextTry);
    TEST(test_getNextCatch);
    TEST(test_getNextClassic);
    TEST(test_getNextPreProc);
    // TEST(test_getNextInstr);



    return 0;
}
