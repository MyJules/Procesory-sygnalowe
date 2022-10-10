#include <string>
#include <iostream>

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
	cxxopts::Options options("AudioProcessor", "Program for audio processing");

	options.add_options()
		("f,file", "Audio file name", cxxopts::value<std::string>())
		("o,output", "Output file", cxxopts::value<std::string>()->default_value("processed"))
		("a,amplify", "Amplify audio", cxxopts::value<bool>()->default_value("false"))
		//TODO: add effects what we want to create
		;
	options.allow_unrecognised_options();

	if (argc == 1)
	{
		std::cout << options.help() << std::endl;
		return 0;
	}

	cxxopts::ParseResult result = options.parse(argc, argv);

	for (auto &res : result.arguments()) 
	{
		std::cout <<  res.key() << " : " << res.value() << std::endl;
	}

	return 0;
}
