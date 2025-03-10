#pragma once

namespace TFEConst
{
	namespace Errors
	{
		const int INVALID_CMDLINE_ARGS_CNT = 1;
		const int SRC_FILE_NOT_EXITS	   = 2;
		const int INVALID_OUTPUT_FILENAME  = 3;
		const int INVALID_OUTPUT_DIRECTORY = 4;
	}

	namespace Messages
	{
		const char* const MSG_INVALID_CMDLINE_ARGS_CNT = "Error: invalid number of the command line parameters : expect {}, actually {}!";
		const char* const MSG_SRC_FILE_NOT_EXITS	   = "Error: the input file \"{}\" does not exist on the drive \"{}\".";
		const char* const MSG_INVALID_OUTPUT_FILENAME  = "Error: the specified output file name is invalid!";
		const char* const MSG_INVALID_OUTPUT_DIRECTORY = "Error: he directory for the output file \"{}\" does not exist!";
		const char* const MSG_RUNTIME_ERROR			   = "An error occured during process: {}!";
	}
}