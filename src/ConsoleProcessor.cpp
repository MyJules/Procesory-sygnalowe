#include "ConsoleProcessor.h"

namespace processor
{
	int processConsoleParams(const parser::ConsoleParser::ConsoleParam& params)
	{
		// Handle bad input
		if (params.helpFlag)
		{
			std::cout << params.helpInfo << std::endl;
			return EXIT_SUCCESS;
		}

		if (params.inputFile.empty())
		{
			std::cerr << "No input file provided, please enter file path" << std::endl;
			return EXIT_FAILURE;
		}

		// Handle effect 
		if (params.echoFlag) 
		{
		}

		if (params.amplifyFlag) 
		{
		}
	}
}