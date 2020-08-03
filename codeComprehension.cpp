#include "codeComprehension.h"


#define CCCHECK(op, msg)        \
    do                          \
    {                           \
        if (!op)                \
        {                       \
            std::cerr << msg;   \
            exit(EXIT_FAILURE); \
        }                       \
    } while (0)

using namespace std;

void codeComprehension::indentAuto(string file, int tabSpace, bool newLineAftDeclaration, bool newLineAftProcedure,
                                   bool breakBeforeOppBool, bool breakAfterComma, bool bracesAftCommand, bool tabBraces,
                                   bool bracesNewLineStruct, bool bracesNewLineClass, bool bracesNewLineEnum,
                                   int spaceComment, int tabCase, int tabContinuDecla, bool oneLineArg,
                                   bool keepBlankLine, bool alineParentheses, bool eightyChar, bool optiBraces)
{
    string buffer = fileInVector(file);
    ofstream indentedCode(file.c_str());
    CCCHECK(indentedCode, "Could not open the file");
    unsigned long buferSize = buffer.size();
    
}

string codeComprehension::fileInVector(string file)
{
    ifstream fileToRead(file);
    string str;

    fileToRead.seekg(0, ios::end);
    str.reserve(t.tellg());
    fileToRead.seekg(0, ios::beg);

    str.assign((istreambuf_iterator<char>(fileToRead)),
               istreambuf_iterator<char>());
    return str;
}

vector<string> codeComprehension::separatedBlocks(string fileContent)
{
    vector<string> blocks();
    size_t found = fileContent.(class);
}