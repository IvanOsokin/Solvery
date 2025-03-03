#pragma once

#include "pch.h"

class TextFileWriter
{
public:
	TextFileWriter() = delete;
	TextFileWriter(const TextFileWriter& other) = delete;
	TextFileWriter(const std::filesystem::path& fileName);
	~TextFileWriter() = default;

	inline std::filesystem::path GetFileName() const { return _fileName; }
	inline void Flush() { _fs.flush(); }
	void Write(const std::string& output);
	void Reset();

private:
	std::filesystem::path _fileName;
	std::ofstream _fs;
};