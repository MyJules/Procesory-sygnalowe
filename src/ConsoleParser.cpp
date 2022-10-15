#include "ConsoleParser.h"

#include <cxxopts.hpp>

ConsoleParser::ConsoleParser()
	:m_consoleOptions("AudioProcessor", "Program for audio processing")
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
		("h,help",          "Print help",                                                       cxxopts::value<bool>(m_parameters.help))
		("i,input",         "Input audio file name",                                            cxxopts::value<std::string>(m_parameters.inputFile))
		("o,output",        "Output file",                                                      cxxopts::value<std::string>(m_parameters.outputFile)->default_value("processed.wav"))
		("a,amplify",       "Enamble amplify audio (dB)",                                       cxxopts::value<bool>(m_parameters.amplify))
		("amplifyparam",    "Example use --amplifyparam \'\' ",                                 cxxopts::value<effects::AmplifyParam>(m_parameters.amplifyParams))
		("e,echo",          "Enable echo",                                                      cxxopts::value<bool>(m_parameters.echo))
		("echoparam",       "Example use --echoparam \'{Delay time(secons)} {Delay factor}\' ", cxxopts::value<effects::EchoParam>(m_parameters.echoParams))
		("n,nextCoolEfect", "Description")
		//TODO: add effects what we want to create
		;
}