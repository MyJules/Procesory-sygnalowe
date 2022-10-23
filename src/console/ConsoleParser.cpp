#include "ConsoleParser.h"

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
			("i,input", "Input audio file name", cxxopts::value<std::string>(m_parameters.inputFile))
			("o,output", "Output file", cxxopts::value<std::string>(m_parameters.outputFile)->default_value("processed.wav"))
			("a,amplify", "Parameters \'\' ", cxxopts::value<std::optional<effects::AmplifyParam>>(m_parameters.amplifyParams))
			("e,echo", "Parameters \'{Delay time(secons)} {Delay factor}\' ", cxxopts::value<std::optional<effects::EchoParam>>(m_parameters.echoParams))
			("d,delay", "Parameters \'{Delay} {Feedback}\' ", cxxopts::value<std::optional<effects::DelayParam>>(m_parameters.delayParams))
			("n,nextCoolEfect", "Description")
			//TODO: add effects what we want to create
			;
	}
}