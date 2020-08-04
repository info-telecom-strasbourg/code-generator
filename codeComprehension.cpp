#include "codeComprehension.hpp"

#define CCCHECK(op, msg)              \
    do                                \
    {                                 \
        if (!op)                      \
        {                             \
            std::cerr << msg << endl; \
            exit(EXIT_FAILURE);       \
        }                             \
    } while (0)

using namespace std;

string
codeComprehension::fileInVector(string file)
{
    ifstream fileToRead(file, ios::in | ios::ate);
    string str;

    fileToRead.seekg(0, ios::end);
    ifstream::streampos size = fileToRead.tellg();
    cout << size << endl;
    str.reserve(size);
    fileToRead.seekg(0, ios::beg);

    str.assign((istreambuf_iterator<char>(fileToRead)),
               istreambuf_iterator<char>());
    return str;
}

string
codeComprehension::getNextString(string &stringToExtract)
{
    if (stringToExtract[0] != '\"')
    {
        cerr << "The first sub string is not a string" << endl;
        return "";
    }

    int i(1);
    while ((stringToExtract[i] != '\"' || stringToExtract[i - 1] == '\\') && i + 1 < stringToExtract.size())
        i++;

    string nextString = stringToExtract.substr(0, i + 1);
    stringToExtract.erase(0, i + 1);
    return nextString;
}

string
codeComprehension::getNextComment(string &stringToExtract)
{
    if(stringToExtract[0] != '/')
    {
        cerr << "The first sub string is not a comment" << endl;
        return "";
    }
    string endComment = (stringToExtract[1] == '/') ? "\n" : "*/";
    int lengthEndComment = (stringToExtract[1] == '/') ? 1 : 2;


    int i(2);
    while (stringToExtract.substr(i,lengthEndComment) != endComment && i + lengthEndComment < stringToExtract.size())
        i++;
    string nextComment = stringToExtract.substr(0, i + lengthEndComment);
    stringToExtract.erase(0, i + 1);
    return nextComment;
}

string
codeComprehension::getNextInstr(string &stringToExtract)
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

string
codeComprehension::getNextIf(string &stringToExtract)
{
    if(stringToExtract.substr(0,3) != "if(")
    {
        cerr << "The first sub string is not a if" << endl;
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

    string nextIf = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextIf;
}

string
codeComprehension::getNextElse(string &stringToExtract)
{
    if (stringToExtract.substr(0, 5) != "else{")
    {
        cerr << "The first sub string is not a else" << endl;
        return "";
    }

    string nextIf = stringToExtract.substr(0, 5);
    stringToExtract.erase(0, 5);
    return nextIf;
}

string
codeComprehension::getNextWhile(string &stringToExtract)
{
    if (stringToExtract.substr(0, 6) != "while(")
    {
        cerr << "The first sub string is not a while" << endl;
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

    string nextWhile = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextWhile;
}

string
codeComprehension::getNextFor(string &stringToExtract)
{
    if (stringToExtract.substr(0, 4) != "for(")
    {
        cerr << "The first sub string is not a for" << endl;
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

    string nextWhile = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextWhile;
}

string
codeComprehension::getNextSwitch(string &stringToExtract)
{
    if (stringToExtract.substr(0, 7) != "switch(")
    {
        cerr << "The first sub string is not a switch" << endl;
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

    string nextWhile = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextWhile;
}

string
codeComprehension::getNextCase(string &stringToExtract)
{
    if (stringToExtract.substr(0, 5) != "case ")
    {
        cerr << "The first sub string is not a case" << endl;
        return "";
    }

    string nextCase = stringToExtract.substr(0, 5);
    stringToExtract.erase(0, 5);
    return nextCase;
}

string
codeComprehension::getNextDefault(string &stringToExtract)
{
    if (stringToExtract.substr(0, 8) != "default:")
    {
        cerr << "The first sub string is not a default" << endl;
        return "";
    }

    string nextDefault = stringToExtract.substr(0, 8);
    stringToExtract.erase(0, 8);
    return nextDefault;
}

string
codeComprehension::getNextDo(string &stringToExtract)
{
    if (stringToExtract.substr(0, 3) != "do{")
    {
        cerr << "The first sub string is not a do" << endl;
        return "";
    }

    string nextDo = stringToExtract.substr(0, 3);
    stringToExtract.erase(0, 3);
    return nextDo;
}

string
codeComprehension::getNextTry(string &stringToExtract)
{
    if (stringToExtract.substr(0, 4) != "try{")
    {
        cerr << "The first sub string is not a try" << endl;
        return "";
    }

    string nextTry = stringToExtract.substr(0, 4);
    stringToExtract.erase(0, 4);
    return nextTry;
}

string
codeComprehension::getNextCatch(string &stringToExtract)
{
    if (stringToExtract.substr(0, 6) != "catch(")
    {
        cerr << "The first sub string is not a catch" << endl;
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

    string nextCatch = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextCatch;
}

string
codeComprehension::getNextClassic(string &stringToExtract)
{
    int i(0);
    while(stringToExtract[i] != ';')
        i++;

    string nextClasic = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextClasic;
}

string
codeComprehension::getNextPreProc(string &stringToExtract)
{
    if (stringToExtract[0] != '#')
    {
        cerr << "The first sub string is not a #" << endl;
        return "";
    }

    int i(0);
    int backSlash(0);
    while(stringToExtract[i] != '\n')
        i++;

    string nextProc = stringToExtract.substr(0, i);
    stringToExtract.erase(0, i);
    return nextProc;
}