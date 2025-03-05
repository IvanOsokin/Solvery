#include "pch.h"

#include "TextEditor.h"
#include "Const.h"

const int GetExpectedArgumentCount(const char* const* /*argv*/)
{
	return 5;
}

int main(int argc, char* argv[])
{
	const int expectedArgCnt = GetExpectedArgumentCount(argv);
	if (expectedArgCnt != argc)
	{
		std::cerr << std::vformat(TFEConst::Messages::MSG_INVALID_CMDLINE_ARGS_CNT, std::make_format_args(expectedArgCnt, argc));
		return TFEConst::Errors::INVALID_CMDLINE_ARGS_CNT;
	}

	std::filesystem::path inputFile{ argv[TFEConst::Arguments::CMD_IDX_INPUT_FILE] };
	if (!std::filesystem::exists(inputFile))
	{
		std::cerr << std::vformat(TFEConst::Messages::MSG_SRC_FILE_NOT_EXITS, std::make_format_args(inputFile.string(), inputFile.root_path().string()));
		return TFEConst::Errors::SRC_FILE_NOT_EXITS;
	}

	std::filesystem::path outputFile{ argv[TFEConst::Arguments::CMD_IDX_OUTPUT_FILE] };
	if (!outputFile.has_filename() || !outputFile.has_extension())
	{
		std::cerr << TFEConst::Messages::MSG_INVALID_OUTPUT_FILENAME;
		return TFEConst::Errors::INVALID_OUTPUT_FILENAME;
	}

	if (outputFile.parent_path().empty())
	{
		outputFile = inputFile.parent_path() / outputFile;
	}
	else if (!std::filesystem::exists(outputFile.parent_path()))
	{
		std::cerr << std::vformat(TFEConst::Messages::MSG_INVALID_OUTPUT_DIRECTORY, std::make_format_args(outputFile.parent_path().string()));
		return TFEConst::Errors::INVALID_OUTPUT_DIRECTORY;
	}

	try
	{
		TextEditor textEditor{ inputFile, outputFile };
		textEditor.ReplaceSubstring(argv[TFEConst::Arguments::CMD_IDX_OLD_PATTERN], argv[TFEConst::Arguments::CMD_IDX_NEW_PATTERN]);
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << std::vformat(TFEConst::Messages::MSG_RUNTIME_ERROR, std::make_format_args(e.what()));
		return EXIT_FAILURE;
	}
}