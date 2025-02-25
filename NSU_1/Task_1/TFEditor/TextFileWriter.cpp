#include "TextFileWriter.h"

TextFileWriter::TextFileWriter(const fs::path& fileName)
{
	_fileName = fileName;
	_fs.open(fileName);
}

void TextFileWriter::Reset()
{
	_fs.clear();
	_fs.seekp(0);
}

void TextFileWriter::Write(const std::string& output)
{
	if (!_fs.is_open())
		throw std::runtime_error(std::string("Write file error: cannot get access to the file: " + _fileName.string()));
	
	_fs.write(output.c_str(), output.size());
}