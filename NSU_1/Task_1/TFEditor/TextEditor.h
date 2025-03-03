#pragma once

#include "pch.h"

#include "TextFileReader.h"
#include "TextFileWriter.h"

class TextEditor
{
public:
	TextEditor() = delete;
	TextEditor(const TextEditor& other) = delete;
	TextEditor(const std::filesystem::path& input, const std::filesystem::path& output);
	~TextEditor() = default;

	void ReplaceSubstring(const std::string& oldPattern, const std::string& newPattern);

private:
	void ResetTextFileHandlers() const;

	std::unique_ptr<TextFileReader> _txtReader;
	std::unique_ptr<TextFileWriter> _txtWriter;
	const int _bufSize = 1024;
};
