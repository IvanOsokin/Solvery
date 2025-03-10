#include "pch.h"

#include "TextEditor.h"
#include "Const.h"

namespace
{
	enum class CommandLineArgument
	{
		claIdxExecutableFilename = 0,
		claIdxInputFile,
		claIdxOutputFile,
		claIdxOldPattern,
		claIdxNewPattern,

		claArgumentCount
	};
}

using TFEConst::Errors::INVALID_CMDLINE_ARGS_CNT;
using TFEConst::Errors::INVALID_OUTPUT_DIRECTORY;
using TFEConst::Errors::INVALID_OUTPUT_FILENAME;
using TFEConst::Errors::SRC_FILE_NOT_EXITS;

using TFEConst::Messages::MSG_INVALID_CMDLINE_ARGS_CNT;
using TFEConst::Messages::MSG_INVALID_OUTPUT_DIRECTORY;
using TFEConst::Messages::MSG_INVALID_OUTPUT_FILENAME;
using TFEConst::Messages::MSG_RUNTIME_ERROR;
using TFEConst::Messages::MSG_SRC_FILE_NOT_EXITS;

int main(int argc, char* argv[])
{
	const int expectedArgumentCount = static_cast<int>(CommandLineArgument::claArgumentCount);
	if (expectedArgumentCount != argc)
	{
		std::cerr << std::vformat(MSG_INVALID_CMDLINE_ARGS_CNT, std::make_format_args(expectedArgumentCount, argc));
		return INVALID_CMDLINE_ARGS_CNT;
	}

	const std::filesystem::path inputFile{ argv[static_cast<int>(CommandLineArgument::claIdxInputFile)]};
	if (!std::filesystem::exists(inputFile))
	{
		std::cerr << std::vformat(MSG_SRC_FILE_NOT_EXITS, std::make_format_args(inputFile.string(), inputFile.root_path().string()));
		return SRC_FILE_NOT_EXITS;
	}

	std::filesystem::path outputFile{ argv[static_cast<int>(CommandLineArgument::claIdxOutputFile)] };
	if (!outputFile.has_filename() || !outputFile.has_extension())
	{
		std::cerr << MSG_INVALID_OUTPUT_FILENAME;
		return INVALID_OUTPUT_FILENAME;
	}

	if (outputFile.parent_path().empty())
	{
		outputFile = inputFile.parent_path() / outputFile;
	}
	else if (!std::filesystem::exists(outputFile.parent_path()))
	{
		std::cerr << std::vformat(MSG_INVALID_OUTPUT_DIRECTORY, std::make_format_args(outputFile.parent_path().string()));
		return INVALID_OUTPUT_DIRECTORY;
	}

	try
	{
		TextEditor textEditor{ inputFile, outputFile };
		textEditor.ReplaceSubstring(argv[static_cast<int>(CommandLineArgument::claIdxOldPattern)], argv[static_cast<int>(CommandLineArgument::claIdxNewPattern)]);
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << std::vformat(MSG_RUNTIME_ERROR, std::make_format_args(e.what()));
		return EXIT_FAILURE;
	}
}