#pragma once

#include "Echo.h"

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
			std::vector<std::shared_ptr<effects::IEffect>> effects;
			std::string inputFile;
			std::string outputFile;
			std::string helpInfo;
		};

		struct EffectsPrams
		{
			std::optional<effects::EchoParam> echoParams;
		};

		void parse(int argc, char* argv[]);
		std::string help();
		ConsoleParam getConsoleParam();

	private:
		void addOptions();

		cxxopts::Options m_consoleOptions;
		ConsoleParam m_parameters;
		EffectsPrams m_effectsParams;
	};
}