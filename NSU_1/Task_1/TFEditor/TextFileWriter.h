#pragma once

#include "pch.h"

#include "Utils.h"

class TextFileWriter
{
public:
	TextFileWriter() = delete;
	TextFileWriter(const TextFileWriter& other) = delete;
	TextFileWriter(const fs::path& fileName);
	~TextFileWriter() = default;

	inline fs::path GetFileName() const { return _fileName; }
	inline void Flush() { _fs.flush(); }
	void Write(const std::string& output);
	void Reset();

private:
	fs::path _fileName;
	std::ofstream _fs;
};