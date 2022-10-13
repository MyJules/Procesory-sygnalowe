#include "Echo.h"

#include <string>
#include <iostream>
#include <vector>

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
	cxxopts::Options mainOptions("AudioProcessor", "Program for audio processing");

	std::string inputFile;
	std::string outputFile;
	audio::EchoParam echoParam;
    std::string hello;

	mainOptions
		.set_width(120)
		.add_options()
		("i,input", "Input audio file name", cxxopts::value<std::string>(inputFile))
		("o,output", "Output file", cxxopts::value<std::string>(outputFile)->default_value("processed.wav"))
		("a,amplify", "Enamble amplify audio (dB)", cxxopts::value<bool>())
		("amplifyparam", "Example use --amplifyparam \'\' ")
		("e,echo", "Enable echo", cxxopts::value<bool>())
		("echoparam", "Example use --echoparam \'{Delay time(secons)} {Delay factor}\' ", cxxopts::value<audio::EchoParam>(echoParam))
		("n,nextCoolEfect", "Description")
		//TODO: add effects what we want to create
		;

	try 
	{
		cxxopts::ParseResult result = mainOptions.parse(argc, argv);
	}
	catch(const cxxopts::exceptions::parsing& exception) 
	{
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	if (argc == 1)
	{
		std::cout << mainOptions.help() << std::endl;
		return 0;
	}

	if (inputFile.empty())
	{
		std::cerr << "No input file provided, please enter file path" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Input file: " << inputFile << std::endl; 
	std::cout << "Output file: " << outputFile << std::endl;
	std::cout << "Echo params: " << echoParam << std::endl;

	return 0;
}
