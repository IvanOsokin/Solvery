#include "TextEditor.h"
#include "Text.h"

TextEditor::TextEditor(const std::filesystem::path& input, const std::filesystem::path& output)
	: _textReader{ std::make_unique<TextFileReader>(input) }
	, _textWriter{ std::make_unique<TextFileWriter>(output) }
{ }

void TextEditor::ReplaceSubstring(const std::string& oldPattern, const std::string& newPattern)
{
	ResetTextFileHandlers();
	while (!_textReader->Eof())
	{
		std::string str = _textReader->Read(_bufferSize);
		Text text{ std::move(str) };
		size_t endPosition;
		if (text.TailStartsWithPattern(oldPattern, endPosition))
		{
			size_t extraBufferSize = oldPattern.size() - (text.Size() - endPosition);
			do
			{
				size_t currentBufferSize = 0;
				if (_bufferSize < extraBufferSize)
				{
					currentBufferSize = _bufferSize;
				}
				else
				{
					currentBufferSize = extraBufferSize;
				}

				Text tmpText{ _textReader->Read(currentBufferSize) };
				text.Append(tmpText);

				extraBufferSize -= currentBufferSize;

			} while (0 < extraBufferSize);
		}
		if (!oldPattern.empty())
		{
			text.Replace(oldPattern, newPattern);
		}
		_textWriter->Write(text.Data());
	}
	_textWriter->Flush();
}

void TextEditor::ResetTextFileHandlers() const
{
	_textReader->Reset();
	_textWriter->Reset();
}
