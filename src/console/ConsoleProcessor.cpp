#include "ConsoleProcessor.h"

#include <kfr/io.hpp>

#include <filesystem>

namespace console
{
	int processConsoleParam(const console::ConsoleParser::ConsoleParam& params)
	{
		if (params.helpFlag)
		{
			std::cout << params.helpInfo << std::endl;
			return EXIT_SUCCESS;
		}

		std::filesystem::path filePath(params.inputFile);
		if (!std::filesystem::exists(filePath)) 
		{
			std::cerr << "Please enter valid input file\n";
			return EXIT_FAILURE;
		}

		kfr::audio_reader_wav<kfr::fbase> wavReader(kfr::open_file_for_reading(filePath));
		kfr::univector<kfr::fbase> wav = wavReader.read(wavReader.format().length);

		if (params.trackInfo)
		{
			std::cout << "File name: " << filePath.filename() << std::endl;
			std::cout << "SempleRate: " << wavReader.format().samplerate << std::endl;
			std::cout << "Channels: " << wavReader.format().channels << std::endl;
			std::cout << "Length: " << wavReader.format().length << std::endl;
			std::cout << "Duration (s): " << wavReader.format().length / wavReader.format().samplerate << std::endl;
			std::cout << "Bit depth: " << kfr::audio_sample_bit_depth(wavReader.format().type) << std::endl;

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

		// At the end we want to save file
		kfr::audio_writer_wav<kfr::fbase> wavWriter(kfr::open_file_for_writing(params.outputFile), wavReader.format());

		wavWriter.write(wav);
		wavWriter.close();
	}
}