#include <string>
#include <iostream>
#include <vector>

#include <cxxopts.hpp>

struct CustomOpts {
	int a;
	int b;

	friend std::istream& operator>>(std::istream& is, CustomOpts& opts)
	{
		is >> opts.a >> opts.b;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, CustomOpts& opts)
	{
		os << opts.a << " : " << opts.b;
		return os;
	}
};

int main(int argc, char *argv[])
{
	cxxopts::Options mainOptions("AudioProcessor", "Program for audio processing");

	std::string inputFile;
	std::string outputFile;
	int amplify = 0;
	CustomOpts opts;

	mainOptions
		.allow_unrecognised_options()
		.add_options()
		("i,input", "Input audio file name", cxxopts::value<std::string>(inputFile))
		("o,output", "Output file", cxxopts::value<std::string>(outputFile)->default_value("processed.wav"))
		("a,amplify", "Amplify audio (dB)", cxxopts::value<int>(amplify))
		("type", "Type params, example use --type \"a b\" ", cxxopts::value<CustomOpts>(opts))
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
	std::cout << "Amplify: " << amplify << std::endl;
	std::cout << "Custom opts: " << opts << std::endl;

	return 0;
}
