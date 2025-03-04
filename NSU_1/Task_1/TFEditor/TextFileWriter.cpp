#include "TextFileWriter.h"

TextFileWriter::TextFileWriter(const std::filesystem::path& fileName)
{
	_fileName = fileName;
	_fs.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	_fs.open(fileName);
}

void TextFileWriter::Reset()
{
	_fs.clear();
	_fs.seekp(0);
}

void TextFileWriter::Write(const std::string& output)
{
	_fs.write(output.c_str(), output.size());
}