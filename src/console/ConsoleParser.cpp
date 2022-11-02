#include "ConsoleParser.h"

#include "EffectCreator.h"

#include <cxxopts.hpp>

namespace console 
{
	ConsoleParser::ConsoleParser()
		: m_consoleOptions("AudioProcessor", "Program for audio processing")
	{
		addOptions();
		m_parameters.helpInfo = m_consoleOptions.help();
	}

	void ConsoleParser::parse(int argc, char* argv[])
	{
		auto result = m_consoleOptions.parse(argc, argv);

		// Emplace new effects into vector of effects
		if (m_effectsParams.echoParams)
		{
			auto effect = effects::createEffect<effects::Echo>(m_effectsParams.echoParams.value());
			m_parameters.effects.emplace_back(std::move(effect));
		}
	}

	std::string ConsoleParser::help()
	{
		return m_consoleOptions.help();
	}

	ConsoleParser::ConsoleParam ConsoleParser::getConsoleParam()
	{
		return m_parameters;
	}

	void ConsoleParser::addOptions()
	{
		m_consoleOptions
			.set_width(120)
			.add_options()
			("h,help", "Print help", cxxopts::value<bool>(m_parameters.helpFlag))
			("info", "Print track info", cxxopts::value<bool>(m_parameters.trackInfo))
			("i,input", "Input audio file name", cxxopts::value<std::string>(m_parameters.inputFile))
			("o,output", "Output file", cxxopts::value<std::string>(m_parameters.outputFile))
			("e,echo", "Parameters \'{Delay time(secons)} {Decay factor}\' ", cxxopts::value<std::optional<effects::EchoParam>>(m_effectsParams.echoParams))
			("n,nextCoolEfect", "Description")
			//TODO: add effects what we want to create
			;
	}
}