#include "TextFileReader.h"

TextFileReader::TextFileReader(const std::filesystem::path& fileName)
{
	_fileName = fileName;
	_inputFileStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	_inputFileStream.open(fileName);
}

void TextFileReader::Reset()
{
	_inputFileStream.clear();
	_inputFileStream.seekg(0);
}

std::string TextFileReader::Read(size_t size)
{
	std::string characterArray(size, '\0');
	if (!_inputFileStream.eof())
	{
		try
		{
			_inputFileStream.read(characterArray.data(), size);
		}
		catch (const std::ios_base::failure& fail)
		{
			if (0 == (_inputFileStream.rdstate() & std::ios_base::eofbit))
			{
				throw fail;
			}
		}
		const size_t readStreamByteCount = static_cast<size_t>(_inputFileStream.gcount());
		if (readStreamByteCount < size)
		{
			characterArray.resize(readStreamByteCount);
		}
	}
	else
	{
		characterArray.clear();
	}
	return characterArray;
}
