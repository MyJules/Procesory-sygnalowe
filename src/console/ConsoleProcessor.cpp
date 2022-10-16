#include "ConsoleProcessor.h"

namespace console
{
	int processConsoleParams(const console::ConsoleParser::ConsoleParam& params)
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
			using namespace effects;
			auto echo = createEffect<Echo>(params.echoParams);
			std::cout << params.echoParams << std::endl;
		}

		if (params.amplifyFlag) 
		{
			using namespace effects;
			auto echo = createEffect<Amplify>(params.amplifyParams);
			std::cout << params.amplifyParams << std::endl;
		}
	}
}