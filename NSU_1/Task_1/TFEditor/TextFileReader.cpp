#include "TextFileReader.h"

TextFileReader::TextFileReader(const fs::path& fileName)
{
	if (!fs::exists(fileName))
		throw std::runtime_error(std::string("File \"" + fileName.string() + "\" not found!"));

	_fileName = fileName;
	_fs.open(fileName);
}

void TextFileReader::Reset()
{
	_fs.clear();
	_fs.seekg(0);
}

std::string TextFileReader::Read(size_t size)
{
	if (!_fs.is_open())
		throw std::runtime_error(std::string("Read file error: cannot get access to the file: " + _fileName.string()));

	std::string charArray(size, '\0');
	if (!_fs.eof())
	{
		_fs.read(charArray.data(), size);
		size_t readCnt = static_cast<size_t>(_fs.gcount());
		if (readCnt < size) charArray.resize(readCnt);
	}
	else charArray.clear();
	return charArray;
}
