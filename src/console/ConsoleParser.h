#pragma once

#include "Echo.h"
#include "Reverse.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"
#include "Invert.h"
#include "Fade.h"

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
			bool helpFlag = false;
			bool trackInfo = false;
			std::vector<std::shared_ptr<effects::IEffect>> effects;
			std::string inputFile;
			std::string outputFile;
			std::string helpInfo;
		};

		struct EffectsPrams
		{
			std::optional<effects::EchoParam> echoParams;
			std::optional<effects::LowPassFilterParam> lowPassParams;
			std::optional<effects::HighPassFilterParam> highPassParams;
			bool reverse = false;
			bool invert = false;
			std::optional<effects::FadeParam> fadeParams;
		};

		void parse(int argc, char* argv[]);
		std::string help();
		ConsoleParam getConsoleParam();

	private:
		void addOptions();
		void processParamEffects();

		void onEcho(const std::string& param);
		void onLowPassFilter(const std::string& param);
		void onHighPassFilter(const std::string& param);
		void onReverse();
		void onInvert();
		void onFade(const std::string& param);

		cxxopts::Options m_consoleOptions;
		cxxopts::ParseResult m_parseResult;
		ConsoleParam m_parameters;
		EffectsPrams m_effectsParams;
	};
}