#pragma once

#include "Amplify.h"
#include "Echo.h"

#include <cxxopts.hpp>

#include <vector>
#include <optional>
#include <string>

namespace parser
{
	class ConsoleParser
	{
	public:
		ConsoleParser();

		struct ConsoleParam
		{
			bool helpFlag;
			bool amplifyFlag;
			bool echoFlag;
			effects::AmplifyParam amplifyParams;
			effects::EchoParam echoParams;
			std::string inputFile;
			std::string outputFile;
			std::string helpInfo;
		};

		void parse(int argc, char* argv[]);
		std::string help();
		ConsoleParam getConsoleParam();

	private:
		void addOptions();

		cxxopts::Options m_consoleOptions;
		ConsoleParam m_parameters;
	};
}