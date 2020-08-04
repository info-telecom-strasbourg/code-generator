#ifndef CODE_GENERATOR_CODE_COMPREHENSION_H
#define CODE_GENERATOR_CODE_COMPREHENSION_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

class codeComprehension
{
private:
    int openedBraces = 0;
    int openedParentheses = 0;
    int openedHook = 0;
    int tabNumb = 0;

public:
	static std::string
	fileInVector(std::string file)
	{
	    std::ifstream fileToRead(file, std::ios::in | std::ios::ate);
	    std::string str;

	    fileToRead.seekg(0, std::ios::end);
	    std::ifstream::streampos size = fileToRead.tellg();
	    std::cout << size << std::endl;
	    str.reserve(size);
	    fileToRead.seekg(0, std::ios::beg);

	    str.assign((std::istreambuf_iterator<char>(fileToRead)),
	               std::istreambuf_iterator<char>());
	    return str;
	}

	static std::string
	getNextString(std::string &stringToExtract)
	{
	    if (stringToExtract[0] != '\"')
	    {
	        std::cerr << "The first sub string is not a string" << std::endl;
	        return "";
	    }

	    int i(1);
	    while ((stringToExtract[i] != '\"' || stringToExtract[i - 1] == '\\') && i + 1 < stringToExtract.size())
	        i++;

	    std::string nextString = stringToExtract.substr(0, i + 1);
	    stringToExtract.erase(0, i + 1);
	    return nextString;
	}

	static std::string
	getNextComment(std::string &stringToExtract)
	{
	    if(stringToExtract[0] != '/')
	    {
	        std::cerr << "The first sub string is not a comment" << std::endl;
	        return "";
	    }
	    std::string endComment = (stringToExtract[1] == '/') ? "\n" : "*/";
	    int lengthEndComment = (stringToExtract[1] == '/') ? 1 : 2;


	    int i(2);
	    while (stringToExtract.substr(i,lengthEndComment) != endComment && i + lengthEndComment < stringToExtract.size())
	        i++;
	    std::string nextComment = stringToExtract.substr(0, i + lengthEndComment);
	    stringToExtract.erase(0, i + 1);
	    return nextComment;
	}

	static std::string
	getNextInstr(std::string &stringToExtract)
	{
	    if(stringToExtract[0] == '#')
	        return getNextPreProc(stringToExtract);
	    else if(stringToExtract.substr(0, 2) == "if")
	        return getNextIf(stringToExtract);
	    else if(stringToExtract.substr(0, 4) == "else")
	        return getNextElse(stringToExtract);
	    else if(stringToExtract.substr(0, 5) == "while")
	        return getNextWhile(stringToExtract);
	    else if(stringToExtract.substr(0, 3) == "for")
	        return getNextFor(stringToExtract);
	    else if(stringToExtract.substr(0, 5) == "switch")
	        return getNextSwitch(stringToExtract);
	    else if(stringToExtract.substr(0, 2) == "do")
	        return getNextDo(stringToExtract);
	    else if(stringToExtract.substr(0, 3) == "try")
	        return getNextTry(stringToExtract);
	    else if(stringToExtract.substr(0, 5) == "catch")
	        return getNextCatch(stringToExtract);
	    else
	        return getNextClassic(stringToExtract);
	}

	static std::string
	getNextIf(std::string &stringToExtract)
	{
	    if(stringToExtract.substr(0,2) != "if")
	    {
	        std::cerr << "The first sub string is not a if" << std::endl;
	        return "";
	    }
	    int i(3);

	    int parentheses(1);
	    while (parentheses > 0 && i < stringToExtract.size())
	    {
	        if (stringToExtract[i] == '(')
	            parentheses++;
	        else if (stringToExtract[i] == ')')
	            parentheses--;
	        i++;
	    }

	    std::string nextIf = stringToExtract.substr(0, i - 1);
	    stringToExtract.erase(0, i - 1);
	    return nextIf;
	}

