#include "ConsoleProcessor.h"

#include <kfr/io.hpp>
#include <spdlog/spdlog.h>

#include <filesystem>

namespace console
{
	int processConsoleParam(const console::ConsoleParser::ConsoleParam& params)
	{
		if (params.helpFlag)
		{
			spdlog::info("Printing help");
			std::cout << params.helpInfo << std::endl;
			return EXIT_SUCCESS;
		}

		std::filesystem::path filePath(params.inputFile);
		if (!std::filesystem::exists(filePath)) 
		{
			spdlog::warn("Input file is not valid");
			std::cerr << "Please enter valid input file\n";
			return EXIT_FAILURE;
		}

		spdlog::info("Opened file for process: {}", params.inputFile);
		kfr::audio_reader_wav<kfr::fbase> wavReader(kfr::open_file_for_reading(filePath));
		auto wavFormat = wavReader.format();
		kfr::univector<kfr::fbase> wav = wavReader.read(wavFormat.length);

		if (params.trackInfo)
		{
			spdlog::info("Printing track info");
			std::cout << "File name: " << filePath.filename() << std::endl;
			std::cout << "SempleRate: " << wavReader.format().samplerate << std::endl;
			std::cout << "Channels: " << wavReader.format().channels << std::endl;
			std::cout << "Length: " << wavReader.format().length << std::endl;
			std::cout << "Duration (s): " << wavReader.format().length / wavReader.format().samplerate << std::endl;
			std::cout << "Bit depth: " << kfr::audio_sample_bit_depth(wavReader.format().type) << std::endl;
		}
		
		// Handle effects
		for (const auto& effect : params.effects) 
		{
			wav = effect->process(wav, wavFormat);
		}

		if (!params.outputFile.empty()) 
		{
			spdlog::info("Saving audio to file: {}", params.outputFile);
			kfr::audio_writer_wav<kfr::fbase> wavWriter(kfr::open_file_for_writing(params.outputFile), wavReader.format());
			wavWriter.write(wav);
			wavWriter.close();
		}
		else 
		{
			spdlog::warn("Output file is empty, not saving processed audio");
			std::cout << "No output file provided, not saving processed audio" << std::endl;
		}

		return EXIT_SUCCESS;
	}
}