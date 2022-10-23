#include "ConsoleProcessor.h"

#include <filesystem>

#include <kfr/base.hpp>
#include <kfr/dft.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>

namespace console
{
	int processConsoleParam(const console::ConsoleParser::ConsoleParam& params)
	{
		std::filesystem::path filePath(params.inputFile);
		if (!std::filesystem::exists(filePath)) 
		{
			std::cerr << "Please enter valid input file\n";
			return EXIT_FAILURE;
		}

		kfr::audio_reader_wav<float> reader(kfr::open_file_for_reading(params.inputFile));

		if (params.helpFlag)
		{
			std::cout << params.helpInfo << std::endl;
			return EXIT_SUCCESS;
		}

		// Handle effect 
		if (params.echoParams)
		{
			using namespace effects;
			auto echo = createEffect<Echo>(params.echoParams.value());
			std::cout << params.echoParams.value() << std::endl;
		}

		if (params.amplifyParams)
		{
			using namespace effects;
			auto echo = createEffect<Amplify>(params.amplifyParams.value());
			std::cout << params.amplifyParams.value() << std::endl;
		}

		if (params.delayParams) 
		{
			using namespace effects;
			auto delay = createEffect<Delay>(params.delayParams.value());
			delay->process();
		}

		if (params.trackInfo) 
		{
			std::cout << "File name: " << filePath.filename() << std::endl;
			std::cout << "SempleRate: " << reader.format().samplerate << std::endl;
			std::cout << "Channels: " << reader.format().channels << std::endl;
			std::cout << "Length: " << reader.format().length << std::endl;
			std::cout << "Duration (s): " << reader.format().length / reader.format().samplerate << std::endl;
			std::cout << "Bit depth: " << kfr::audio_sample_bit_depth(reader.format().type) << std::endl;
		}
	}
}