	static std::string
	getNextElse(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 4) != "else")
	    {
	        std::cerr << "The first sub string is not a else" << std::endl;
	        return "";
	    }

	    std::string nextIf = stringToExtract.substr(0, 4);
	    stringToExtract.erase(0, 4);
	    return nextIf;
	}

	static std::string
	getNextWhile(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 5) != "while")
	    {
	        std::cerr << "The first sub string is not a while" << std::endl;
	        return "";
	    }

	    int i(6);

	    int parentheses(1);
	    while(parentheses > 0 && i < stringToExtract.size())
	    {
	        if(stringToExtract[i] == '(')
	            parentheses++;
	        else if (stringToExtract[i] == ')')
	            parentheses--;
	        i++;
	    }

	    std::string nextWhile = stringToExtract.substr(0, i - 1);
	    stringToExtract.erase(0, i - 1);
	    return nextWhile;
	}

	static std::string
	getNextFor(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 3) != "for")
	    {
	        std::cerr << "The first sub string is not a for" << std::endl;
	        return "";
	    }

	    int i(4);
	    int parentheses(1);
	    while (parentheses > 0 && i < stringToExtract.size())
	    {
	        if (stringToExtract[i] == '(')
	            parentheses++;
	        else if (stringToExtract[i] == ')')
	            parentheses--;
	        i++;
	    }

	    std::string nextWhile = stringToExtract.substr(0, i - 1);
	    stringToExtract.erase(0, i - 1);
	    return nextWhile;
	}

	static std::string
	getNextSwitch(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 6) != "switch")
	    {
	        std::cerr << "The first sub string is not a switch" << std::endl;
	        return "";
	    }

	    int i(7);
	    int parentheses(1);
	    while (parentheses > 0 && i < stringToExtract.size())
	    {
	        if (stringToExtract[i] == '(')
	            parentheses++;
	        else if (stringToExtract[i] == ')')
	            parentheses--;
	        i++;
	    }

	    std::string nextWhile = stringToExtract.substr(0, i - 1);
	    stringToExtract.erase(0, i - 1);
	    return nextWhile;
	}

	static std::string
	getNextCase(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 4) != "case")
	    {
	        std::cerr << "The first sub string is not a case" << std::endl;
	        return "";
	    }

	    std::string nextCase = stringToExtract.substr(0, 5);
	    stringToExtract.erase(0, 5);
	    return nextCase;
	}

	static std::string
	getNextDefault(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 7) != "default")
	    {
	        std::cerr << "The first sub string is not a default" << std::endl;
	        return "";
	    }

	    std::string nextDefault = stringToExtract.substr(0, 8);
	    stringToExtract.erase(0, 8);
	    return nextDefault;
	}

	static std::string
	getNextDo(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 2) != "do")
	    {
	        std::cerr << "The first sub string is not a do" << std::endl;
	        return "";
	    }

	    std::string nextDo = stringToExtract.substr(0, 2);
	    stringToExtract.erase(0, 2);
	    return nextDo;
	}

	static std::string
	getNextTry(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 3) != "try")
	    {
	        std::cerr << "The first sub string is not a try" << std::endl;
	        return "";
	    }

	    std::string nextTry = stringToExtract.substr(0, 3);
	    stringToExtract.erase(0, 3);
	    return nextTry;
	}

	static std::string
	getNextCatch(std::string &stringToExtract)
	{
	    if (stringToExtract.substr(0, 5) != "catch")
	    {
	        std::cerr << "The first sub string is not a catch" << std::endl;
	        return "";
	    }

	    int i(6);
	    int parentheses(1);
	    while (parentheses > 0 && i < stringToExtract.size())
	    {
	        if (stringToExtract[i] == '(')
	            parentheses++;
	        else if (stringToExtract[i] == ')')
	            parentheses--;
	        i++;
	    }

	    std::string nextCatch = stringToExtract.substr(0, i - 1);
	    stringToExtract.erase(0, i - 1);
	    return nextCatch;
	}

	static std::string
	getNextClassic(std::string &stringToExtract)
	{
	    int i(0);
	    while(stringToExtract[i] != ';')
	        i++;

	    std::string nextClasic = stringToExtract.substr(0, i);
	    stringToExtract.erase(0, i);
	    return nextClasic;
	}

	static std::string
	getNextPreProc(std::string &stringToExtract)
	{
	    if (stringToExtract[0] != '#')
	    {
	        std::cerr << "The first sub string is not a #" << std::endl;
	        return "";
	    }

	    int i(0);
	    int backSlash(0);
	    while(stringToExtract[i] != '\n')
	        i++;

	    std::string nextProc = stringToExtract.substr(0, i);
	    stringToExtract.erase(0, i);
	    return nextProc;
	}


    void indentAuto(std::string file, int tabSpace, bool newLineAftDeclaration, bool newLineAftProcedure,
                    bool breakBeforeOppBool, bool breakAfterComma, bool bracesAftCommand, bool tabBraces,
                    bool bracesNewLineStruct, bool bracesNewLineClass, bool bracesNewLineEnum, int spaceComment,
                    int tabCase, int tabContinuDecla, bool oneLineArg, bool keepBlankLine, bool alineParentheses,
                    bool eightyChar, bool optiBraces, bool preProcTab);
};

#endif //CODE_GENERATOR_CODE_COMPREHENSION_H
