#pragma once

#include <fstream>
#include <string>

#include "Utils.h"

class TextFileReader
{
public:
	TextFileReader() = delete;
	TextFileReader(const TextFileReader& other) = delete;
	TextFileReader(const fs::path& fileName);
	~TextFileReader() = default;

	inline fs::path GetFileName() const { return _fileName; }
	inline bool Eof() const { return _fs.eof(); }
	void Reset();
	std::string Read(size_t size);

private:
	fs::path _fileName;
	std::ifstream _fs;
};