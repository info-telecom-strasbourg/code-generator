#ifndef CODE_COMPACT_H
#define CODE_COMPACT_H

#include "codeComprehension.hpp"

/**
 * A class that compact a code
 */
class codeCompact : codeComprehension
{
public:
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
};

#endif 