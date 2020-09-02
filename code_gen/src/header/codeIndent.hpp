#ifndef CODE_INDENT_H
#define CODE_INDENT_H

#include "codeComprehension.hpp"
#include "codeWrite.hpp"

/**
 * A class that indent automatically a code
 */
class codeIndent : codeComprehension, codeWrite
{
static void indentAuto(std::string inputFile, std::string outputFile, int tabSpace, bool newLineAftDeclaration, bool newLineAftInstr,
						   bool breakBeforeOppBool, bool breakAfterComma, bool bracesAftCommand, bool tabBraces,
						   bool bracesNewLineStruct, bool bracesNewLineClass, bool bracesNewLineEnum, int spaceComment,
						   int tabCase, int tabContinuDecla, bool oneLineArg, bool keepBlankLine, bool alineParentheses,
						   bool eightyChar, bool optiBraces, bool preProcTab, bool spaceInstrPar, bool spaceInstBraces)
	{
		std::ofstream outFile;
		if (outputFile == "")
			outFile.open(inputFile);
		else
			outFile.open(outputFile);

		std::string toIndent = fileInVector(inputFile);
		int tabNum(0);
		while (toIndent.size() > 0)
		{
			if (toIndent[0] == '#')
				outFile << indentPreProc(toIndent);
			else if (toIndent[0] == ' ')
			{
				outFile << '\n';
				toIndent.erase(0, 1);
			}
			else if (toIndent[0] == '{')
				caseOpenBrace(outFile, toIndent, tabNum, newLineAftInstr, spaceInstBraces);
			else if (toIndent[0] == '}')
				caseCloseBrace(outFile, toIndent, tabNum);
			else if (toIndent.substr(0, 3) == "if(")
				outFile << indentIf(toIndent);
			else if (toIndent.substr(0, 4) == "for(")
				outFile << indentFor(toIndent);
			else if (toIndent.substr(0, 6) == "while(")
				outFile << indentWhile(toIndent);
			else if (toIndent.substr(0, 7) == "switch(")
				outFile << indentSwitch(toIndent);
			else if (toIndent.substr(0, 3) == "do(")
				outFile << indentDo(toIndent);
		}
	}

	static std::string caseOpenBrace(std::ofstream &outFile, std::string &toIndent, int &tabNum, bool newLineBrace, bool spaceBrace)
	{
		if (!newLineBrace && spaceBrace)
			outFile << ' ';

		if (newLineBrace)
		{
			outFile << '\n';
			for (int i(0); i < tabNum; i++)
				outFile << '\t';
		}

		outFile << "{\n";
		tabNum++;
		for (int i(0); i < tabNum; i++)
			outFile << '\t';
		toIndent.erase(0, 1);
	}

	static std::string caseCloseBrace(std::ofstream &outFile, std::string &toIndent, int &tabNum)
	{
		outFile << '\n';
		tabNum--;

		for (int i(0); i < tabNum; i++)
			outFile << '\t';

		outFile << "}\n";

		for (int i(0); i < tabNum; i++)
			outFile << '\t';

		toIndent.erase(0, 1);
	}

	static std::string indentPreProc(std::string &toIndent)
	{
		return getNextPreProc(toIndent);
	}

	static std::string indentIf(std::string &toIndent)
	{
		return getNextIf(toIndent);
	}

	static std::string indentFor(std::string &toIndent)
	{
		return getNextFor(toIndent);
	}

	static std::string indentWhile(std::string &toIndent)
	{
		return getNextWhile(toIndent);
	}

	static std::string indentSwitch(std::string &toIndent)
	{
		return getNextSwitch(toIndent);
	}

	static std::string indentDo(std::string &toIndent)
	{
		return getNextDo(toIndent);
	}

};

#endif 