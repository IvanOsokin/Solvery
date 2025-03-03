#include "pch.h"

#include "TextEditor.h"
#include "Errors.h"

int main(int argc, char* argv[])
{
	if (5 != argc)
	{
		std::cerr << "Error: invalid number of the command line parameters: expect 5, actually " << argc << ".";
		return TFEError::INVALID_CMDLINE_ARGS_CNT;
	}

	std::filesystem::path inputFile = std::filesystem::path(argv[1]);
	if (!std::filesystem::exists(inputFile))
	{
		std::cerr << "Error: the input file \"" << inputFile.string() << "\" does not exist on the drive \"" << inputFile.root_path().string() << "\".";
		return TFEError::SRC_FILE_NOT_EXITS;
	}

	std::filesystem::path outputFile = std::filesystem::path(argv[2]);
	if (!outputFile.has_filename() || !outputFile.has_extension())
	{
		std::cerr << "Error: the specified output file name is invalid!";
		return TFEError::INVALID_OUTPUT_FILENAME;
	}

	if (outputFile.parent_path().empty())
	{
		outputFile = inputFile.parent_path() / outputFile;
	}
	else if (!std::filesystem::exists(outputFile.parent_path()))
	{
		std::cerr << "Error: he directory for the output file \"" << outputFile.parent_path().string() << "\" does not exist!";
		return TFEError::INVALID_OUTPUT_DIRECTORY;
	}

	try
	{
		TextEditor textEditor(inputFile, outputFile);
		textEditor.ReplaceSubstring(argv[3], argv[4]);
		return TFEError::SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occured during process: " << e.what();
		return TFEError::APP_RUNTIME_ERROR;
	}
}