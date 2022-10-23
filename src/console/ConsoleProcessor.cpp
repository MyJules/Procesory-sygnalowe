#include "ConsoleProcessor.h"

namespace console
{
	int processConsoleParam(const console::ConsoleParser::ConsoleParam& params)
	{
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
		if (params.echoParams)
		{
			using namespace effects;
			auto echo = createEffect<Echo>(params.echoParams.value());
			std::cout << params.echoParams.value() << std::endl;
		}

		if (params.amplifyParams)
		{
			using namespace effects;
			auto echo = createEffect<Amplify>(params.amplifyParams.value());
			std::cout << params.amplifyParams.value() << std::endl;
		}

		if (params.delayParams) 
		{
			using namespace effects;
			auto delay = createEffect<Delay>(params.delayParams.value());
			delay->process();
			std::cout << params.delayParams.value() << std::endl;
		}
	}
}