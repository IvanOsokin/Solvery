#pragma once

#include "pch.h"

#include "TextFileReader.h"
#include "TextFileWriter.h"

class TextEditor
{
public:
	TextEditor() = delete;
	explicit TextEditor(const TextEditor& other) = delete;
	TextEditor(const std::filesystem::path& input, const std::filesystem::path& output);
	~TextEditor() = default;

	void ReplaceSubstring(const std::string& oldPattern, const std::string& newPattern);

private:
	void ResetTextFileHandlers() const;

	std::unique_ptr<TextFileReader> _textReader;
	std::unique_ptr<TextFileWriter> _textWriter;
	const size_t _bufferSize = 1024;
};
