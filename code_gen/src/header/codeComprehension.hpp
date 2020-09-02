#ifndef CODE_GENERATOR_CODE_COMPREHENSION_H
#define CODE_GENERATOR_CODE_COMPREHENSION_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "unistd.h"

/**
 * A class that analyse a formated file code
 */
class codeComprehension
{
private:
	/* number of opened braces */
	int openedBraces = 0;
	/* number of opened parentheses */
	int openedParentheses = 0;
	/* number of opened hooks */
	int openedHook = 0;
	/* number of tabs required */
	int tabNumb = 0;

public:
	/**
	 * Put a file's content in a string
	 * @param file: the file name
	 * @return a string containing the file's content
	 */
	static std::string
	fileInVector(std::string file)
	{
		std::ifstream fileToRead(file, std::ios::in | std::ios::ate);
		if (!fileToRead)
		{
			std::cerr << "Problem while opening the file " << file << std::endl;
			exit(EXIT_FAILURE);
		}
		std::string str;

		fileToRead.seekg(0, std::ios::end);
		std::ifstream::streampos size = fileToRead.tellg();

		str.reserve(size);
		fileToRead.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(fileToRead)),
				   std::istreambuf_iterator<char>());

		fileToRead.close();
		return str;
	}

	/**
	 * Extract the next string from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next string
	 */
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

	/**
	 * Extract an opening brace
	 * @param stringToExtract: the file's content
	 * @return: a string containing the opening brace
	 */
	static std::string
	getNextOpeningBrace(std::string &stringToExtract)
	{
		if (stringToExtract[0] != '{')
		{
			std::cerr << "The first sub string is not an opening brace" << std::endl;
			return "";
		}

		stringToExtract.erase(0, 1);
		if (stringToExtract.size() != 0 && stringToExtract[0] == '\n')
			stringToExtract.erase(0, 1);
		return "{";
	}

	/**
	 * Extract a closing brace
	 * @param stringToExtract: the file's content
	 * @return: a string containing the closing brace
	 */
	static std::string
	getNextClosingBrace(std::string &stringToExtract)
	{
		if (stringToExtract[0] != '}')
		{
			std::cerr << "The first sub string is not a closing brace" << std::endl;
			return "";
		}

		stringToExtract.erase(0, 1);
		if (stringToExtract.size() != 0 && stringToExtract[0] == '\n')
			stringToExtract.erase(0, 1);
		return "}";
	}

	/**
	 * Extract a space
	 * @param stringToExtract: the file's content
	 * @return: a string containing the space
	 */
	static std::string
	getNextSpace(std::string &stringToExtract)
	{
		if (stringToExtract[0] != ' ')
		{
			std::cerr << "The first sub string is not a space" << std::endl;
			return "";
		}

		stringToExtract.erase(0, 1);
		return " ";
	}

	/**
	 * Extract a linebreak
	 * @param stringToExtract: the file's content
	 * @return: a string containing the linebreak
	 */
	static std::string
	getNextLinebreak(std::string &stringToExtract)
	{
		if (stringToExtract[0] != '\n')
		{
			std::cerr << "The first sub string is not a linebreak" << std::endl;
			return "";
		}

		stringToExtract.erase(0, 1);
		if (stringToExtract.size() != 0)
		{
			int pos = 0;
			while (pos != stringToExtract.size() && (stringToExtract[pos] == ' ' || stringToExtract[pos] == '\t'))
				pos++;
			if (stringToExtract[pos] == '{' || stringToExtract[pos] == '}')
				return "";
		}
		return "\n";
	}

	/**
	 * Extract a tabulation
	 * @param stringToExtract: the file's content
	 * @return: a string containing the tabulation
	 */
	static std::string
	getNextTabulation(std::string &stringToExtract)
	{
		if (stringToExtract[0] != '\t')
		{
			std::cerr << "The first sub string is not a tabulation" << std::endl;
			return "";
		}

		stringToExtract.erase(0, 1);
		return "\t";
	}

	/**
	 * Extract the next comment from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next string
	 */
	static std::string
	getNextComment(std::string &stringToExtract)
	{
		if (stringToExtract[0] != '/')
		{
			std::cerr << "The first sub string is not a comment" << std::endl;
			return "";
		}
		std::string endComment = (stringToExtract[1] == '/') ? "\n" : "*/";
		int lengthEndComment = (stringToExtract[1] == '/') ? 1 : 2;
		int lengthEnd = (stringToExtract[1] == '/') ? 0 : 2;

		int i(2);
		while (stringToExtract.substr(i, lengthEndComment) != endComment && i + lengthEndComment < stringToExtract.size())
			i++;
		std::string nextComment = stringToExtract.substr(0, i + lengthEnd);
		stringToExtract.erase(0, i + lengthEnd);
		return nextComment;
	}

	/**
	 * Extract the next "if" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "if" instruction
	 */
	static std::string
	getNextIf(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 3) != "if(")
		{
			std::cerr << "The first sub string is not a if" << std::endl;
			return "";
		}
		int i(3);

		int parentheses(1);
		bool isInString(false);
		while (parentheses > 0 && i < stringToExtract.size())
		{
			if (stringToExtract[i] == '\"' || stringToExtract[i] == '\'' && stringToExtract[i - 1] != '\\')
				isInString = !isInString;

			if (stringToExtract[i] == '(' && !isInString)
				parentheses++;
			else if (stringToExtract[i] == ')' && !isInString)
				parentheses--;
			i++;
		}

		std::string nextIf = stringToExtract.substr(0, i);
		stringToExtract.erase(0, i);
		return nextIf;
	}

	/**
	 * Extract the next "else" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "else" instruction
	 */
	static std::string
	getNextElse(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 5) != "else{")
		{
			std::cerr << "The first sub string is not a else" << std::endl;
			return "";
		}

		std::string nextIf = stringToExtract.substr(0, 4);
		stringToExtract.erase(0, 4);
		return nextIf;
	}

	/**
	 * Extract the next "while" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "while" instruction
	 */
	static std::string
	getNextWhile(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 6) != "while(")
		{
			std::cerr << "The first sub string is not a while" << std::endl;
			return "";
		}

		int i(6);

		int parentheses(1);
		bool isInString(false);
		while (parentheses > 0 && i < stringToExtract.size())
		{
			if (stringToExtract[i] == '\"' || stringToExtract[i] == '\'' && stringToExtract[i - 1] != '\\')
				isInString = !isInString;

			if (stringToExtract[i] == '(' && !isInString)
				parentheses++;
			else if (stringToExtract[i] == ')' && !isInString)
				parentheses--;
			i++;
		}

		std::string nextWhile = stringToExtract.substr(0, i);
		stringToExtract.erase(0, i);
		return nextWhile;
	}

	/**
	 * Extract the next "for" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "for" instruction
	 */
	static std::string
	getNextFor(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 4) != "for(")
		{
			std::cerr << "The first sub string is not a for" << std::endl;
			return "";
		}

		int i(4);
		int parentheses(1);
		bool isInString(false);
		while (parentheses > 0 && i < stringToExtract.size())
		{
			if (stringToExtract[i] == '\"' || stringToExtract[i] == '\'' && stringToExtract[i - 1] != '\\')
				isInString = !isInString;

			if (stringToExtract[i] == '(' && !isInString)
				parentheses++;
			else if (stringToExtract[i] == ')' && !isInString)
				parentheses--;
			i++;
		}

		std::string nextWhile = stringToExtract.substr(0, i);
		stringToExtract.erase(0, i);
		return nextWhile;
	}

	/**
	 * Extract the next "switch" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "switch" instruction
	 */
	static std::string
	getNextSwitch(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 7) != "switch(")
		{
			std::cerr << "The first sub string is not a switch" << std::endl;
			return "";
		}

		int i(7);
		int parentheses(1);
		bool isInString(false);
		while (parentheses > 0 && i < stringToExtract.size())
		{
			if (stringToExtract[i] == '\"' || stringToExtract[i] == '\'' && stringToExtract[i - 1] != '\\')
				isInString = !isInString;

			if (stringToExtract[i] == '(' && !isInString)
				parentheses++;
			else if (stringToExtract[i] == ')' && !isInString)
				parentheses--;
			i++;
		}

		std::string nextWhile = stringToExtract.substr(0, i);
		stringToExtract.erase(0, i);
		return nextWhile;
	}

	/**
	 * Extract the next "case" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "case" instruction
	 */
	static std::string
	getNextCase(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 5) != "case ")
		{
			std::cerr << "The first sub string is not a case" << std::endl;
			return "";
		}

		std::string nextCase = stringToExtract.substr(0, 5);
		stringToExtract.erase(0, 5);

		int i(0);
		while (i < stringToExtract.size() - 1)
		{
			if (stringToExtract[i] == ':' && stringToExtract[i + 1] == ':')
				i++;
			else if (stringToExtract[i] == ':' && (stringToExtract[i - 1] != '\'' || stringToExtract[i + 1] != '\''))
				break;
			i++;
		}

		nextCase = nextCase + stringToExtract.substr(0, i + 1);
		stringToExtract.erase(0, i + 1);
		return nextCase;
	}

	/**
	 * Extract the next "default" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "default" instruction
	 */
	static std::string
	getNextDefault(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 8) != "default:")
		{
			std::cerr << "The first sub string is not a default" << std::endl;
			return "";
		}

		std::string nextDefault = stringToExtract.substr(0, 8);
		stringToExtract.erase(0, 8);
		return nextDefault;
	}

	/**
	 * Extract the next "do" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "do" instruction
	 */
	static std::string
	getNextDo(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 3) != "do{")
		{
			std::cerr << "The first sub string is not a do" << std::endl;
			return "";
		}

		std::string nextDo = stringToExtract.substr(0, 2);
		stringToExtract.erase(0, 2);
		return nextDo;
	}

	/**
	 * Extract the next "try" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "try" instruction
	 */
	static std::string
	getNextTry(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 4) != "try{")
		{
			std::cerr << "The first sub string is not a try" << std::endl;
			return "";
		}

		std::string nextTry = stringToExtract.substr(0, 3);
		stringToExtract.erase(0, 3);
		return nextTry;
	}

	/**
	 * Extract the next "catch" instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next "catch" instruction
	 */
	static std::string
	getNextCatch(std::string &stringToExtract)
	{
		if (stringToExtract.substr(0, 6) != "catch(")
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

		std::string nextCatch = stringToExtract.substr(0, i);
		stringToExtract.erase(0, i);
		return nextCatch;
	}

	/**
	 * Extract the next classic instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next classic instruction
	 */
	static std::string
	getNextClassic(std::string &stringToExtract)
	{
		int i(0);
		bool isInString(false);
		while (i < stringToExtract.size())
		{
			if (stringToExtract[i] == '\"' || stringToExtract[i] == '\'')
				if (i > 0 && stringToExtract[i - 1] != '\\')
					isInString = !isInString;

			if (!isInString && stringToExtract[i] == ';')
			{
				i++;
				break;
			}
			else if (!isInString && (stringToExtract[i] == '\n' || stringToExtract[i] == '{'))
				break;
			i++;
		}

		std::string nextClasic = stringToExtract.substr(0, i);
		stringToExtract.erase(0, i);
		return nextClasic;
	}

	/**
	 * Extract the next pre-processor instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next pre-processor instruction
	 */
	static std::string
	getNextPreProc(std::string &stringToExtract)
	{
		if (stringToExtract[0] != '#')
		{
			std::cerr << "The first sub string is not a #" << std::endl;
			return "";
		}

		int i(0);
		bool slashed(false);
		while (i < stringToExtract.size() - 1)
		{
			if (stringToExtract[i] == '\n' && !slashed)
				break;

			if (stringToExtract[i] == '\\')
				slashed = true;
			else if (stringToExtract[i] != ' ')
				slashed = false;
			i++;
		}

		std::string nextProc = stringToExtract.substr(0, i + 1);
		stringToExtract.erase(0, i + 1);
		return nextProc;
	}

	/**
	 * Extract the next item from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next string
	 */
	static std::string
	getNextItem(std::string &stringToExtract)
	{
		if (stringToExtract[0] == '#')
			return getNextPreProc(stringToExtract);
		else if (stringToExtract[0] == '/')
			return getNextComment(stringToExtract);
		else if (stringToExtract[0] == '\"')
			return getNextString(stringToExtract);
		else if (stringToExtract[0] == '{')
			return getNextOpeningBrace(stringToExtract);
		else if (stringToExtract[0] == '}')
			return getNextClosingBrace(stringToExtract);
		else if (stringToExtract[0] == ' ')
			return getNextSpace(stringToExtract);
		else if (stringToExtract[0] == '\n')
			return getNextLinebreak(stringToExtract);
		else if (stringToExtract[0] == '\t')
			return getNextTabulation(stringToExtract);
		else if (stringToExtract.substr(0, 3) == "if(")
			return getNextIf(stringToExtract);
		else if (stringToExtract.substr(0, 5) == "else{")
			return getNextElse(stringToExtract);
		else if (stringToExtract.substr(0, 6) == "while(")
			return getNextWhile(stringToExtract);
		else if (stringToExtract.substr(0, 4) == "for(")
			return getNextFor(stringToExtract);
		else if (stringToExtract.substr(0, 7) == "switch(")
			return getNextSwitch(stringToExtract);
		else if (stringToExtract.substr(0, 5) == "case ")
			return getNextCase(stringToExtract);
		else if (stringToExtract.substr(0, 8) == "default:")
			return getNextDefault(stringToExtract);
		else if (stringToExtract.substr(0, 3) == "do{")
			return getNextDo(stringToExtract);
		else if (stringToExtract.substr(0, 4) == "try{")
			return getNextTry(stringToExtract);
		else if (stringToExtract.substr(0, 6) == "catch(")
			return getNextCatch(stringToExtract);
		else
			return getNextClassic(stringToExtract);
	}

	/**
	 * Extract the next item from the file to compact
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next string
	 */
	static std::string
	getNextItemCompact(std::string &stringToExtract)
	{
		if (stringToExtract[0] == '#')
			return getNextPreProc(stringToExtract);
		else if (stringToExtract[0] == '/')
			return getNextComment(stringToExtract);
		else if (stringToExtract[0] == '\"')
			return getNextString(stringToExtract);
		else if (stringToExtract[0] == '{')
			return getNextOpeningBrace(stringToExtract);
		else if (stringToExtract[0] == '}')
			return getNextClosingBrace(stringToExtract);
		else if (stringToExtract[0] == ' ')
			return getNextSpace(stringToExtract);
		else if (stringToExtract[0] == '\n')
			return getNextLinebreak(stringToExtract);
		else if (stringToExtract[0] == '\t')
			return getNextTabulation(stringToExtract);
		else
			return getNextClassic(stringToExtract);
	}

	/**
	 * Indicates if this is an intruction that can have no braces
	 * @param stringToExtract: the file's content
	 * @return: a boolean
	 */
	static bool
	isAnInstructionOneLine(std::string &stringToExtract)
	{
		return (stringToExtract.substr(0, 2) == "if" ||
				stringToExtract.substr(0, 5) == "while" ||
				stringToExtract.substr(0, 3) == "for");
	}

	static void compact(std::string origin_file, std::string compacted_file)
	{
		std::string stringToExtract = fileInVector(origin_file);
		std::string stringExtracted;

		std::ofstream flux_compacted_file(compacted_file, std::ios::out | std::ios::trunc);
		if (!flux_compacted_file)
		{
			std::cerr << "Problem while opening the file " << compacted_file << std::endl;
			exit(EXIT_FAILURE);
		}

		while (stringToExtract.size() > 0)
		{
			stringExtracted = getNextItemCompact(stringToExtract);
			if (stringExtracted[0] == '#' ||
				stringExtracted[0] == '\"' ||
				stringExtracted[0] == '{' ||
				stringExtracted[0] == '}')
				flux_compacted_file << stringExtracted;
			else if (stringExtracted[0] == '/')
			{
				if (stringExtracted[1] == '/')
					flux_compacted_file << "/*";
				flux_compacted_file << stringExtracted;
				if (stringExtracted[1] == '/')
					flux_compacted_file << "*/";
			}
			else if (stringExtracted[0] == ' ' || stringExtracted[0] == '\t')
				continue;
			else if (stringExtracted[0] == '\n')
				flux_compacted_file << " ";
			else
			{
				bool isInString = false;
				for (int i = 0; i < stringExtracted.size(); i++)
				{
					flux_compacted_file << stringExtracted[i];
					if (stringExtracted[i] == '"')
						isInString = !isInString;
					if (!isInString)
					{
						std::string symbols("+-/*=<>()[]:;,?!");
						bool removeSpace = false;
						int pos = i;
						pos++;
						for (int j = 0; j < symbols.size(); j++)
							if (stringExtracted[i] == symbols[j])
							{
								removeSpace = true;
								while (stringExtracted[pos] == ' ' || stringExtracted[pos] == '\t')
									pos++;
							}
						while (stringExtracted[pos] == ' ' || stringExtracted[pos] == '\t')
						{
							pos++;
							for (int j = 0; j < symbols.size(); j++)
								if (stringExtracted[pos] == symbols[j])
									removeSpace = true;
						}
						if (removeSpace)
						{
							i += pos - i - 1;
							removeSpace = false;
						}
					}
				}
			}
			flux_compacted_file.flush();
		}

		flux_compacted_file.close();
	}

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

#endif //CODE_GENERATOR_CODE_COMPREHENSION_H
