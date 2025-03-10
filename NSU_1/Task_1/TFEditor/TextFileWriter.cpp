#include "TextFileWriter.h"

TextFileWriter::TextFileWriter(const std::filesystem::path& fileName)
{
	_fileName = fileName;
	_outputFileStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	_outputFileStream.open(fileName);
}

void TextFileWriter::Reset()
{
	_outputFileStream.clear();
	_outputFileStream.seekp(0);
}

void TextFileWriter::Write(const std::string& output)
{
	_outputFileStream.write(output.c_str(), output.size());
}