#pragma once

#include "pch.h"

class TextFileReader
{
public:
	TextFileReader() = delete;
	TextFileReader(const TextFileReader& other) = delete;
	TextFileReader(const std::filesystem::path& fileName);
	~TextFileReader() = default;

	inline std::filesystem::path GetFileName() const { return _fileName; }
	inline bool Eof() const { return _fs.eof(); }
	void Reset();
	std::string Read(size_t size);

private:
	std::filesystem::path _fileName;
	std::ifstream _fs;
};