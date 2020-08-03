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

        string fileInVector(string file);
        vector<string> separatedBlocks(string fileContent);

    public:
        void indentAuto(string file, int tabSpace, bool newLineAftDeclaration, bool newLineAftProcedure,
                bool breakBeforeOppBool,bool breakAfterComma, bool bracesAftCommand, bool tabBraces,
                bool bracesNewLineStruct, bool bracesNewLineClass, bool bracesNewLineEnum, int spaceComment,
                int tabCase, int tabContinuDecla, bool oneLineArg, bool keepBlankLine, bool alineParentheses,
                bool eightyChar, bool optiBraces);


};


#endif //CODE_GENERATOR_CODE_COMPREHENSION_H
