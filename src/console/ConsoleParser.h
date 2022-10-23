#pragma once

#include "Amplify.h"
#include "Echo.h"
#include "Delay.h"

#include <cxxopts.hpp>

#include <vector>
#include <optional>
#include <string>

namespace console
{
	class ConsoleParser
	{
	public:
		ConsoleParser();

		struct ConsoleParam
		{
			bool helpFlag;
			bool trackInfo;
			std::optional<effects::AmplifyParam> amplifyParams;
			std::optional<effects::EchoParam> echoParams;
			std::optional<effects::DelayParam> delayParams;
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