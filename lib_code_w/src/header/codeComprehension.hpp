#ifndef CODE_GENERATOR_CODE_COMPREHENSION_H
#define CODE_GENERATOR_CODE_COMPREHENSION_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

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

		int i(2);
		while (stringToExtract.substr(i, lengthEndComment) != endComment && i + lengthEndComment < stringToExtract.size())
			i++;
		std::string nextComment = stringToExtract.substr(0, i + lengthEndComment);
		stringToExtract.erase(0, i + 1);
		return nextComment;
	}

	/**
	 * Extract the next instruction from the file
	 * @param stringToExtract: the file's content
	 * @return: a string containing the next string
	 */
	static std::string
	getNextInstr(std::string &stringToExtract)
	{
		if (stringToExtract[0] == '#')
			return getNextPreProc(stringToExtract);
		else if (stringToExtract.substr(0, 2) == "if")
			return getNextIf(stringToExtract);
		else if (stringToExtract.substr(0, 4) == "else")
			return getNextElse(stringToExtract);
		else if (stringToExtract.substr(0, 5) == "while")
			return getNextWhile(stringToExtract);
		else if (stringToExtract.substr(0, 3) == "for")
			return getNextFor(stringToExtract);
		else if (stringToExtract.substr(0, 5) == "switch")
			return getNextSwitch(stringToExtract);
		else if (stringToExtract.substr(0, 2) == "do")
			return getNextDo(stringToExtract);
		else if (stringToExtract.substr(0, 3) == "try")
			return getNextTry(stringToExtract);
		else if (stringToExtract.substr(0, 5) == "catch")
			return getNextCatch(stringToExtract);
		else
			return getNextClassic(stringToExtract);
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
		while (stringToExtract[i] != ';' && i < stringToExtract.size()-1)
			i++;

		std::string nextClasic = stringToExtract.substr(0, i+1);
		stringToExtract.erase(0, i+1);
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
		while (i < stringToExtract.size())
		{
			if(stringToExtract[i] == '\n' && !slashed)
				break;

			if(stringToExtract[i] == '\\')
				slashed = true;
			else if(stringToExtract[i] != ' ')
				slashed = false;
			i++;
		}

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
