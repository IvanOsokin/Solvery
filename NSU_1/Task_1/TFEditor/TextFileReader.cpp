#include "TextFileReader.h"

TextFileReader::TextFileReader(const std::filesystem::path& fileName)
{
	_fileName = fileName;
	_fs.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	_fs.open(fileName);
}

void TextFileReader::Reset()
{
	_fs.clear();
	_fs.seekg(0);
}

std::string TextFileReader::Read(size_t size)
{
	std::string charArray(size, '\0');
	if (!_fs.eof())
	{
		try
		{
			_fs.read(charArray.data(), size);
		}
		catch (const std::ios_base::failure& fail)
		{
			if (0 == (_fs.rdstate() & std::ios_base::eofbit))
			{
				throw fail;
			}
		}
		size_t readCnt = static_cast<size_t>(_fs.gcount());
		if (readCnt < size)
		{
			charArray.resize(readCnt);
		}
	}
	else
	{
		charArray.clear();
	}
	return charArray;
}
