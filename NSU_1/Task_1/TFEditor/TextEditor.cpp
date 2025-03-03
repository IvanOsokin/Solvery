#include "TextEditor.h"
#include "Text.h"

TextEditor::TextEditor(const std::filesystem::path& input, const std::filesystem::path& output)
	: _txtReader(std::make_unique<TextFileReader>(input))
	, _txtWriter(std::make_unique<TextFileWriter>(output))
{ }

void TextEditor::ReplaceSubstring(const std::string& oldPattern, const std::string& newPattern)
{
	ResetTextFileHandlers();
	while (!_txtReader->Eof())
	{
		auto str = _txtReader->Read(_bufSize);
		Text text(std::move(str));
		size_t endPos;
		if (text.TailStartsWithPattern(oldPattern, endPos))
		{
			size_t extraBufSize = oldPattern.size() - (text.Size() - endPos);
			do
			{
				size_t curBufSize = 0;
				if (_bufSize < extraBufSize)
				{
					curBufSize = _bufSize;
				}
				else
				{
					curBufSize = extraBufSize;
				}

				Text tmpText(_txtReader->Read(curBufSize));
				text.Append(tmpText);

				extraBufSize -= curBufSize;

			} while (0 < extraBufSize);
		}
		if (!oldPattern.empty())
		{
			text.Replace(oldPattern, newPattern);
		}
		_txtWriter->Write(text.Data());
	}
	_txtWriter->Flush();
}

void TextEditor::ResetTextFileHandlers() const
{
	_txtReader->Reset();
	_txtWriter->Reset();
}
