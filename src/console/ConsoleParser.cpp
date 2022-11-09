#include "ConsoleParser.h"

#include "EffectCreator.h"

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <map>

namespace 
{
	enum class EffectType
	{
		Echo,
		Reverse,
	};

	static std::multimap<std::string, EffectType> effectMap
	{
		{"echo", EffectType::Echo},
		{"reverse", EffectType::Reverse}
	};
}

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
		for (const auto& res : result.arguments()) 
		{
			if (auto search = effectMap.find(res.key()); search != effectMap.end()) 
			{
				EffectType effectType = search->second;
				switch (effectType)
				{
				case EffectType::Echo:
				{
					effects::EchoParam echoParams;
					std::stringstream paramStream(res.value());
					paramStream >> echoParams;
					spdlog::info("Creating Echo effect with params: {}", echoParams);
					auto effect = effects::createEffect<effects::Echo>(echoParams);
					m_parameters.effects.emplace_back(std::move(effect));
					break;
				}
				case EffectType::Reverse: 
				{
					spdlog::info("Creating Reverse effect");
					auto effect = effects::createEffect<effects::Reverse>();
					m_parameters.effects.emplace_back(std::move(effect));
					break;
				}
				default:
					spdlog::error("Unhandled EffectType");
					break;
				};
			}
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
			("r,reverse", "Reverse track", cxxopts::value<bool>(m_effectsParams.reverse))
			("n,nextCoolEfect", "Description")
			//TODO: add effects what we want to create
			;
	}
}