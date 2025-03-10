#pragma once

#include "pch.h"

class TextFileReader
{
public:
	TextFileReader() = delete;
	explicit TextFileReader(const TextFileReader& other) = delete;
	explicit TextFileReader(const std::filesystem::path& fileName);
	~TextFileReader() = default;

	inline std::filesystem::path GetFileName() const { return _fileName; }
	inline bool Eof() const { return _inputFileStream.eof(); }
	void Reset();
	std::string Read(size_t size);

private:
	std::filesystem::path _fileName;
	std::ifstream _inputFileStream;
};