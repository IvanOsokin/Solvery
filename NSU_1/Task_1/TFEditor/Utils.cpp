#include "Utils.h"

int ParseCmdLine(int argc, char* argv[], fs::path& inputFile, fs::path& outputFile)
{
	if (argc != 5)
	{
		std::cerr << "Error: invalid number of the command line parameters: expect 5, actually " << argc << ".";
		return TFEError::INVALID_CMDLINE_ARGS_CNT;
	}

	inputFile = fs::path(argv[1]);
	if (!fs::exists(inputFile))
	{
		std::cerr << "Error: the input file \"" << inputFile.string() << "\"\ndoes not exist on the drive \"" << inputFile.root_path().string() << "\".";
		return TFEError::SRC_FILE_NOT_EXITS;
	}

	outputFile = fs::path(argv[2]);
	if (!outputFile.has_filename() || !outputFile.has_extension())
	{
		std::cerr << "Error: the specified output file name is invalid!";
		return TFEError::INVALID_OUTPUT_FILENAME;
	}

	if (outputFile.parent_path().empty()) outputFile = inputFile.parent_path() / outputFile;
	else if (!fs::exists(outputFile.parent_path()))
	{
		std::cerr << "Error: he directory for the output file \"" << outputFile.parent_path().string() << "\" does not exist!";
		return TFEError::INVALID_OUTPUT_DIRECTORY;
	}

	return TFEError::SUCCESS;
}