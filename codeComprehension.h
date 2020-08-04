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
    static std::string fileInVector(std::string file);
    static std::string getNextString(std::string &stringToExtract);
    static std::string getNextComment(std::string &stringToExtract);
    static std::string getNextInstr(std::string &stringToExtract);
    static std::string getNextIf(std::string &stringToExtract);
    static std::string getNextElse(std::string &stringToExtract);
    static std::string getNextWhile(std::string &stringToExtract);
    static std::string getNextFor(std::string &stringToExtract);
    static std::string getNextSwitch(std::string &stringToExtract);
    static std::string getNextCase(std::string &stringToExtract);
    static std::string getNextDefault(std::string &stringToExtract);
    static std::string getNextDo(std::string &stringToExtract);
    static std::string getNextTry(std::string &stringToExtract);
    static std::string getNextCatch(std::string &stringToExtract);
    static std::string getNextClassic(std::string &stringToExtract);
    static std::string getNextPreProc(std::string &stringToExtract);

    void indentAuto(std::string file, int tabSpace, bool newLineAftDeclaration, bool newLineAftProcedure,
                    bool breakBeforeOppBool, bool breakAfterComma, bool bracesAftCommand, bool tabBraces,
                    bool bracesNewLineStruct, bool bracesNewLineClass, bool bracesNewLineEnum, int spaceComment,
                    int tabCase, int tabContinuDecla, bool oneLineArg, bool keepBlankLine, bool alineParentheses,
                    bool eightyChar, bool optiBraces, bool preProcTab);
};

#endif //CODE_GENERATOR_CODE_COMPREHENSION_H