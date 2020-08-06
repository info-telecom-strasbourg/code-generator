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
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextString(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = " \"Prank\"";
    assert(codeComprehension::getNextString(stringExtracted) == "");
    assert(stringExtracted == " \"Prank\""); 

    stringExtracted = "\"Keep this string\"";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Keep this string\"");
    assert(stringExtracted == ""); 

    stringExtracted = "\"Keep this string\" but not this one";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Keep this string\"");
    assert(stringExtracted == " but not this one"); 

    stringExtracted = "\"Are u \\\"kidding\\\" me\"";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Are u \\\"kidding\\\" me\"");
    assert(stringExtracted == ""); 

    stringExtracted = "\"Line\\ \n break\"";
    assert(codeComprehension::getNextString(stringExtracted) == "\"Line\\ \n break\"");
    assert(stringExtracted == ""); 
}

void test_getNextOpeningBrace(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextOpeningBrace(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextOpeningBrace(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = " {";
    assert(codeComprehension::getNextOpeningBrace(stringExtracted) == "");
    assert(stringExtracted == " {"); 

    stringExtracted = "{";
    assert(codeComprehension::getNextOpeningBrace(stringExtracted) == "{");
    assert(stringExtracted == ""); 

    stringExtracted = "{prank";
    assert(codeComprehension::getNextOpeningBrace(stringExtracted) == "{");
    assert(stringExtracted == "prank"); 
}

void test_getNextClosingBrace(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextClosingBrace(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextClosingBrace(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = " }";
    assert(codeComprehension::getNextClosingBrace(stringExtracted) == "");
    assert(stringExtracted == " }"); 

    stringExtracted = "}";
    assert(codeComprehension::getNextClosingBrace(stringExtracted) == "}");
    assert(stringExtracted == ""); 

    stringExtracted = "}prank";
    assert(codeComprehension::getNextClosingBrace(stringExtracted) == "}");
    assert(stringExtracted == "prank"); 
}

void test_getNextSpace(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextSpace(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextSpace(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = "prank ";
    assert(codeComprehension::getNextSpace(stringExtracted) == "");
    assert(stringExtracted == "prank "); 

    stringExtracted = " ";
    assert(codeComprehension::getNextSpace(stringExtracted) == " ");
    assert(stringExtracted == ""); 

    stringExtracted = " prank";
    assert(codeComprehension::getNextSpace(stringExtracted) == " ");
    assert(stringExtracted == "prank"); 
}

void test_getNextLinebreak(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextLinebreak(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextLinebreak(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = "prank\n";
    assert(codeComprehension::getNextLinebreak(stringExtracted) == "");
    assert(stringExtracted == "prank\n"); 

    stringExtracted = "\n";
    assert(codeComprehension::getNextLinebreak(stringExtracted) == "\n");
    assert(stringExtracted == ""); 

    stringExtracted = "\nprank";
    assert(codeComprehension::getNextLinebreak(stringExtracted) == "\n");
    assert(stringExtracted == "prank"); 
}

void test_getNextTabulation(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextTabulation(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextTabulation(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = "prank\t";
    assert(codeComprehension::getNextTabulation(stringExtracted) == "");
    assert(stringExtracted == "prank\t"); 

    stringExtracted = "\t";
    assert(codeComprehension::getNextTabulation(stringExtracted) == "\t");
    assert(stringExtracted == ""); 

    stringExtracted = "\tprank";
    assert(codeComprehension::getNextTabulation(stringExtracted) == "\t");
    assert(stringExtracted == "prank"); 
}

void test_getNextComment(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextComment(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "No comment";
    assert(codeComprehension::getNextComment(stringExtracted) == "");
    assert(stringExtracted == "No comment"); 

    stringExtracted = " //Prank";
    assert(codeComprehension::getNextComment(stringExtracted) == "");
    assert(stringExtracted == " //Prank"); 

    stringExtracted = " /*Prank*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "");
    assert(stringExtracted == " /*Prank*/"); 

    stringExtracted = "//Comment\n";
    assert(codeComprehension::getNextComment(stringExtracted) == "//Comment");
    assert(stringExtracted == "\n"); 

    stringExtracted = "/*Comment*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment*/");
    assert(stringExtracted == ""); 

    stringExtracted = "/*Comment*/ but not here";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment*/");
    assert(stringExtracted == " but not here"); 

    stringExtracted = "/*Comment";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment");
    assert(stringExtracted == ""); 

    stringExtracted = "/*//Tricky comment*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*//Tricky comment*/");
    assert(stringExtracted == ""); 

    stringExtracted = "///*Comment\n";
    assert(codeComprehension::getNextComment(stringExtracted) == "///*Comment");
    assert(stringExtracted == "\n"); 

    stringExtracted = "/*Comment\nwith a line break*/";
    assert(codeComprehension::getNextComment(stringExtracted) == "/*Comment\nwith a line break*/");
    assert(stringExtracted == ""); 
}

void test_getNextIf(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextIf(stringExtracted) == ""); 
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextIf(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = " if";
    assert(codeComprehension::getNextIf(stringExtracted) == "");
    assert(stringExtracted == " if"); 

    stringExtracted = "if";
    assert(codeComprehension::getNextIf(stringExtracted) == "");
    assert(stringExtracted == "if"); 

    stringExtracted = "ifouf";
    assert(codeComprehension::getNextIf(stringExtracted) == "");
    assert(stringExtracted == "ifouf"); 

    stringExtracted = "if ouf";
    assert(codeComprehension::getNextIf(stringExtracted) == "");
    assert(stringExtracted == "if ouf"); 

    stringExtracted = "if()";
    assert(codeComprehension::getNextIf(stringExtracted) == "if()");
    assert(stringExtracted == ""); 

    stringExtracted = "if(a&b)";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(a&b)");
    assert(stringExtracted == ""); 

    stringExtracted = "if(a&b) ";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(a&b)");
    assert(stringExtracted == " "); 

    stringExtracted = "if(test())";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(test())");
    assert(stringExtracted == ""); 

    stringExtracted = "if(char == ')')";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(char == ')')");
    assert(stringExtracted == ""); 

    stringExtracted = "if(str == \"prank)\")";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(str == \"prank)\")");
    assert(stringExtracted == ""); 

    stringExtracted = "if(test(\"prank)\",')'))";
    assert(codeComprehension::getNextIf(stringExtracted) == "if(test(\"prank)\",')'))");
    assert(stringExtracted == ""); 
}

void test_getNextElse(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextElse(stringExtracted) == ""); 
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextElse(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = " else";
    assert(codeComprehension::getNextElse(stringExtracted) == "");
    assert(stringExtracted == " else"); 

    stringExtracted = "else";
    assert(codeComprehension::getNextElse(stringExtracted) == "");
    assert(stringExtracted == "else"); 

    stringExtracted = "elseoups";
    assert(codeComprehension::getNextElse(stringExtracted) == "");
    assert(stringExtracted == "elseoups"); 

    stringExtracted = "else oups";
    assert(codeComprehension::getNextElse(stringExtracted) == "");
    assert(stringExtracted == "else oups"); 

    stringExtracted = "else{";
    assert(codeComprehension::getNextElse(stringExtracted) == "else");
    assert(stringExtracted == "{"); 

    stringExtracted = "else{prank";
    assert(codeComprehension::getNextElse(stringExtracted) == "else");
    assert(stringExtracted == "{prank"); 

}

void test_getNextWhile(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextWhile(stringExtracted) == ""); 
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get"); 

    stringExtracted = " while";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");
    assert(stringExtracted == " while"); 

    stringExtracted = "while";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");
    assert(stringExtracted == "while"); 

    stringExtracted = "whileoups";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");
    assert(stringExtracted == "whileoups"); 

    stringExtracted = "while oups";
    assert(codeComprehension::getNextWhile(stringExtracted) == "");
    assert(stringExtracted == "while oups"); 

    stringExtracted = "while()";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while()");
    assert(stringExtracted == ""); 

    stringExtracted = "while(a&b)";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(a&b)");
    assert(stringExtracted == ""); 

    stringExtracted = "while(a&b) ";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(a&b)");
    assert(stringExtracted == " "); 

    stringExtracted = "while(test())";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(test())");
    assert(stringExtracted == ""); 

    stringExtracted = "while(char == ')')";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(char == ')')");
    assert(stringExtracted == ""); 

    stringExtracted = "while(str == \"prank)\")";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(str == \"prank)\")");
    assert(stringExtracted == ""); 

    stringExtracted = "while(test(\"prank)\",')'))";
    assert(codeComprehension::getNextWhile(stringExtracted) == "while(test(\"prank)\",')'))");
    assert(stringExtracted == ""); 
}

void test_getNextFor(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextFor(stringExtracted) == "");
    assert(stringExtracted == ""); 

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextFor(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " for";
    assert(codeComprehension::getNextFor(stringExtracted) == "");
    assert(stringExtracted == " for");

    stringExtracted = "for";
    assert(codeComprehension::getNextFor(stringExtracted) == "");
    assert(stringExtracted == "for");

    stringExtracted = "foroups";
    assert(codeComprehension::getNextFor(stringExtracted) == "");
    assert(stringExtracted == "foroups");

    stringExtracted = "for oups";
    assert(codeComprehension::getNextFor(stringExtracted) == "");
    assert(stringExtracted == "for oups");

    stringExtracted = "for()";
    assert(codeComprehension::getNextFor(stringExtracted) == "for()");
    assert(stringExtracted == "");

    stringExtracted = "for(x;y;z)";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(x;y;z)");
    assert(stringExtracted == "");

    stringExtracted = "for(x;y;z) ";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(x;y;z)");
    assert(stringExtracted == " ");

    stringExtracted = "for((x);(y);(z))";
    assert(codeComprehension::getNextFor(stringExtracted) == "for((x);(y);(z))");
    assert(stringExtracted == "");

    stringExtracted = "for(char == ')')";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(char == ')')");
    assert(stringExtracted == "");

    stringExtracted = "for(str == \"prank)\")";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(str == \"prank)\")");
    assert(stringExtracted == "");

    stringExtracted = "for(test(\"prank)\",')'))";
    assert(codeComprehension::getNextFor(stringExtracted) == "for(test(\"prank)\",')'))");
    assert(stringExtracted == "");    
}

void test_getNextSwitch(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextSwitch(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " switch";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");
    assert(stringExtracted == " switch");

    stringExtracted = "switch";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");
    assert(stringExtracted == "switch");

    stringExtracted = "switchouf";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");
    assert(stringExtracted == "switchouf");

    stringExtracted = "switch ouf";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "");
    assert(stringExtracted == "switch ouf");

    stringExtracted = "switch()";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch()");
    assert(stringExtracted == "");

    stringExtracted = "switch(a+b)";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(a+b)");
    assert(stringExtracted == "");

    stringExtracted = "switch(a+b) ";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(a+b)");
    assert(stringExtracted == " ");

    stringExtracted = "switch(test())";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(test())");
    assert(stringExtracted == "");

    stringExtracted = "switch(char == ')')";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(char == ')')");
    assert(stringExtracted == "");

    stringExtracted = "switch(str == \"prank)\")";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(str == \"prank)\")");
    assert(stringExtracted == "");

    stringExtracted = "switch(test(\"prank)\",')'))";
    assert(codeComprehension::getNextSwitch(stringExtracted) == "switch(test(\"prank)\",')'))");  
    assert(stringExtracted == "");
}

void test_getNextCase(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextCase(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextCase(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " case";
    assert(codeComprehension::getNextCase(stringExtracted) == "");
    assert(stringExtracted == " case");

    stringExtracted = "caseouf";
    assert(codeComprehension::getNextCase(stringExtracted) == "");
    assert(stringExtracted == "caseouf");

    stringExtracted = "case 'a':";
    assert(codeComprehension::getNextCase(stringExtracted) == "case 'a':");
    assert(stringExtracted == "");

    stringExtracted = "case 'a': ";
    assert(codeComprehension::getNextCase(stringExtracted) == "case 'a':");
    assert(stringExtracted == " ");

    stringExtracted = "case ':':";
    assert(codeComprehension::getNextCase(stringExtracted) == "case ':':");
    assert(stringExtracted == "");
}

void test_getNextDefault(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextDefault(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " default";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");
    assert(stringExtracted == " default");

    stringExtracted = "default";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");
    assert(stringExtracted == "default");

    stringExtracted = "defaultoups";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");
    assert(stringExtracted == "defaultoups");

    stringExtracted = "default oups";
    assert(codeComprehension::getNextDefault(stringExtracted) == "");
    assert(stringExtracted == "default oups");

    stringExtracted = "default:";
    assert(codeComprehension::getNextDefault(stringExtracted) == "default:");
    assert(stringExtracted == "");

    stringExtracted = "default:prank";
    assert(codeComprehension::getNextDefault(stringExtracted) == "default:");
    assert(stringExtracted == "prank");
}

void test_getNextDo(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextDo(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextDo(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " do";
    assert(codeComprehension::getNextDo(stringExtracted) == "");
    assert(stringExtracted == " do");

    stringExtracted = "do";
    assert(codeComprehension::getNextDo(stringExtracted) == "");
    assert(stringExtracted == "do");

    stringExtracted = "dooups";
    assert(codeComprehension::getNextDo(stringExtracted) == "");
    assert(stringExtracted == "dooups"); 

    stringExtracted = "do oups";
    assert(codeComprehension::getNextDo(stringExtracted) == "");
    assert(stringExtracted == "do oups"); 

    stringExtracted = "do{";
    assert(codeComprehension::getNextDo(stringExtracted) == "do");
    assert(stringExtracted == "{");

    stringExtracted = "do{prank";
    assert(codeComprehension::getNextDo(stringExtracted) == "do"); 
    assert(stringExtracted == "{prank");   
}

void test_getNextTry(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextTry(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextTry(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " try";
    assert(codeComprehension::getNextTry(stringExtracted) == "");
    assert(stringExtracted == " try");

    stringExtracted = "try";
    assert(codeComprehension::getNextTry(stringExtracted) == "");
    assert(stringExtracted == "try");

    stringExtracted = "tryoups";
    assert(codeComprehension::getNextTry(stringExtracted) == "");
    assert(stringExtracted == "tryoups"); 

    stringExtracted = "try oups";
    assert(codeComprehension::getNextTry(stringExtracted) == "");
    assert(stringExtracted == "try oups"); 

    stringExtracted = "try{";
    assert(codeComprehension::getNextTry(stringExtracted) == "try");
    assert(stringExtracted == "{");

    stringExtracted = "try{prank";
    assert(codeComprehension::getNextTry(stringExtracted) == "try");
    assert(stringExtracted == "{prank");   
}

void test_getNextCatch(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextCatch(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");

    stringExtracted = " catch";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");
    assert(stringExtracted == " catch");

    stringExtracted = "catch";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");
    assert(stringExtracted == "catch");

    stringExtracted = "catchouf";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");
    assert(stringExtracted == "catchouf");

    stringExtracted = "catch ouf";
    assert(codeComprehension::getNextCatch(stringExtracted) == "");
    assert(stringExtracted == "catch ouf");

    stringExtracted = "catch()";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch()");
    assert(stringExtracted == "");

    stringExtracted = "catch(a&b)";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch(a&b)");
    assert(stringExtracted == "");

    stringExtracted = "catch(a&b) ";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch(a&b)");
    assert(stringExtracted == " ");

    stringExtracted = "catch(test())";
    assert(codeComprehension::getNextCatch(stringExtracted) == "catch(test())");
    assert(stringExtracted == "");
}

void test_getNextClassic(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextClassic(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Something to get";
    assert(codeComprehension::getNextClassic(stringExtracted) == "Something to get");
    assert(stringExtracted == "");

    stringExtracted = "Something to get;";
    assert(codeComprehension::getNextClassic(stringExtracted) == "Something to get;");
    assert(stringExtracted == "");
   
    stringExtracted = "Something to get;But note here;";
    assert(codeComprehension::getNextClassic(stringExtracted) == "Something to get;");
    assert(stringExtracted == "But note here;");

    stringExtracted = "std::cout << \"This is a semicolon : ;\";";
    assert(codeComprehension::getNextClassic(stringExtracted) == "std::cout << \"This is a semicolon : ;\";");
    assert(stringExtracted == "");

    stringExtracted = "std::cout << ';';";
    assert(codeComprehension::getNextClassic(stringExtracted) == "std::cout << ';';");
    assert(stringExtracted == "");

    stringExtracted = "std::cout << \"This is a semicolon : ;\" << ';';";
    assert(codeComprehension::getNextClassic(stringExtracted) == "std::cout << \"This is a semicolon : ;\" << ';';");
    assert(stringExtracted == "");
}

void test_getNextPreProc(void)
{
    std::string stringExtracted("");
    assert(codeComprehension::getNextPreProc(stringExtracted) == ""); 
    assert(stringExtracted == "");

    stringExtracted = "Nothing to get";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "");
    assert(stringExtracted == "Nothing to get");
    
    stringExtracted = " #case";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "");
    assert(stringExtracted == " #case");

    stringExtracted = "#endif";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#endif");
    assert(stringExtracted == "");

    stringExtracted = "#endif\n";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#endif\n");
    assert(stringExtracted == "");

    stringExtracted = "#define A 2";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define A 2");
    assert(stringExtracted == "");

    stringExtracted = "#define A 2\n";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define A 2\n");
    assert(stringExtracted == "");

    stringExtracted = "#define A 2\nprank";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define A 2\n");
    assert(stringExtracted == "prank");

    stringExtracted = "#define CCCHECK(op, msg)\\\ndo\n";
    assert(codeComprehension::getNextPreProc(stringExtracted) == "#define CCCHECK(op, msg)\\\ndo\n");
    assert(stringExtracted == "");

}

void test_getNextItem(void)
{
    std::string stringExtracted("#endif\nprank");
    assert(codeComprehension::getNextItem(stringExtracted) == "#endif\n");
    assert(stringExtracted == "prank");

    stringExtracted = "/*comment*/prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "/*comment*/");
    assert(stringExtracted == "prank");

    stringExtracted = "\"text\"prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "\"text\"");
    assert(stringExtracted == "prank");

    stringExtracted = "{prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "{");
    assert(stringExtracted == "prank");

    stringExtracted = "}prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "}");
    assert(stringExtracted == "prank");

    stringExtracted = " prank";
    assert(codeComprehension::getNextItem(stringExtracted) == " ");
    assert(stringExtracted == "prank");

    stringExtracted = "\nprank";
    assert(codeComprehension::getNextItem(stringExtracted) == "\n");
    assert(stringExtracted == "prank");

    stringExtracted = "\tprank";
    assert(codeComprehension::getNextItem(stringExtracted) == "\t");
    assert(stringExtracted == "prank");

    stringExtracted = "if()prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "if()");
    assert(stringExtracted == "prank");

    stringExtracted = "else{prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "else");
    assert(stringExtracted == "{prank");

    stringExtracted = "while()prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "while()");
    assert(stringExtracted == "prank");

    stringExtracted = "for()prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "for()");
    assert(stringExtracted == "prank");

    stringExtracted = "switch()prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "switch()");
    assert(stringExtracted == "prank");

    stringExtracted = "case 'a':prank";
    assert(codeComprehension::getNextCase(stringExtracted) == "case 'a':");
    assert(stringExtracted == "prank");

    stringExtracted = "default:prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "default:");
    assert(stringExtracted == "prank");

    stringExtracted = "do{prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "do");
    assert(stringExtracted == "{prank");

    stringExtracted = "try{prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "try");
    assert(stringExtracted == "{prank");

    stringExtracted = "catch()prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "catch()");
    assert(stringExtracted == "prank");

    stringExtracted = "Something classic to get;prank";
    assert(codeComprehension::getNextItem(stringExtracted) == "Something classic to get;");
    assert(stringExtracted == "prank");
}


int main(void)
{
    std::cout << "----- Launch tests for the library codeComprehension -----" << std::endl << std::endl;
    TEST(test_stringExtracted);
    TEST(test_getNextString);
    TEST(test_getNextOpeningBrace);
    TEST(test_getNextClosingBrace);
    TEST(test_getNextSpace);
    TEST(test_getNextLinebreak);
    TEST(test_getNextTabulation);
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
    TEST(test_getNextItem);

    return 0;
}
