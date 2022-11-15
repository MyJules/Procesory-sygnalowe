#include "ConsoleParser.h"

#include "EffectCreator.h"
#include <Validator.h>

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
		LowPassFilter,
	};

	const static std::unordered_multimap<std::string, EffectType> effectMap
	{
		{"echo", EffectType::Echo},
		{"reverse", EffectType::Reverse},
		{"lowPassFilter", EffectType::LowPassFilter}
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
		m_parseResult = m_consoleOptions.parse(argc, argv);

		processParamEffects();
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
			("l,lowPassFilter", "Parameters \'{Frequency} {Roll off - (6, 12, 24, 36, 48)}\' ", cxxopts::value<std::optional<effects::LowPassFilterParam>>(m_effectsParams.lowPassParams))
			("r,reverse", "Reverse track", cxxopts::value<bool>(m_effectsParams.reverse))
			//("n,nextCoolEfect", "Description")
			//TODO: add effects what we want to create
			;
	}

	void ConsoleParser::processParamEffects()
	{
		// Emplace new effects into vector of effects
		for (const auto& res : m_parseResult.arguments())
		{
			if (auto search = effectMap.find(res.key()); search != effectMap.end())
			{
				EffectType effectType = search->second;
				switch (effectType)
				{
				case EffectType::Echo:
					onEcho(res.value());
					break;
				
				case EffectType::Reverse:
					onReverse();
					break;
				
				case EffectType::LowPassFilter:
					onLowPassFilter(res.value());
					break;
				
				default:
					spdlog::error("Unhandled EffectType");
					break;
				};
			}
		}
	}
	void ConsoleParser::onEcho(const std::string& param)
	{
		effects::EchoParam echoParams;
		std::stringstream paramStream(param);
		paramStream >> echoParams;

		spdlog::info("Creating Echo effect with params: {}", echoParams);

		auto effect = effects::createEffect<effects::Echo>(echoParams);
		m_parameters.effects.emplace_back(std::move(effect));
	}

	void ConsoleParser::onReverse()
	{
		spdlog::info("Creating Reverse effect");
		auto effect = effects::createEffect<effects::Reverse>();
		m_parameters.effects.emplace_back(std::move(effect));
	}

	void ConsoleParser::onLowPassFilter(const std::string& param)
	{
		effects::LowPassFilterParam lowPassFilterParam;
		std::stringstream paramStream(param);
		paramStream >> lowPassFilterParam;

		bool validated = effects::validate(lowPassFilterParam);
		if (!validated)
		{
			spdlog::warn("Failed to validate Low pass filter params");
			std::cout << "Bad Low pass filter parameters: \n" << lowPassFilterParam << std::endl;
			return;
		}

		spdlog::info("Creating Low pass filter effect with params: {}", lowPassFilterParam);
		auto effect = effects::createEffect<effects::LowPassFilter>(lowPassFilterParam);
		m_parameters.effects.emplace_back(std::move(effect));
	}
}